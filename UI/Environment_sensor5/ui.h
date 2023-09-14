// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: Environment_sensor

#ifndef _ENVIRONMENT_SENSOR_UI_H
#define _ENVIRONMENT_SENSOR_UI_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "lvgl/lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_MainScreen
void ui_MainScreen_screen_init(void);
extern lv_obj_t *ui_MainScreen;
extern lv_obj_t *ui_TempLabel;
extern lv_obj_t *ui_TempIcon;
extern lv_obj_t *ui_GAP1;
extern lv_obj_t *ui_GAP2;
extern lv_obj_t *ui_HumidityLabel;
extern lv_obj_t *ui_HumidityIcon;
extern lv_obj_t *ui_CO2Icon;
extern lv_obj_t *ui_CO2Label;
extern lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE( ui_img_light_blue_dithered_rotated_png);   // assets\light_blue_dithered_rotated.png
LV_IMG_DECLARE( ui_img_thermometer_png);   // assets\Thermometer.png
LV_IMG_DECLARE( ui_img_droplet_png);   // assets\Droplet.png
LV_IMG_DECLARE( ui_img_co2_png);   // assets\CO2.png

LV_FONT_DECLARE( ui_font_Interbold52);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
