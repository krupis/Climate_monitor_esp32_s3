// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: Environment_sensor

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_MainScreen
void ui_MainScreen_screen_init(void);
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

// SCREEN: ui_TemperatureScreen
void ui_TemperatureScreen_screen_init(void);
lv_obj_t * ui_TemperatureScreen;
lv_obj_t * ui_TemperatureLabel1;
lv_obj_t * ui_ThermometerIcon;
lv_obj_t * ui_TempValue;
lv_obj_t * ui_HomeIcon;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Image1;
lv_obj_t * ui_ThermometerIcon1;

// SCREEN: ui_TemperatureScreen1
void ui_TemperatureScreen1_screen_init(void);
lv_obj_t * ui_TemperatureScreen1;
lv_obj_t * ui_TemperatureLabel2;
lv_obj_t * ui_ThermometerIcon2;
lv_obj_t * ui_TempValue1;
lv_obj_t * ui_HomeIcon1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Image2;
lv_obj_t * ui_ThermometerIcon3;

// SCREEN: ui_TemperatureScreen2
void ui_TemperatureScreen2_screen_init(void);
lv_obj_t * ui_TemperatureScreen2;
lv_obj_t * ui_TemperatureLabel3;
lv_obj_t * ui_ThermometerIcon4;
lv_obj_t * ui_TempValue2;
lv_obj_t * ui_HomeIcon2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Image3;
lv_obj_t * ui_ThermometerIcon5;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_blue_yellow_red[1] = {&ui_img_blue_yellow_red2_png};
const lv_img_dsc_t * ui_imgset_co[1] = {&ui_img_co2_png};
const lv_img_dsc_t * ui_imgset_dithered[1] = {&ui_img_dithered1_png};
const lv_img_dsc_t * ui_imgset_main_screen_gradient[2] = {&ui_img_main_screen_gradient2_png, &ui_img_main_screen_gradient3_png};
const lv_img_dsc_t * ui_imgset_thermometer[1] = {&ui_img_thermometer2_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_MainScreen_screen_init();
    ui_TemperatureScreen_screen_init();
    ui_TemperatureScreen1_screen_init();
    ui_TemperatureScreen2_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_MainScreen);
}
