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



LV_IMG_DECLARE(Droplet)
LV_IMG_DECLARE(Thermometer)




lv_obj_t * ui_Screen1;
lv_obj_t * ui_Icon_group;
lv_obj_t * ui_Droplet;
lv_obj_t * ui_Thermometer;
lv_obj_t * ui_Text_group;
lv_obj_t * ui_TemperatureText;
lv_obj_t * ui_HumidityText;
lv_obj_t * ui____initial_actions0;



void set_temperature(float temperature){
    char temp_buf[10];
    lv_textarea_set_text(ui_TemperatureText, "22");
}


void ui_Mainscreen_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    
    ui_Icon_group = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Icon_group, 66);
    lv_obj_set_height(ui_Icon_group, 219);
    lv_obj_set_x(ui_Icon_group, -44);
    lv_obj_set_y(ui_Icon_group, -44);
    lv_obj_set_align(ui_Icon_group, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Icon_group, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Icon_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Icon_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Icon_group, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Icon_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Droplet = lv_img_create(ui_Icon_group);
    lv_img_set_src(ui_Droplet, &Droplet);
    lv_obj_set_width(ui_Droplet, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Droplet, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Droplet, 1);
    lv_obj_set_y(ui_Droplet, 56);
    lv_obj_set_align(ui_Droplet, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Droplet, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Droplet, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Droplet, 185);

    ui_Thermometer = lv_img_create(ui_Icon_group);
    lv_img_set_src(ui_Thermometer, &Thermometer);
    lv_obj_set_width(ui_Thermometer, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Thermometer, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Thermometer, 0);
    lv_obj_set_y(ui_Thermometer, -50);
    lv_obj_set_align(ui_Thermometer, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Thermometer, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Thermometer, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Thermometer, 175);

    ui_Text_group = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Text_group, 86);
    lv_obj_set_height(ui_Text_group, 216);
    lv_obj_set_x(ui_Text_group, 35);
    lv_obj_set_y(ui_Text_group, -44);
    lv_obj_set_align(ui_Text_group, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Text_group, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Text_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Text_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Text_group, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Text_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureText = lv_textarea_create(ui_Text_group);
    lv_obj_set_width(ui_TemperatureText, 87);
    lv_obj_set_height(ui_TemperatureText, 70);
    lv_obj_set_x(ui_TemperatureText, -3);
    lv_obj_set_y(ui_TemperatureText, -29);
    lv_obj_set_align(ui_TemperatureText, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_TemperatureText, "+23°");
    lv_textarea_set_placeholder_text(ui_TemperatureText, "Placeholder...");
    lv_obj_set_style_text_font(ui_TemperatureText, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TemperatureText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TemperatureText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_TemperatureText, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_TemperatureText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HumidityText = lv_textarea_create(ui_Text_group);
    lv_obj_set_width(ui_HumidityText, 87);
    lv_obj_set_height(ui_HumidityText, 70);
    lv_obj_set_x(ui_HumidityText, 1);
    lv_obj_set_y(ui_HumidityText, 74);
    lv_obj_set_align(ui_HumidityText, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_HumidityText, "70%");
    lv_textarea_set_placeholder_text(ui_HumidityText, "Placeholder...");
    lv_obj_set_style_text_font(ui_HumidityText, &lv_font_montserrat_36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_HumidityText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_HumidityText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_HumidityText, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_HumidityText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

}


void Display_main(){
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    lv_disp_set_rotation(dispp, LV_DISP_ROT_270);

    ui_Mainscreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}