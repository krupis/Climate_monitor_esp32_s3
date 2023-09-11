#ifndef LVGL_WATER_DROPLET_H
#define LVGL_WATER_DROPLET_H

#include "lvgl.h"
#include "lvgl_setup.h"

void ui_Mainscreen_screen_init(void);
void Display_main();
void set_temperature(float temperature);
void set_co2(int16_t co2);
void set_humidity(float humidity);
void Update_temp_humidity(void* arg);


void ui_HomeScreen_screen_init(void);
void Display_home_screen(void);
void display_widgets();




void ui_MainMenu_screen_init(void);
void ui_SettingsScreen_screen_init(void);
void ui_PasswordScreen_screen_init(void);
void ui_init(void);

#endif