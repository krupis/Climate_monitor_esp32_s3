#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
#include "lvgl_setup.h"
#include "lvgl_water_droplet.h"
//#include "UART0.h"

static const char *TAG = "main";


static void Monitoring_task(void *argument);


void app_main(void)
{
    lvgl_setup();


    //Call one at a time to see examples
    //display_meter();
    // display_image();
    // display_window();

    //display_test_temperature();
    //test_display_init();
    //droplet_chatgpt();

    Create_main_display();  

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
//         vTaskDelay(1000/portTICK_PERIOD_MS);
//     }
// }
