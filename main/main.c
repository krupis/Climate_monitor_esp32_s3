#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "nvs_flash.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
#include "lvgl_setup.h"
#include "lvgl_water_droplet.h"
#include "UART0.h"
#include "SHT40.h"
#include "WIFI.h"
#include "nvs_custom.h"
#include "S8.h"

static const char *TAG = "main";
extern lv_obj_t *ui_Water;

static void Monitoring_task(void *argument);

void app_main(void)
{
    esp_err_t ret;
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
    {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    lvgl_setup();
    // NVS_open();

    // set_nvs_key_value("wifi_ssid", "TP-Link_5AA5");
    // set_nvs_key_value("wifi_pass", "43634927");

    // char wifi_ssid_local[20];
    // char wifi_pass_local[20];
    // get_nvs_key_value("wifi_ssid",wifi_ssid_local);
    // get_nvs_key_value("wifi_pass",wifi_pass_local);
    // wifi_init_sta2(wifi_ssid_local,wifi_pass_local);

    UART1_setup();
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    // get_info();

    // get_info();

    // Call one at a time to see examples
    //  bsp_display_lock(0);
    //  display_meter();
    //  bsp_display_unlock();
    //  display_image();
    //  display_window();
    // display_color_wheel();

    bsp_display_lock(0);
    display_widgets();
    // Display_keyboard();
    // ui_init();
    bsp_display_unlock();

    // char result[100];
    // const char *middle = "example";

    // // the snprintf solution
    // snprintf(result, sizeof result, "<%s>", middle);

    // // the strcat solution
    // result[0] = '\0';
    // strcat(result, "<");
    // strcat(result, middle);
    // strcat(result, ">");
    // printf("result = %s \n",result);

    // Create_main_display();

    //xTaskCreate(SHT40_task,"SHT40_task",10000,NULL,5,NULL); // receiving commands from main uart
    xTaskCreate(UART0_task, "UART0_task", 10000, NULL, 5, NULL); // receiving commands from main uart
    xTaskCreate(rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(tx_task, "uart_tx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 2, NULL);
    //xTaskCreate(Update_temp_humidity,"Update_temp_humidity",10000,NULL,2,NULL); // receiving commands from main uart
    //xTaskCreate(Update_co2,"Update_temp_humidity",10000,NULL,2,NULL); // receiving commands from main uart
}
