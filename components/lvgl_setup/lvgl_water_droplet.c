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

lv_obj_t *main_screen;
lv_obj_t *droplet_image;
lv_obj_t *humidity_label;

static lv_style_t style_btn;
static lv_style_t style_btn_pressed;
static lv_style_t style_btn_red;

static lv_color_t darken(const lv_color_filter_dsc_t * dsc, lv_color_t color, lv_opa_t opa)
{
    LV_UNUSED(dsc);
    return lv_color_darken(color, opa);
}

LV_IMG_DECLARE(droplet_transparent)
LV_IMG_DECLARE(droplet2)

static void style_init(void)
{
    /*Create a simple button style*/



    
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 10);
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn, lv_palette_lighten(LV_PALETTE_GREY, 3));
    lv_style_set_bg_grad_color(&style_btn, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_grad_dir(&style_btn, LV_GRAD_DIR_VER);

    lv_style_set_border_color(&style_btn, lv_color_black());
    lv_style_set_border_opa(&style_btn, LV_OPA_20);
    lv_style_set_border_width(&style_btn, 2);

    lv_style_set_text_color(&style_btn, lv_color_black());

    /*Create a style for the pressed state.
     *Use a color filter to simply modify all colors in this state*/
    static lv_color_filter_dsc_t color_filter;
    lv_color_filter_dsc_init(&color_filter, darken);
    lv_style_init(&style_btn_pressed);
    lv_style_set_color_filter_dsc(&style_btn_pressed, &color_filter);
    lv_style_set_color_filter_opa(&style_btn_pressed, LV_OPA_20);

    /*Create a red style. Change only some colors.*/
    lv_style_init(&style_btn_red);
    lv_style_set_bg_color(&style_btn_red, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&style_btn_red, lv_palette_lighten(LV_PALETTE_RED, 3));
}



void display_transparent_water_droplet(void)
{
    main_screen = lv_obj_create(NULL);
    lv_obj_clear_flag(main_screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags





    //START OF BUTTON TEST
    //style_init();
    //lv_obj_t * btn = lv_btn_create(main_screen);
    // lv_obj_remove_style_all(btn);
    // lv_obj_set_pos(btn, 10, 10);
    // lv_obj_set_size(btn, 120, 50);
    // lv_obj_add_style(btn, &style_btn, 0);
    // lv_obj_add_style(btn, &style_btn_pressed, LV_STATE_PRESSED);

    //     /*Add a label to the button*/
    // lv_obj_t * label = lv_label_create(btn);
    // lv_label_set_text(label, "Button");
    // lv_obj_center(label);
    //END OF BUTTON TEST

    static lv_style_t style;
    lv_style_init(&style);

    /*Set a background color and a radius*/
    //lv_style_set_radius(&style, 5);
    //lv_style_set_bg_opa(&style, LV_OPA_COVER);
    //lv_style_set_bg_color(&style, lv_palette_lighten(LV_PALETTE_GREY, 3));
    //lv_style_set_border_width(&style, 2);
    //lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_img_recolor(&style, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_img_recolor_opa(&style, LV_OPA_90);
    //lv_style_set_transform_angle(&style, 300);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_img_create(main_screen);
    lv_obj_add_style(obj, &style, 0);


    lv_img_set_src(obj, &droplet2);

    lv_obj_center(obj);



    // droplet_image = lv_img_create(main_screen);
    // lv_img_set_src(droplet_image, &droplet_transparent);
    // lv_obj_set_width(droplet_image, LV_SIZE_CONTENT);  /// 1
    // lv_obj_set_height(droplet_image, LV_SIZE_CONTENT); /// 1
    // lv_obj_set_align(droplet_image, LV_ALIGN_CENTER);
    // lv_obj_add_flag(droplet_image, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    // lv_obj_clear_flag(droplet_image, LV_OBJ_FLAG_SCROLLABLE); /// Flags


    // humidity_label = lv_label_create(main_screen);
    // lv_obj_set_width(humidity_label, LV_SIZE_CONTENT);  /// 1
    // lv_obj_set_height(humidity_label, LV_SIZE_CONTENT); /// 1
    // lv_obj_set_x(humidity_label, -1);
    // lv_obj_set_y(humidity_label, -65);
    // lv_obj_set_align(humidity_label, LV_ALIGN_CENTER);
    // lv_label_set_text(humidity_label, "Humidity");

    lv_disp_load_scr(main_screen);
}