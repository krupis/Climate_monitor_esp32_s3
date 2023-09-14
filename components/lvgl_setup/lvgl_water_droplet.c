#include <stdio.h>

#include "esp_log.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ui_helpers.h"
#include "lvgl.h"
#include "lvgl_water_droplet.h"
#include "SHT40.h"




lv_obj_t *ui_MainScreen;
lv_obj_t *ui_TempLabel;
lv_obj_t *ui_TempIcon;
lv_obj_t *ui_GAP1;
lv_obj_t *ui_GAP2;
lv_obj_t *ui_HumidityLabel;
lv_obj_t *ui_HumidityIcon;
lv_obj_t *ui_CO2Icon;
lv_obj_t *ui_CO2Label;
lv_obj_t *ui____initial_actions0;


LV_IMG_DECLARE(light_blue_png)           // HumidityScreen
LV_IMG_DECLARE(CO2_png)           // HumidityScreen
LV_IMG_DECLARE(Thermometer_png)           // HumidityScreen
LV_IMG_DECLARE(Droplet_png)           // HumidityScreen

LV_FONT_DECLARE(ui_font_Interbold52);

extern QueueHandle_t update_queue;

void set_temperature(float temperature)
{
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%.1f", temperature); // make the number into string using sprintf function
    final_temp_buf[0] = '\0';
    strcat(final_temp_buf, "+");
    strcat(final_temp_buf, float_temp_buf);
    strcat(final_temp_buf, "°");
    lv_label_set_text(ui_TempLabel, final_temp_buf);
}

void set_humidity(float humidity)
{
    char temp_buf[8];
    sprintf(temp_buf, "%.1f", humidity); // make the number into string using sprintf function
    strcat(temp_buf, "%");
    lv_label_set_text(ui_HumidityLabel, temp_buf);
}

void set_co2(int16_t co2)
{
    printf("set co2 \n");
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%u", co2); // make the number into string using sprintf function
    lv_label_set_text(ui_CO2Label, float_temp_buf);
}


void Update_temp_humidity(void *arg)
{
    struct sht40_reading_s local_sht40;
    struct sht40_reading_s average_sht40;
    static uint8_t avg_counter = 0;

    for (;;)
    {
        if (xQueueReceive(update_queue, &local_sht40, portMAX_DELAY))
        {
            average_sht40.temperature += local_sht40.temperature;
            average_sht40.humidity += local_sht40.humidity;
            avg_counter++;
            if (avg_counter >= 10)
            {
                local_sht40.temperature = (average_sht40.temperature / avg_counter);
                local_sht40.humidity = (average_sht40.humidity / avg_counter);
                average_sht40.temperature = 0;
                average_sht40.humidity = 0;

                bsp_display_lock(0);
                set_temperature(local_sht40.temperature);
                set_humidity(local_sht40.humidity);
                bsp_display_unlock();
                avg_counter = 0;
            }
        }
    }
}









void ui_MainScreen_screen_init(void)
{
ui_MainScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_img_src( ui_MainScreen, &light_blue_png, LV_PART_MAIN | LV_STATE_DEFAULT );

ui_TempLabel = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_TempLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TempLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_TempLabel, 0 );
lv_obj_set_y( ui_TempLabel, -85 );
lv_obj_set_align( ui_TempLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_TempLabel,"+20°");
lv_obj_set_style_text_color(ui_TempLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_TempLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TempLabel, &ui_font_Interbold52, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TempIcon = lv_img_create(ui_MainScreen);
lv_img_set_src(ui_TempIcon, &Thermometer_png);
lv_obj_set_width( ui_TempIcon, LV_SIZE_CONTENT);  /// 106
lv_obj_set_height( ui_TempIcon, LV_SIZE_CONTENT);   /// 102
lv_obj_set_x( ui_TempIcon, 0 );
lv_obj_set_y( ui_TempIcon, -130 );
lv_obj_set_align( ui_TempIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_TempIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_TempIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_TempIcon,140);

ui_GAP1 = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_GAP1, 170);
lv_obj_set_height( ui_GAP1, 8);
lv_obj_set_x( ui_GAP1, 0 );
lv_obj_set_y( ui_GAP1, -53 );
lv_obj_set_align( ui_GAP1, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_GAP1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_GAP2 = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_GAP2, 170);
lv_obj_set_height( ui_GAP2, 8);
lv_obj_set_x( ui_GAP2, 0 );
lv_obj_set_y( ui_GAP2, 53 );
lv_obj_set_align( ui_GAP2, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_GAP2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_HumidityLabel = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_HumidityLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_HumidityLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_HumidityLabel, 0 );
lv_obj_set_y( ui_HumidityLabel, 20 );
lv_obj_set_align( ui_HumidityLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_HumidityLabel,"45%");
lv_obj_set_style_text_color(ui_HumidityLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_HumidityLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_HumidityLabel, &ui_font_Interbold52, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_HumidityIcon = lv_img_create(ui_MainScreen);
lv_img_set_src(ui_HumidityIcon, &Droplet_png);
lv_obj_set_width( ui_HumidityIcon, LV_SIZE_CONTENT);  /// 100
lv_obj_set_height( ui_HumidityIcon, LV_SIZE_CONTENT);   /// 100
lv_obj_set_x( ui_HumidityIcon, 1 );
lv_obj_set_y( ui_HumidityIcon, -25 );
lv_obj_set_align( ui_HumidityIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_HumidityIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_HumidityIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_HumidityIcon,135);

ui_CO2Icon = lv_img_create(ui_MainScreen);
lv_img_set_src(ui_CO2Icon, &CO2_png);
lv_obj_set_width( ui_CO2Icon, LV_SIZE_CONTENT);  /// 150
lv_obj_set_height( ui_CO2Icon, LV_SIZE_CONTENT);   /// 83
lv_obj_set_x( ui_CO2Icon, 1 );
lv_obj_set_y( ui_CO2Icon, 78 );
lv_obj_set_align( ui_CO2Icon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_CO2Icon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_CO2Icon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_CO2Icon,140);

ui_CO2Label = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_CO2Label, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CO2Label, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CO2Label, 0 );
lv_obj_set_y( ui_CO2Label, 123 );
lv_obj_set_align( ui_CO2Label, LV_ALIGN_CENTER );
lv_label_set_text(ui_CO2Label,"1000");
lv_obj_set_style_text_color(ui_CO2Label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_CO2Label, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_CO2Label, &ui_font_Interbold52, LV_PART_MAIN| LV_STATE_DEFAULT);

}


void ui_init( void )
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_MainScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);

    lv_disp_set_rotation(dispp,LV_DISP_ROT_270);

    lv_disp_load_scr( ui_MainScreen);
}