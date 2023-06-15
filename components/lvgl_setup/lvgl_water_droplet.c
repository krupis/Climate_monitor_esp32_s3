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

void ui_Screen1_screen_init(void);
lv_obj_t *ui_Screen1;
lv_obj_t *ui_paneldroplet;
lv_obj_t *ui_droplet;
lv_obj_t *ui_dropletarc;
lv_obj_t *ui_paneltemperature;
lv_obj_t *ui_thermometerfill;
lv_obj_t *ui_thermometer;
lv_obj_t *ui_temperaturearc;
lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE(droplet)
LV_IMG_DECLARE(thermometer_fill)
LV_IMG_DECLARE(thermometer)

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0xEBF491), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_paneldroplet = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_paneldroplet, 148);
    lv_obj_set_height(ui_paneldroplet, 163);
    lv_obj_set_x(ui_paneldroplet, 82);
    lv_obj_set_y(ui_paneldroplet, 0);
    lv_obj_set_align(ui_paneldroplet, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_paneldroplet, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_paneldroplet, lv_color_hex(0xEBF491), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_paneldroplet, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_paneldroplet, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_paneldroplet, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_droplet = lv_img_create(ui_paneldroplet);
    lv_img_set_src(ui_droplet, &droplet);
    lv_obj_set_width(ui_droplet, LV_SIZE_CONTENT);  /// 100
    lv_obj_set_height(ui_droplet, LV_SIZE_CONTENT); /// 100
    lv_obj_set_x(ui_droplet, 4);
    lv_obj_set_y(ui_droplet, -44);
    lv_obj_set_align(ui_droplet, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_droplet, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_droplet, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(ui_droplet, 150);


    // ui_paneltemperature = lv_obj_create(ui_Screen1);
    // lv_obj_set_width(ui_paneltemperature, 141);
    // lv_obj_set_height(ui_paneltemperature, 162);
    // lv_obj_set_x(ui_paneltemperature, -87);
    // lv_obj_set_y(ui_paneltemperature, 0);
    // lv_obj_set_align(ui_paneltemperature, LV_ALIGN_CENTER);
    // lv_obj_clear_flag(ui_paneltemperature, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    // lv_obj_set_style_bg_color(ui_paneltemperature, lv_color_hex(0xEBF491), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui_paneltemperature, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_color(ui_paneltemperature, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_opa(ui_paneltemperature, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_thermometerfill = lv_obj_create(ui_paneltemperature);
    // lv_obj_set_width(ui_thermometerfill, 11);
    // lv_obj_set_height(ui_thermometerfill, 56);
    // lv_obj_set_x(ui_thermometerfill, 5);
    // lv_obj_set_y(ui_thermometerfill, -42);
    // lv_obj_set_align(ui_thermometerfill, LV_ALIGN_CENTER);
    // lv_obj_clear_flag(ui_thermometerfill, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    // lv_obj_set_style_bg_img_src(ui_thermometerfill, &thermometer_fill, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_color(ui_thermometerfill, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_opa(ui_thermometerfill, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_thermometer = lv_img_create(ui_paneltemperature);
    // lv_img_set_src(ui_thermometer, &thermometer);
    // lv_obj_set_width(ui_thermometer, LV_SIZE_CONTENT);  /// 1
    // lv_obj_set_height(ui_thermometer, LV_SIZE_CONTENT); /// 1
    // lv_obj_set_x(ui_thermometer, 6);
    // lv_obj_set_y(ui_thermometer, -43);
    // lv_obj_set_align(ui_thermometer, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_thermometer, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    // lv_obj_clear_flag(ui_thermometer, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    // lv_img_set_zoom(ui_thermometer, 150);

    // ui_temperaturearc = lv_arc_create(ui_paneltemperature);
    // lv_obj_set_width(ui_temperaturearc, 60);
    // lv_obj_set_height(ui_temperaturearc, 60);
    // lv_obj_set_x(ui_temperaturearc, 5);
    // lv_obj_set_y(ui_temperaturearc, 49);
    // lv_obj_set_align(ui_temperaturearc, LV_ALIGN_CENTER);
}

void Create_main_display(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
