#ifndef LVGL_WATER_DROPLET_H
#define LVGL_WATER_DROPLET_H

#include "lvgl.h"

void ui_Screen2_screen_init(void);
void Moving_water_Animation(lv_obj_t * TargetObject, int delay);
void Create_main_display(void);
void Move_water_up_down(lv_obj_t * TargetObject, int delay,uint16_t start,uint16_t end);
#endif