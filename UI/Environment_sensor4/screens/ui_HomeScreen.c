// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: Environment_sensor

#include "../ui.h"

void ui_HomeScreen_screen_init(void)
{
    ui_HomeScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_HomeScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_HomeScreen, &ui_img_main_screen_gradient_png, LV_PART_MAIN | LV_STATE_DEFAULT);

}
