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
#include "lvgl_custom.h"
#include "UART0.h"
#include "SHT40.h"
#include "WIFI.h"
#include "nvs_custom.h"
#include "S8.h"
#include "gpio.h"

#include "MLX90614_custom.h"

static const char *TAG = "main";







void app_main(void)
{
    esp_err_t ret;
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }


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

    

     UART1_setup();
     xTaskCreate(rx_task, "uart_rx_task", 2048 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
     xTaskCreate(tx_task, "uart_tx_task", 2048 * 2, NULL, configMAX_PRIORITIES - 2, NULL);
    //get_info();

    MUX_initialization();
    lvgl_setup();
    bsp_display_lock(0);
    ui_init();
    bsp_display_unlock();


    ADC_Setup();
    
    xTaskCreate(UART0_task, "UART0_task", 4000, NULL, 5, NULL); // receiving commands from main uart

    xTaskCreate(SHT40_task, "SHT40_task", 4000, NULL, 5, NULL);                     

    xTaskCreate(MLX90614_measure_temp, "MLX90614_measure_temp", 4000, NULL, 5, NULL);                     

    
    xTaskCreate(Update_temp_humidity, "Update_temp_humidity", 4000, NULL, 2, NULL);


}

