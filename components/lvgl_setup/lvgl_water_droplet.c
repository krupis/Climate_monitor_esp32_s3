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



LV_IMG_DECLARE(Blue_yellow_red_png)
LV_IMG_DECLARE(Co2_png)
LV_IMG_DECLARE(Co2_arc_png)
LV_IMG_DECLARE(Droplet_png)
LV_IMG_DECLARE(Thermometer_png)
LV_IMG_DECLARE(Water_png)

extern QueueHandle_t update_queue;

lv_obj_t * ui_MainScreen;
lv_obj_t * ui_TemperatureGroup;
lv_obj_t * ui_TemperatureArc;
lv_obj_t * ui_Thermometer;
lv_obj_t * ui_TemperatureLabel;
lv_obj_t * ui_HumidityGroup;
lv_obj_t * ui_HumidityArc;
lv_obj_t * ui_Droplet;
lv_obj_t * ui_DropletLabel;
lv_obj_t * ui_CO2Group;
lv_obj_t * ui_CO2Arc;
lv_obj_t * ui_CO2;
lv_obj_t * ui_CO2Label;
lv_obj_t * ui____initial_actions0;






void set_temperature(float temperature){
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%.1f", temperature);//make the number into string using sprintf function
    final_temp_buf[0] = '\0';
    strcat(final_temp_buf, "+");
    strcat(final_temp_buf, float_temp_buf);
    strcat(final_temp_buf, "°");
    lv_label_set_text(ui_TemperatureLabel, final_temp_buf);
    lv_arc_set_value(ui_TemperatureArc, (int16_t)(temperature));
}

void set_humidity(float humidity){
    char temp_buf[8];
    sprintf(temp_buf, "%.1f", humidity);//make the number into string using sprintf function
    strcat(temp_buf,"%");
    lv_label_set_text(ui_DropletLabel, temp_buf);
    lv_arc_set_value(ui_HumidityArc, (int16_t)(humidity));
}


