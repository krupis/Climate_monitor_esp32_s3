#ifndef LVGL_WATER_DROPLET_H
#define LVGL_WATER_DROPLET_H

#include "lvgl.h"
#include "lvgl_setup.h"

void ui_Mainscreen_screen_init(void);
void Display_main();
void set_temperature(float temperature);
void Update_temp_humidity(void* arg);

#endif