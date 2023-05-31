#include <stdio.h>

#include "esp_log.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ui_helpers.h"
#include "lvgl.h"
#include "lvgl_water_droplet.h"

void ui_Screen2_screen_init(void);

lv_obj_t *ui_Screen2;
lv_obj_t *ui_Panel1;
lv_obj_t *ui_Water;
lv_obj_t *ui_Droplet;
lv_obj_t *ui_Panel2;
lv_obj_t *ui_Thermometer_fill;
lv_obj_t *ui_Thermometer;
lv_obj_t *ui_Temperature_label;
lv_obj_t *ui_Humidity_label;
lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE(droplet)
LV_IMG_DECLARE(thermometer_fill)
LV_IMG_DECLARE(thermometer)
LV_IMG_DECLARE(water)

void Moving_water_Animation(lv_obj_t *TargetObject, int delay)
{
    ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 3000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 50, -50);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 200);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 3000);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 200);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);
    ui_anim_user_data_t *PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_1_user_data->target = TargetObject;
    PropertyAnimation_1_user_data->val = -1;
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 1200);
    lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_1, -40, 30);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 100);
    lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_1, 1200);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 100);
    lv_anim_set_repeat_count(&PropertyAnimation_1, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, false);
    lv_anim_start(&PropertyAnimation_1);
}

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Screen2, lv_color_hex(0xFF7F27), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel1 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel1, 94);
    lv_obj_set_height(ui_Panel1, 127);
    lv_obj_set_x(ui_Panel1, 69);
    lv_obj_set_y(ui_Panel1, 14);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Water = lv_img_create(ui_Panel1);
    lv_img_set_src(ui_Water, &water);
    lv_obj_set_width(ui_Water, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Water, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Water, 50);
    lv_obj_set_y(ui_Water, 76);
    lv_obj_set_align(ui_Water, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Water, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Water, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_angle(ui_Water, -5);

    ui_Droplet = lv_img_create(ui_Panel1);
    lv_img_set_src(ui_Droplet, &droplet);
    lv_obj_set_width(ui_Droplet, LV_SIZE_CONTENT);  /// 100
    lv_obj_set_height(ui_Droplet, LV_SIZE_CONTENT); /// 100
    lv_obj_set_x(ui_Droplet, 2);
    lv_obj_set_y(ui_Droplet, 1);
    lv_obj_set_align(ui_Droplet, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Droplet, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Droplet, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Panel2 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel2, 115);
    lv_obj_set_height(ui_Panel2, 120);
    lv_obj_set_x(ui_Panel2, -86);
    lv_obj_set_y(ui_Panel2, 15);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Thermometer_fill = lv_img_create(ui_Panel2);
    lv_img_set_src(ui_Thermometer_fill, &thermometer_fill);
    lv_obj_set_width(ui_Thermometer_fill, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Thermometer_fill, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Thermometer_fill, -6);
    lv_obj_set_y(ui_Thermometer_fill, 32);
    lv_obj_set_align(ui_Thermometer_fill, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Thermometer_fill, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Thermometer_fill, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Thermometer = lv_img_create(ui_Panel2);
    lv_img_set_src(ui_Thermometer, &thermometer);
    lv_obj_set_width(ui_Thermometer, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Thermometer, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Thermometer, 1);
    lv_obj_set_y(ui_Thermometer, 0);
    lv_obj_set_align(ui_Thermometer, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Thermometer, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Thermometer, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Temperature_label = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_Temperature_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Temperature_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Temperature_label, -95);
    lv_obj_set_y(ui_Temperature_label, -60);
    lv_obj_set_align(ui_Temperature_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Temperature_label, "Temperature:");

    ui_Humidity_label = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_Humidity_label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Humidity_label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Humidity_label, 66);
    lv_obj_set_y(ui_Humidity_label, -60);
    lv_obj_set_align(ui_Humidity_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Humidity_label, "Humidity:");

    Moving_water_Animation(ui_Water, 0);
}

void Create_main_display(void)
{
    // LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen2_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen2);
}

void Move_water_up_down(lv_obj_t *TargetObject, int delay, uint16_t start, uint16_t end)
{
    ui_anim_user_data_t *PropertyAnimation_2_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_2_user_data->target = TargetObject;
    PropertyAnimation_2_user_data->val = -1;
    lv_anim_t PropertyAnimation_2;
    lv_anim_init(&PropertyAnimation_2);
    lv_anim_set_time(&PropertyAnimation_2, 3000);
    lv_anim_set_user_data(&PropertyAnimation_2, PropertyAnimation_2_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_2, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_2, start, end);
    lv_anim_set_path_cb(&PropertyAnimation_2, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_2, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_2, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_2, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_2, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_2, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_2, 0);
    lv_anim_set_early_apply(&PropertyAnimation_2, false);
    lv_anim_start(&PropertyAnimation_2);
}