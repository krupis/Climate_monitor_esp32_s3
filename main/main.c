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

static const char *TAG = "main";
extern lv_obj_t * ui_Water;

static void Monitoring_task(void *argument);


void app_main(void)
{
    esp_err_t ret;
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
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
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());


    lvgl_setup();


    //Call one at a time to see examples
    display_meter();
    // display_image();
    // display_window();


  

    // vTaskDelay(4000/portTICK_PERIOD_MS);
    // Move_water_up_down(ui_Water,0,97,70);
    // vTaskDelay(4000/portTICK_PERIOD_MS);
    // Move_water_up_down(ui_Water,0,70,97);
    // vTaskDelay(4000/portTICK_PERIOD_MS);
    // Move_water_up_down(ui_Water,0,97,70);


    //xTaskCreate(UART0_task,"UART0_task",10000,NULL,5,NULL); // receiving commands from main uart
    //xTaskCreate(Monitoring_task,"Monitoring_task",10000,NULL,5,NULL); // receiving commands from main uart
}






// static void Monitoring_task(void *argument){
//   	for (;;)
// 	{	
//         char stats_buffer[1024];
//         vTaskGetRunTimeStats(stats_buffer);
//         //printf("Task name    | State | Priority    | Stack       | Number \n");
//         ESP_LOGI("TASK_MONITORING","%s",stats_buffer);
//         //printf("%s\n", stats_buffer);
//         vTaskDelay(5000/portTICK_PERIOD_MS);
//     }
// }
