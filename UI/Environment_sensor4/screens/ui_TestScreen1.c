// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.6
// Project name: Environment_sensor

#include "../ui.h"

void ui_TestScreen1_screen_init(void)
{
    ui_TestScreen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_TestScreen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_TestScreen1, &ui_img_green_blue_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_TestScreen1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -133);
    lv_obj_set_y(ui_Label1, -62);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

}
