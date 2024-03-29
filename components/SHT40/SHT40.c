#include "SHT40.h"


#define I2C_MASTER_SCL_IO 17
#define I2C_MASTER_SDA_IO 18

#define I2C_MASTER_NUM 0            /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ 400000   /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS 1000

extern QueueHandle_t update_queue;
struct sht40_reading_s sht40_reading;


extern SemaphoreHandle_t i2c_mux;

esp_err_t i2c_master_init(void)
{

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(0, &conf);
    return i2c_driver_install(0, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);

    return ESP_OK;
}

esp_err_t Measure_temp_humidity(uint8_t precision)
{
    uint8_t read_buffer[6];
    uint8_t write_command[1] = {precision};
    esp_err_t err;
    err = i2c_master_write_to_device(I2C_MASTER_NUM, SHT40_SENSOR_ADDR, &write_command, 1, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    if (err != ESP_OK)
    {
        printf("Error in writing to SHT40 device \n");
        return err;
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);

    err = i2c_master_read_from_device(I2C_MASTER_NUM, SHT40_SENSOR_ADDR, &read_buffer, 6, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    if (err != ESP_OK)
    {
        printf("Error in reading from SHT40 device \n");
        return err;
    }

    float t_ticks = read_buffer[0] * 256 + read_buffer[1];
    float rh_ticks = read_buffer[3] * 256 + read_buffer[4];

    float t_degC = -45 + 175 * t_ticks / 65535;
    float rh_pRH = -6 + 125 * rh_ticks / 65535;

    //printf("temperature = %.2f \n", t_degC);
    //printf("humidity = %.2f \n", rh_pRH);
    sht40_reading.temperature = t_degC;
    sht40_reading.humidity = rh_pRH;
    xQueueSend(update_queue, &sht40_reading, NULL);

    return ESP_OK;
}

void SHT40_task(void *argument)
{
    i2c_master_init();
    update_queue = xQueueCreate(2, sizeof(sht40_reading));
    for (;;)
    {
        if (xSemaphoreTake(i2c_mux, 100) == pdTRUE)
        {
            Measure_temp_humidity(SHT40_TEMP_HUMID_REG_HIGH_PREC);
            xSemaphoreGive(i2c_mux);
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
