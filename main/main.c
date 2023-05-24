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

static const char *TAG = "main";

void app_main(void)
{
    lvgl_setup();

    display_meter();
    // display_image();
}