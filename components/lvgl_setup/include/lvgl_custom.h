#ifndef LVGL_CUSTOM_H
#define LVGL_CUSTOM_H

#include "lvgl.h"
#include "lvgl_setup.h"


void set_temperature(float temperature);
void set_co2(int16_t co2);
void set_humidity(float humidity);
void set_battery_voltage(float battery_voltage);
void Update_temp_humidity(void* arg);
void set_point_temperature(float temperature);
void set_ambient_temperature(float temperature);





void Update_point_temperature(void *arg);
void Update_ambient_temperature(void *arg);







#endif