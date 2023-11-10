// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: Environment_sensor

#include "ui.h"

void ui_MainScreen1_screen_init(void)
{
ui_MainScreen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_MainScreen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_img_src( ui_MainScreen1, &ui_img_light_blue_dithered_rotated_png, LV_PART_MAIN | LV_STATE_DEFAULT );

ui_TempLabel1 = lv_label_create(ui_MainScreen1);
lv_obj_set_width( ui_TempLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TempLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_TempLabel1, 20 );
lv_obj_set_y( ui_TempLabel1, 30 );
lv_obj_set_align( ui_TempLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_TempLabel1,"+20");
lv_obj_set_style_text_color(ui_TempLabel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_TempLabel1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TempLabel1, &ui_font_Interbold40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TempIcon1 = lv_img_create(ui_MainScreen1);
lv_img_set_src(ui_TempIcon1, &ui_img_thermometer_png);
lv_obj_set_width( ui_TempIcon1, LV_SIZE_CONTENT);  /// 106
lv_obj_set_height( ui_TempIcon1, LV_SIZE_CONTENT);   /// 102
lv_obj_set_x( ui_TempIcon1, -60 );
lv_obj_set_y( ui_TempIcon1, 30 );
lv_obj_set_align( ui_TempIcon1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_TempIcon1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_TempIcon1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_TempIcon1,120);

ui_HumidityLabel1 = lv_label_create(ui_MainScreen1);
lv_obj_set_width( ui_HumidityLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_HumidityLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_HumidityLabel1, 20 );
lv_obj_set_y( ui_HumidityLabel1, 80 );
lv_obj_set_align( ui_HumidityLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_HumidityLabel1,"45");
lv_obj_set_style_text_color(ui_HumidityLabel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_HumidityLabel1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_HumidityLabel1, &ui_font_Interbold40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_HumidityIcon1 = lv_img_create(ui_MainScreen1);
lv_img_set_src(ui_HumidityIcon1, &ui_img_droplet_png);
lv_obj_set_width( ui_HumidityIcon1, LV_SIZE_CONTENT);  /// 100
lv_obj_set_height( ui_HumidityIcon1, LV_SIZE_CONTENT);   /// 100
lv_obj_set_x( ui_HumidityIcon1, -60 );
lv_obj_set_y( ui_HumidityIcon1, 80 );
lv_obj_set_align( ui_HumidityIcon1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_HumidityIcon1, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_HumidityIcon1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_HumidityIcon1,120);

ui_CO2Label1 = lv_label_create(ui_MainScreen1);
lv_obj_set_width( ui_CO2Label1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CO2Label1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CO2Label1, 20 );
lv_obj_set_y( ui_CO2Label1, 130 );
lv_obj_set_align( ui_CO2Label1, LV_ALIGN_CENTER );
lv_label_set_text(ui_CO2Label1,"1000");
lv_obj_set_style_text_color(ui_CO2Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_CO2Label1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_CO2Label1, &ui_font_Interbold40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CO2Icon1 = lv_imgbtn_create(ui_MainScreen1);
lv_imgbtn_set_src(ui_CO2Icon1, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_co2_resize_png, NULL);
lv_imgbtn_set_src(ui_CO2Icon1, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_co2_resize_png, NULL);
lv_obj_set_width( ui_CO2Icon1, 83);
lv_obj_set_height( ui_CO2Icon1, 46);
lv_obj_set_x( ui_CO2Icon1, -60 );
lv_obj_set_y( ui_CO2Icon1, 130 );
lv_obj_set_align( ui_CO2Icon1, LV_ALIGN_CENTER );

ui_GAP6 = lv_obj_create(ui_MainScreen1);
lv_obj_set_width( ui_GAP6, 170);
lv_obj_set_height( ui_GAP6, 5);
lv_obj_set_x( ui_GAP6, 0 );
lv_obj_set_y( ui_GAP6, -125 );
lv_obj_set_align( ui_GAP6, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_GAP6, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_GAP6, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_GAP6, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_BatLabel1 = lv_label_create(ui_MainScreen1);
lv_obj_set_width( ui_BatLabel1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_BatLabel1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_BatLabel1, 0 );
lv_obj_set_y( ui_BatLabel1, -144 );
lv_obj_set_align( ui_BatLabel1, LV_ALIGN_CENTER );
lv_label_set_text(ui_BatLabel1,"Battery:");
lv_obj_set_style_text_color(ui_BatLabel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_BatLabel1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_BatLabel1, &lv_font_montserrat_26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_GAP4 = lv_obj_create(ui_MainScreen1);
lv_obj_set_width( ui_GAP4, 170);
lv_obj_set_height( ui_GAP4, 5);
lv_obj_set_x( ui_GAP4, 0 );
lv_obj_set_y( ui_GAP4, -90 );
lv_obj_set_align( ui_GAP4, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_GAP4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_GAP4, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_GAP4, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_GAP5 = lv_obj_create(ui_MainScreen1);
lv_obj_set_width( ui_GAP5, 170);
lv_obj_set_height( ui_GAP5, 5);
lv_obj_set_align( ui_GAP5, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_GAP5, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_GAP5, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_GAP5, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_AirLabel = lv_label_create(ui_MainScreen1);
lv_obj_set_width( ui_AirLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_AirLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_AirLabel, 0 );
lv_obj_set_y( ui_AirLabel, -18 );
lv_obj_set_align( ui_AirLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_AirLabel,"Air");
lv_obj_set_style_text_color(ui_AirLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_AirLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_AirLabel, &lv_font_montserrat_26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ObjectLabel = lv_label_create(ui_MainScreen1);
lv_obj_set_width( ui_ObjectLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ObjectLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ObjectLabel, 0 );
lv_obj_set_y( ui_ObjectLabel, -107 );
lv_obj_set_align( ui_ObjectLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_ObjectLabel,"Object");
lv_obj_set_style_text_color(ui_ObjectLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ObjectLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ObjectLabel, &lv_font_montserrat_26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Image3 = lv_img_create(ui_MainScreen1);
lv_img_set_src(ui_Image3, &ui_img_point_temperature_png);
lv_obj_set_width( ui_Image3, LV_SIZE_CONTENT);  /// 50
lv_obj_set_height( ui_Image3, LV_SIZE_CONTENT);   /// 50
lv_obj_set_x( ui_Image3, -58 );
lv_obj_set_y( ui_Image3, -63 );
lv_obj_set_align( ui_Image3, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Image3, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Image3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_GAP7 = lv_obj_create(ui_MainScreen1);
lv_obj_set_width( ui_GAP7, 170);
lv_obj_set_height( ui_GAP7, 5);
lv_obj_set_x( ui_GAP7, 0 );
lv_obj_set_y( ui_GAP7, -35 );
lv_obj_set_align( ui_GAP7, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_GAP7, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_GAP7, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_GAP7, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ObjectTempLabel = lv_label_create(ui_MainScreen1);
lv_obj_set_width( ui_ObjectTempLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ObjectTempLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ObjectTempLabel, 12 );
lv_obj_set_y( ui_ObjectTempLabel, -62 );
lv_obj_set_align( ui_ObjectTempLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_ObjectTempLabel,"+100");
lv_obj_set_style_text_color(ui_ObjectTempLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ObjectTempLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_ObjectTempLabel, &ui_font_Interbold40, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_CO2Icon1, ui_event_CO2Icon1, LV_EVENT_ALL, NULL);

}
