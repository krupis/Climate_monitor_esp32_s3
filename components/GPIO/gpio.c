#include "gpio.h"
#include "lvgl_custom.h"




static int adc_raw[2][10];
static int voltage[2][10];
adc_oneshot_unit_handle_t adc1_handle;

const static char *TAG = "ADC";

static bool example_adc_calibration_init(adc_unit_t unit, adc_atten_t atten, adc_cali_handle_t *out_handle);

void ADC_Setup(){


    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

        adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = EXAMPLE_ADC_ATTEN,
    };


    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, EXAMPLE_ADC1_CHAN3, &config));

    xTaskCreate(Measure_bat_voltage,"Measure_bat_voltage",5000,NULL,2,NULL); // receiving commands from main uart


    adc_cali_handle_t adc1_cali_handle = NULL;
    bool do_calibration1 = example_adc_calibration_init(ADC_UNIT_1, EXAMPLE_ADC_ATTEN, &adc1_cali_handle);


}



static bool example_adc_calibration_init(adc_unit_t unit, adc_atten_t atten, adc_cali_handle_t *out_handle)
{
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI(TAG, "calibration scheme version is %s", "Curve Fitting");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_12,
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGI(TAG, "calibration scheme version is %s", "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

    *out_handle = handle;
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else {
        ESP_LOGE(TAG, "Invalid arg or no memory");
    }

    return calibrated;
}

float Get_ADC_Voltage(uint16_t channel){
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, channel, &adc_raw[0][0]));
    //ESP_LOGI(TAG, "ADC%d Channel[%d] Raw Data: %d", ADC_UNIT_1 + 1, channel, adc_raw[0][0]);
    float voltage = (adc_raw[0][0] * 3.3 / 4096)*2.0;
    //ESP_LOGI(TAG, "ADC%d Channel[%d] Voltage: %.2f", ADC_UNIT_1 + 1, channel, voltage);
    set_battery_voltage(voltage);
    return voltage;
}

void Measure_bat_voltage(void *argument)
{
    for (;;)
    {

        Get_ADC_Voltage(EXAMPLE_ADC1_CHAN3);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}