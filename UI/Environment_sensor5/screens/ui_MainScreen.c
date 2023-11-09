// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: Environment_sensor

#include "../ui.h"

void ui_MainScreen_screen_init(void)
{
ui_MainScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_img_src( ui_MainScreen, &ui_img_light_blue_dithered_rotated_png, LV_PART_MAIN | LV_STATE_DEFAULT );

ui_TempLabel = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_TempLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TempLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_TempLabel, 0 );
lv_obj_set_y( ui_TempLabel, -56 );
lv_obj_set_align( ui_TempLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_TempLabel,"+20");
lv_obj_set_style_text_color(ui_TempLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_TempLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_TempLabel, &ui_font_Interbold40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TempIcon = lv_img_create(ui_MainScreen);
lv_img_set_src(ui_TempIcon, &ui_img_thermometer_png);
lv_obj_set_width( ui_TempIcon, LV_SIZE_CONTENT);  /// 106
lv_obj_set_height( ui_TempIcon, LV_SIZE_CONTENT);   /// 102
lv_obj_set_x( ui_TempIcon, 0 );
lv_obj_set_y( ui_TempIcon, -100 );
lv_obj_set_align( ui_TempIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_TempIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_TempIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_TempIcon,130);

ui_GAP1 = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_GAP1, 170);
lv_obj_set_height( ui_GAP1, 5);
lv_obj_set_x( ui_GAP1, 0 );
lv_obj_set_y( ui_GAP1, -30 );
lv_obj_set_align( ui_GAP1, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_GAP1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_GAP1, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_GAP1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_GAP2 = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_GAP2, 170);
lv_obj_set_height( ui_GAP2, 5);
lv_obj_set_x( ui_GAP2, 0 );
lv_obj_set_y( ui_GAP2, 68 );
lv_obj_set_align( ui_GAP2, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_GAP2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_GAP2, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_GAP2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_HumidityLabel = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_HumidityLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_HumidityLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_HumidityLabel, 0 );
lv_obj_set_y( ui_HumidityLabel, 41 );
lv_obj_set_align( ui_HumidityLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_HumidityLabel,"45");
lv_obj_set_style_text_color(ui_HumidityLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_HumidityLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_HumidityLabel, &ui_font_Interbold40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_HumidityIcon = lv_img_create(ui_MainScreen);
lv_img_set_src(ui_HumidityIcon, &ui_img_droplet_png);
lv_obj_set_width( ui_HumidityIcon, LV_SIZE_CONTENT);  /// 100
lv_obj_set_height( ui_HumidityIcon, LV_SIZE_CONTENT);   /// 100
lv_obj_set_x( ui_HumidityIcon, 1 );
lv_obj_set_y( ui_HumidityIcon, -3 );
lv_obj_set_align( ui_HumidityIcon, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_HumidityIcon, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_HumidityIcon, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_img_set_zoom(ui_HumidityIcon,130);

ui_CO2Label = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_CO2Label, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CO2Label, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CO2Label, 0 );
lv_obj_set_y( ui_CO2Label, 135 );
lv_obj_set_align( ui_CO2Label, LV_ALIGN_CENTER );
lv_label_set_text(ui_CO2Label,"1000");
lv_obj_set_style_text_color(ui_CO2Label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_CO2Label, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_CO2Label, &ui_font_Interbold40, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CO2Icon = lv_imgbtn_create(ui_MainScreen);
lv_imgbtn_set_src(ui_CO2Icon, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_co2_resize_png, NULL);
lv_imgbtn_set_src(ui_CO2Icon, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_co2_resize_png, NULL);
lv_obj_set_width( ui_CO2Icon, 83);
lv_obj_set_height( ui_CO2Icon, 46);
lv_obj_set_x( ui_CO2Icon, 1 );
lv_obj_set_y( ui_CO2Icon, 92 );
lv_obj_set_align( ui_CO2Icon, LV_ALIGN_CENTER );

ui_GAP3 = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_GAP3, 170);
lv_obj_set_height( ui_GAP3, 5);
lv_obj_set_x( ui_GAP3, 0 );
lv_obj_set_y( ui_GAP3, -126 );
lv_obj_set_align( ui_GAP3, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_GAP3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_GAP3, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_GAP3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_BatLabel = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_BatLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_BatLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_BatLabel, 0 );
lv_obj_set_y( ui_BatLabel, -144 );
lv_obj_set_align( ui_BatLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_BatLabel,"Battery:");
lv_obj_set_style_text_color(ui_BatLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_BatLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_BatLabel, &lv_font_montserrat_26, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_CO2Icon, ui_event_CO2Icon, LV_EVENT_ALL, NULL);

}
