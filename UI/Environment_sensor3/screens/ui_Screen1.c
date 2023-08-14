// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: Environment_sensor

#include "../ui.h"

void ui_Screen1_screen_init(void)
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
    lv_img_set_src(ui_Droplet, &ui_img_droplet_png);
    lv_obj_set_width(ui_Droplet, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Droplet, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Droplet, 1);
    lv_obj_set_y(ui_Droplet, 56);
    lv_obj_set_align(ui_Droplet, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Droplet, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Droplet, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_Droplet, 185);

    ui_Thermometer = lv_img_create(ui_Icon_group);
    lv_img_set_src(ui_Thermometer, &ui_img_thermometer_png);
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
    lv_obj_set_y(ui_TemperatureText, -39);
    lv_obj_set_align(ui_TemperatureText, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_TemperatureText, "+23°");
    lv_textarea_set_placeholder_text(ui_TemperatureText, "Placeholder...");
    lv_obj_set_style_text_font(ui_TemperatureText, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
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
    lv_obj_set_style_text_font(ui_HumidityText, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_HumidityText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_HumidityText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_HumidityText, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_HumidityText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

}