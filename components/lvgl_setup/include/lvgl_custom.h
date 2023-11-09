#ifndef LVGL_CUSTOM_H
#define LVGL_CUSTOM_H

#include "lvgl.h"
#include "lvgl_setup.h"


void set_temperature(float temperature);
void set_co2(int16_t co2);
void set_humidity(float humidity);
void set_battery_voltage(float battery_voltage);
void Update_temp_humidity(void* arg);



void ui_init(void);




#endif