void ui_Mainscreen_screen_init(void)
{
    // ui_MainScreen = lv_obj_create(NULL);
    // lv_obj_clear_flag(ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    // ui_TemperatureGroup = lv_obj_create(ui_MainScreen);
    // lv_obj_set_width(ui_TemperatureGroup, 160);
    // lv_obj_set_height(ui_TemperatureGroup, 100);
    // lv_obj_set_x(ui_TemperatureGroup, 0);
    // lv_obj_set_y(ui_TemperatureGroup, -100);
    // lv_obj_set_align(ui_TemperatureGroup, LV_ALIGN_CENTER);
    // lv_obj_clear_flag(ui_TemperatureGroup, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    // lv_obj_set_style_bg_color(ui_TemperatureGroup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui_TemperatureGroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_color(ui_TemperatureGroup, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_opa(ui_TemperatureGroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_TemperatureArc = lv_arc_create(ui_TemperatureGroup);
    // lv_obj_set_width(ui_TemperatureArc, 80);
    // lv_obj_set_height(ui_TemperatureArc, 80);
    // lv_obj_set_x(ui_TemperatureArc, -40);
    // lv_obj_set_y(ui_TemperatureArc, 0);
    // lv_obj_set_align(ui_TemperatureArc, LV_ALIGN_CENTER);
    // lv_arc_set_range(ui_TemperatureArc, -40, 100);
    // lv_arc_set_value(ui_TemperatureArc, 55);
    // lv_obj_set_style_arc_color(ui_TemperatureArc, lv_color_hex(0xB3B3E5), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_opa(ui_TemperatureArc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_width(ui_TemperatureArc, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_set_style_arc_width(ui_TemperatureArc, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_img_src(ui_TemperatureArc, &Blue_yellow_red_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // ui_Thermometer = lv_img_create(ui_TemperatureGroup);
    // lv_img_set_src(ui_Thermometer, &Thermometer_png);
    // lv_obj_set_width(ui_Thermometer, LV_SIZE_CONTENT);   /// 1
    // lv_obj_set_height(ui_Thermometer, LV_SIZE_CONTENT);    /// 1
    // lv_obj_set_x(ui_Thermometer, -40);
    // lv_obj_set_y(ui_Thermometer, 0);
    // lv_obj_set_align(ui_Thermometer, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_Thermometer, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    // lv_obj_clear_flag(ui_Thermometer, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    // lv_img_set_zoom(ui_Thermometer, 100);

    // ui_TemperatureLabel = lv_label_create(ui_TemperatureGroup);
    // lv_obj_set_width(ui_TemperatureLabel, LV_SIZE_CONTENT);   /// 1
    // lv_obj_set_height(ui_TemperatureLabel, LV_SIZE_CONTENT);    /// 1
    // lv_obj_set_x(ui_TemperatureLabel, 40);
    // lv_obj_set_y(ui_TemperatureLabel, 0);
    // lv_obj_set_align(ui_TemperatureLabel, LV_ALIGN_CENTER);
    // lv_label_set_text(ui_TemperatureLabel, "+24.5°");
    // lv_obj_set_style_text_font(ui_TemperatureLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_HumidityGroup = lv_obj_create(ui_MainScreen);
    // lv_obj_set_width(ui_HumidityGroup, 160);
    // lv_obj_set_height(ui_HumidityGroup, 100);
    // lv_obj_set_align(ui_HumidityGroup, LV_ALIGN_CENTER);
    // lv_obj_clear_flag(ui_HumidityGroup, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    // lv_obj_set_style_bg_color(ui_HumidityGroup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui_HumidityGroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_color(ui_HumidityGroup, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_opa(ui_HumidityGroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_HumidityArc = lv_arc_create(ui_HumidityGroup);
    // lv_obj_set_width(ui_HumidityArc, 80);
    // lv_obj_set_height(ui_HumidityArc, 80);
    // lv_obj_set_x(ui_HumidityArc, -40);
    // lv_obj_set_y(ui_HumidityArc, 0);
    // lv_obj_set_align(ui_HumidityArc, LV_ALIGN_CENTER);
    // lv_arc_set_value(ui_HumidityArc, 55);
    // lv_obj_set_style_arc_color(ui_HumidityArc, lv_color_hex(0xB3B3E5), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_opa(ui_HumidityArc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_width(ui_HumidityArc, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_set_style_arc_width(ui_HumidityArc, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_img_src(ui_HumidityArc, &Water_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // ui_Droplet = lv_img_create(ui_HumidityGroup);
    // lv_img_set_src(ui_Droplet, &Droplet_png);
    // lv_obj_set_width(ui_Droplet, LV_SIZE_CONTENT);   /// 1
    // lv_obj_set_height(ui_Droplet, LV_SIZE_CONTENT);    /// 1
    // lv_obj_set_x(ui_Droplet, -40);
    // lv_obj_set_y(ui_Droplet, 0);
    // lv_obj_set_align(ui_Droplet, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_Droplet, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    // lv_obj_clear_flag(ui_Droplet, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    // lv_img_set_zoom(ui_Droplet, 100);

    // ui_DropletLabel = lv_label_create(ui_HumidityGroup);
    // lv_obj_set_width(ui_DropletLabel, LV_SIZE_CONTENT);   /// 1
    // lv_obj_set_height(ui_DropletLabel, LV_SIZE_CONTENT);    /// 1
    // lv_obj_set_x(ui_DropletLabel, 40);
    // lv_obj_set_y(ui_DropletLabel, 0);
    // lv_obj_set_align(ui_DropletLabel, LV_ALIGN_CENTER);
    // lv_label_set_text(ui_DropletLabel, "70%");
    // lv_obj_set_style_text_font(ui_DropletLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_CO2Group = lv_obj_create(ui_MainScreen);
    // lv_obj_set_width(ui_CO2Group, 160);
    // lv_obj_set_height(ui_CO2Group, 100);
    // lv_obj_set_x(ui_CO2Group, 0);
    // lv_obj_set_y(ui_CO2Group, 100);
    // lv_obj_set_align(ui_CO2Group, LV_ALIGN_CENTER);
    // lv_obj_clear_flag(ui_CO2Group, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    // lv_obj_set_style_bg_color(ui_CO2Group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui_CO2Group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_color(ui_CO2Group, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_opa(ui_CO2Group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_CO2Arc = lv_arc_create(ui_CO2Group);
    // lv_obj_set_width(ui_CO2Arc, 80);
    // lv_obj_set_height(ui_CO2Arc, 80);
    // lv_obj_set_x(ui_CO2Arc, -40);
    // lv_obj_set_y(ui_CO2Arc, 0);
    // lv_obj_set_align(ui_CO2Arc, LV_ALIGN_CENTER);
    // lv_arc_set_value(ui_CO2Arc, 55);
    // lv_obj_set_style_arc_color(ui_CO2Arc, lv_color_hex(0xB3B3E5), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_opa(ui_CO2Arc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_width(ui_CO2Arc, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_set_style_arc_width(ui_CO2Arc, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    // lv_obj_set_style_arc_img_src(ui_CO2Arc, &Co2_arc_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // ui_CO2 = lv_img_create(ui_CO2Group);
    // lv_img_set_src(ui_CO2, &Co2_png);
    // lv_obj_set_width(ui_CO2, LV_SIZE_CONTENT);   /// 1
    // lv_obj_set_height(ui_CO2, LV_SIZE_CONTENT);    /// 1
    // lv_obj_set_x(ui_CO2, -40);
    // lv_obj_set_y(ui_CO2, 0);
    // lv_obj_set_align(ui_CO2, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_CO2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    // lv_obj_clear_flag(ui_CO2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    // lv_img_set_zoom(ui_CO2, 100);

    // ui_CO2Label = lv_label_create(ui_CO2Group);
    // lv_obj_set_width(ui_CO2Label, LV_SIZE_CONTENT);   /// 1
    // lv_obj_set_height(ui_CO2Label, LV_SIZE_CONTENT);    /// 1
    // lv_obj_set_x(ui_CO2Label, 40);
    // lv_obj_set_y(ui_CO2Label, 0);
    // lv_obj_set_align(ui_CO2Label, LV_ALIGN_CENTER);
    // lv_label_set_text(ui_CO2Label, "1000\nppm");
    // lv_obj_set_style_text_font(ui_CO2Label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_MainScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TemperatureGroup = lv_obj_create(ui_MainScreen);
    lv_obj_set_width(ui_TemperatureGroup, 100);
    lv_obj_set_height(ui_TemperatureGroup, 160);
    lv_obj_set_x(ui_TemperatureGroup, -100);
    lv_obj_set_y(ui_TemperatureGroup, 0);
    lv_obj_set_align(ui_TemperatureGroup, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_TemperatureGroup, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_TemperatureGroup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TemperatureGroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TemperatureGroup, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TemperatureGroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureArc = lv_arc_create(ui_TemperatureGroup);
    lv_obj_set_width(ui_TemperatureArc, 90);
    lv_obj_set_height(ui_TemperatureArc, 90);
    lv_obj_set_x(ui_TemperatureArc, -5);
    lv_obj_set_y(ui_TemperatureArc, 0);
    lv_obj_set_align(ui_TemperatureArc, LV_ALIGN_CENTER);
    lv_arc_set_range(ui_TemperatureArc, -40, 100);
    lv_arc_set_value(ui_TemperatureArc, 55);
    lv_obj_set_style_arc_width(ui_TemperatureArc, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_TemperatureArc, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_img_src(ui_TemperatureArc, &Blue_yellow_red_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_TemperatureArc, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TemperatureArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Thermometer = lv_img_create(ui_TemperatureGroup);
    lv_img_set_src(ui_Thermometer, &Thermometer_png);
    lv_obj_set_width(ui_Thermometer, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Thermometer, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Thermometer, -5);
    lv_obj_set_y(ui_Thermometer, 0);
    lv_obj_set_align(ui_Thermometer, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Thermometer, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Thermometer, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Thermometer, 125);

    ui_TemperatureLabel = lv_label_create(ui_TemperatureGroup);
    lv_obj_set_width(ui_TemperatureLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TemperatureLabel, 0);
    lv_obj_set_y(ui_TemperatureLabel, -65);
    lv_obj_set_align(ui_TemperatureLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TemperatureLabel, "+24.5°");
    lv_obj_set_style_text_font(ui_TemperatureLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HumidityGroup = lv_obj_create(ui_MainScreen);
    lv_obj_set_width(ui_HumidityGroup, 100);
    lv_obj_set_height(ui_HumidityGroup, 160);
    lv_obj_set_align(ui_HumidityGroup, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_HumidityGroup, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_HumidityGroup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_HumidityGroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_HumidityGroup, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_HumidityGroup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HumidityArc = lv_arc_create(ui_HumidityGroup);
    lv_obj_set_width(ui_HumidityArc, 90);
    lv_obj_set_height(ui_HumidityArc, 90);
    lv_obj_set_align(ui_HumidityArc, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_HumidityArc, 55);
    lv_obj_set_style_arc_width(ui_HumidityArc, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_HumidityArc, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_img_src(ui_HumidityArc, &Water_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_HumidityArc, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_HumidityArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Droplet = lv_img_create(ui_HumidityGroup);
    lv_img_set_src(ui_Droplet, &Droplet_png);
    lv_obj_set_width(ui_Droplet, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Droplet, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Droplet, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Droplet, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Droplet, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Droplet, 125);

    ui_DropletLabel = lv_label_create(ui_HumidityGroup);
    lv_obj_set_width(ui_DropletLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DropletLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DropletLabel, 0);
    lv_obj_set_y(ui_DropletLabel, -65);
    lv_obj_set_align(ui_DropletLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DropletLabel, "70%");
    lv_obj_set_style_text_font(ui_DropletLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CO2Group = lv_obj_create(ui_MainScreen);
    lv_obj_set_width(ui_CO2Group, 113);
    lv_obj_set_height(ui_CO2Group, 160);
    lv_obj_set_x(ui_CO2Group, 100);
    lv_obj_set_y(ui_CO2Group, 0);
    lv_obj_set_align(ui_CO2Group, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_CO2Group, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_CO2Group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CO2Group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CO2Group, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CO2Group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CO2Arc = lv_arc_create(ui_CO2Group);
    lv_obj_set_width(ui_CO2Arc, 90);
    lv_obj_set_height(ui_CO2Arc, 90);
    lv_obj_set_x(ui_CO2Arc, 5);
    lv_obj_set_y(ui_CO2Arc, 0);
    lv_obj_set_align(ui_CO2Arc, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_CO2Arc, 55);
    lv_obj_set_style_arc_width(ui_CO2Arc, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_CO2Arc, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_img_src(ui_CO2Arc, &Co2_arc_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_CO2Arc, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CO2Arc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_CO2 = lv_img_create(ui_CO2Group);
    lv_img_set_src(ui_CO2, &Co2_png);
    lv_obj_set_width(ui_CO2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CO2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CO2, 5);
    lv_obj_set_y(ui_CO2, 0);
    lv_obj_set_align(ui_CO2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CO2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_CO2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_CO2, 125);

    ui_CO2Label = lv_label_create(ui_CO2Group);
    lv_obj_set_width(ui_CO2Label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CO2Label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CO2Label, 0);
    lv_obj_set_y(ui_CO2Label, -65);
    lv_obj_set_align(ui_CO2Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CO2Label, "1000ppm");
    lv_obj_set_style_text_font(ui_CO2Label, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);





}


void Display_main(){
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    //lv_disp_set_rotation(dispp, LV_DISP_ROT_270);
    ui_Mainscreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_MainScreen);

    

}


void Update_temp_humidity(void* arg){
    struct sht40_reading_s local_sht40;
    struct sht40_reading_s average_sht40;
    static uint8_t avg_counter = 0;
    
    for(;;) {
        if(xQueueReceive(update_queue, &local_sht40, portMAX_DELAY)) { 
            average_sht40.temperature += local_sht40.temperature;
            average_sht40.humidity += local_sht40.humidity;
            avg_counter++;
            if(avg_counter >= 10){
                local_sht40.temperature = (average_sht40.temperature/avg_counter);
                local_sht40.humidity = (average_sht40.humidity/avg_counter);
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