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
#include "SHT40.h"

// SCREEN: ui_MainScreen
void ui_MainScreen_screen_init(void);
lv_obj_t *ui_MainScreen;
lv_obj_t *ui_TempLabel;
lv_obj_t *ui_TempIcon;
lv_obj_t *ui_GAP1;
lv_obj_t *ui_GAP2;
lv_obj_t *ui_HumidityLabel;
lv_obj_t *ui_HumidityIcon;
lv_obj_t *ui_CO2Label;
void ui_event_CO2Icon(lv_event_t *e);
lv_obj_t *ui_CO2Icon;
lv_obj_t *ui_GAP3;

// SCREEN: ui_CalibrationScreen
void ui_CalibrationScreen_screen_init(void);
lv_obj_t *ui_CalibrationScreen;
lv_obj_t *ui_CalibrateLabel;
void ui_event_CalibrateButton(lv_event_t *e);
lv_obj_t *ui_CalibrateButton;
void ui_event_BackButton1(lv_event_t *e);
lv_obj_t *ui_BackButton1;
lv_obj_t *ui_BackLabel1;

// SCREEN: ui_ConfirmationScreen
void ui_ConfirmationScreen_screen_init(void);
lv_obj_t *ui_ConfirmationScreen;
lv_obj_t *ui_CalibrateInfo;
void ui_event_CalibrateStart(lv_event_t *e);
lv_obj_t *ui_CalibrateStart;
lv_obj_t *ui_StartLabel;
void ui_event_UpdateProgress(lv_event_t *e);
lv_obj_t *ui_UpdateProgress;
void ui_event_BackButton2(lv_event_t *e);
lv_obj_t *ui_BackButton2;
lv_obj_t *ui_BackLabel2;
lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE(light_blue_png)  // HumidityScreen
LV_IMG_DECLARE(CO2_png)         // HumidityScreen
LV_IMG_DECLARE(CO2_resize_png)  // HumidityScreen
LV_IMG_DECLARE(Thermometer_png) // HumidityScreen
LV_IMG_DECLARE(Droplet_png)     // HumidityScreen
LV_IMG_DECLARE(Calibrate_png)   // HumidityScreen

LV_FONT_DECLARE(ui_font_Interbold52);

static void set_update_progress_value(void *indic, int32_t v);

extern QueueHandle_t update_queue;

void set_temperature(float temperature)
{
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%.1f", temperature); // make the number into string using sprintf function
    final_temp_buf[0] = '\0';
    strcat(final_temp_buf, "+");
    strcat(final_temp_buf, float_temp_buf);
    strcat(final_temp_buf, "°");
    lv_label_set_text(ui_TempLabel, final_temp_buf);
}

void set_humidity(float humidity)
{
    char temp_buf[8];
    sprintf(temp_buf, "%.1f", humidity); // make the number into string using sprintf function
    strcat(temp_buf, "%");
    lv_label_set_text(ui_HumidityLabel, temp_buf);
}

void set_co2(int16_t co2)
{
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%u", co2); // make the number into string using sprintf function
    lv_label_set_text(ui_CO2Label, float_temp_buf);
}

void Update_temp_humidity(void *arg)
{
    struct sht40_reading_s local_sht40;
    struct sht40_reading_s average_sht40;
    static uint8_t avg_counter = 0;

    for (;;)
    {
        if (xQueueReceive(update_queue, &local_sht40, portMAX_DELAY))
        {
            average_sht40.temperature += local_sht40.temperature;
            average_sht40.humidity += local_sht40.humidity;
            avg_counter++;
            if (avg_counter >= 10)
            {
                local_sht40.temperature = (average_sht40.temperature / avg_counter);
                local_sht40.humidity = (average_sht40.humidity / avg_counter);
                average_sht40.temperature = 0;
                average_sht40.humidity = 0;

                bsp_display_lock(0);
                set_temperature(local_sht40.temperature);
                set_humidity(local_sht40.humidity);
                bsp_display_unlock();
                avg_counter = 0;
            }
        }
    }
}

void ui_MainScreen_screen_init(void)
{
    ui_MainScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_img_src(ui_MainScreen, &light_blue_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TempLabel = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_TempLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_TempLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_TempLabel, 0);
    lv_obj_set_y(ui_TempLabel, -56);
    lv_obj_set_align(ui_TempLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TempLabel, "+20");
    lv_obj_set_style_text_color(ui_TempLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TempLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TempLabel, &ui_font_Interbold52, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TempIcon = lv_img_create(ui_MainScreen);
    lv_img_set_src(ui_TempIcon, &Thermometer_png);
    lv_obj_set_width(ui_TempIcon, LV_SIZE_CONTENT);  /// 106
    lv_obj_set_height(ui_TempIcon, LV_SIZE_CONTENT); /// 102
    lv_obj_set_x(ui_TempIcon, 0);
    lv_obj_set_y(ui_TempIcon, -100);
    lv_obj_set_align(ui_TempIcon, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_TempIcon, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_TempIcon, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(ui_TempIcon, 130);

    ui_GAP1 = lv_obj_create(ui_MainScreen);
    lv_obj_set_width(ui_GAP1, 170);
    lv_obj_set_height(ui_GAP1, 5);
    lv_obj_set_x(ui_GAP1, 0);
    lv_obj_set_y(ui_GAP1, -30);
    lv_obj_set_align(ui_GAP1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_GAP1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_GAP1, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_GAP1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_GAP2 = lv_obj_create(ui_MainScreen);
    lv_obj_set_width(ui_GAP2, 170);
    lv_obj_set_height(ui_GAP2, 5);
    lv_obj_set_x(ui_GAP2, 0);
    lv_obj_set_y(ui_GAP2, 68);
    lv_obj_set_align(ui_GAP2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_GAP2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_GAP2, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_GAP2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HumidityLabel = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_HumidityLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_HumidityLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_HumidityLabel, 0);
    lv_obj_set_y(ui_HumidityLabel, 41);
    lv_obj_set_align(ui_HumidityLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_HumidityLabel, "45");
    lv_obj_set_style_text_color(ui_HumidityLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_HumidityLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_HumidityLabel, &ui_font_Interbold52, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HumidityIcon = lv_img_create(ui_MainScreen);
    lv_img_set_src(ui_HumidityIcon, &Droplet_png);
    lv_obj_set_width(ui_HumidityIcon, LV_SIZE_CONTENT);  /// 100
    lv_obj_set_height(ui_HumidityIcon, LV_SIZE_CONTENT); /// 100
    lv_obj_set_x(ui_HumidityIcon, 1);
    lv_obj_set_y(ui_HumidityIcon, -3);
    lv_obj_set_align(ui_HumidityIcon, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_HumidityIcon, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_HumidityIcon, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(ui_HumidityIcon, 130);

    ui_CO2Label = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_CO2Label, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CO2Label, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CO2Label, 0);
    lv_obj_set_y(ui_CO2Label, 135);
    lv_obj_set_align(ui_CO2Label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CO2Label, "1000");
    lv_obj_set_style_text_color(ui_CO2Label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CO2Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CO2Label, &ui_font_Interbold52, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CO2Icon = lv_imgbtn_create(ui_MainScreen);
    lv_imgbtn_set_src(ui_CO2Icon, LV_IMGBTN_STATE_RELEASED, NULL, &CO2_resize_png, NULL);
    lv_imgbtn_set_src(ui_CO2Icon, LV_IMGBTN_STATE_PRESSED, NULL, &CO2_resize_png, NULL);
    lv_obj_set_width(ui_CO2Icon, 83);
    lv_obj_set_height(ui_CO2Icon, 46);
    lv_obj_set_x(ui_CO2Icon, 1);
    lv_obj_set_y(ui_CO2Icon, 92);
    lv_obj_set_align(ui_CO2Icon, LV_ALIGN_CENTER);

    ui_GAP3 = lv_obj_create(ui_MainScreen);
    lv_obj_set_width(ui_GAP3, 170);
    lv_obj_set_height(ui_GAP3, 5);
    lv_obj_set_x(ui_GAP3, 0);
    lv_obj_set_y(ui_GAP3, -126);
    lv_obj_set_align(ui_GAP3, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_GAP3, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_GAP3, lv_color_hex(0x201388), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_GAP3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_CO2Icon, ui_event_CO2Icon, LV_EVENT_ALL, NULL);
}

void ui_CalibrationScreen_screen_init(void)
{
    ui_CalibrationScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_CalibrationScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_img_src(ui_CalibrationScreen, &light_blue_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalibrateLabel = lv_label_create(ui_CalibrationScreen);
    lv_obj_set_width(ui_CalibrateLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CalibrateLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CalibrateLabel, 0);
    lv_obj_set_y(ui_CalibrateLabel, -48);
    lv_obj_set_align(ui_CalibrateLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CalibrateLabel, "Calibrate CO2");
    lv_obj_set_style_text_color(ui_CalibrateLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CalibrateLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CalibrateLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CalibrateLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalibrateButton = lv_imgbtn_create(ui_CalibrationScreen);
    lv_imgbtn_set_src(ui_CalibrateButton, LV_IMGBTN_STATE_RELEASED, NULL, &Calibrate_png, NULL);
    lv_obj_set_height(ui_CalibrateButton, 80);
    lv_obj_set_width(ui_CalibrateButton, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CalibrateButton, 1);
    lv_obj_set_y(ui_CalibrateButton, 23);
    lv_obj_set_align(ui_CalibrateButton, LV_ALIGN_CENTER);

    ui_BackButton1 = lv_btn_create(ui_CalibrationScreen);
    lv_obj_set_width(ui_BackButton1, 120);
    lv_obj_set_height(ui_BackButton1, 50);
    lv_obj_set_x(ui_BackButton1, 0);
    lv_obj_set_y(ui_BackButton1, 130);
    lv_obj_set_align(ui_BackButton1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BackButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_BackButton1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_BackButton1, lv_color_hex(0xD76565), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BackButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BackLabel1 = lv_label_create(ui_CalibrationScreen);
    lv_obj_set_width(ui_BackLabel1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_BackLabel1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_BackLabel1, 0);
    lv_obj_set_y(ui_BackLabel1, 130);
    lv_obj_set_align(ui_BackLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BackLabel1, "BACK");
    lv_obj_set_style_text_color(ui_BackLabel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BackLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BackLabel1, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_CalibrateButton, ui_event_CalibrateButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BackButton1, ui_event_BackButton1, LV_EVENT_ALL, NULL);
}

void ui_ConfirmationScreen_screen_init(void)
{
    ui_ConfirmationScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ConfirmationScreen, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_img_src(ui_ConfirmationScreen, &light_blue_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalibrateInfo = lv_label_create(ui_ConfirmationScreen);
    lv_obj_set_width(ui_CalibrateInfo, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_CalibrateInfo, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_CalibrateInfo, 1);
    lv_obj_set_y(ui_CalibrateInfo, -64);
    lv_obj_set_align(ui_CalibrateInfo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CalibrateInfo, "Calibrate in Fresh air:\nTake device outside\nfor a few minutes");
    lv_obj_set_style_text_color(ui_CalibrateInfo, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CalibrateInfo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CalibrateInfo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CalibrateInfo, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalibrateStart = lv_btn_create(ui_ConfirmationScreen);
    lv_obj_set_width(ui_CalibrateStart, 100);
    lv_obj_set_height(ui_CalibrateStart, 50);
    lv_obj_set_align(ui_CalibrateStart, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CalibrateStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_CalibrateStart, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_CalibrateStart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CalibrateStart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CalibrateStart, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_StartLabel = lv_label_create(ui_ConfirmationScreen);
    lv_obj_set_width(ui_StartLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_StartLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_StartLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_StartLabel, "Calibrate");
    lv_obj_set_style_text_font(ui_StartLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_UpdateProgress = lv_bar_create(ui_ConfirmationScreen);
    lv_obj_set_width(ui_UpdateProgress, 150);
    lv_obj_set_height(ui_UpdateProgress, 20);
    lv_obj_set_x(ui_UpdateProgress, 0);
    lv_obj_set_y(ui_UpdateProgress, 70);
    lv_obj_set_align(ui_UpdateProgress, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_UpdateProgress, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_UpdateProgress, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_anim_time(ui_UpdateProgress, 5000, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_UpdateProgress, lv_color_hex(0x409E3B), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_UpdateProgress, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_BackButton2 = lv_btn_create(ui_ConfirmationScreen);
    lv_obj_set_width(ui_BackButton2, 120);
    lv_obj_set_height(ui_BackButton2, 50);
    lv_obj_set_x(ui_BackButton2, 0);
    lv_obj_set_y(ui_BackButton2, 130);
    lv_obj_set_align(ui_BackButton2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_BackButton2, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_BackButton2, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_BackButton2, lv_color_hex(0xD76565), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BackButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BackLabel2 = lv_label_create(ui_ConfirmationScreen);
    lv_obj_set_width(ui_BackLabel2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_BackLabel2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_BackLabel2, 0);
    lv_obj_set_y(ui_BackLabel2, 130);
    lv_obj_set_align(ui_BackLabel2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BackLabel2, "BACK");
    lv_obj_set_style_text_color(ui_BackLabel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BackLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BackLabel2, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_CalibrateStart, ui_event_CalibrateStart, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_BackButton2, ui_event_BackButton2, LV_EVENT_ALL, NULL);
}

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_MainScreen_screen_init();
    ui_CalibrationScreen_screen_init();
    ui_ConfirmationScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_set_rotation(dispp, LV_DISP_ROT_270);
    lv_disp_load_scr(ui_MainScreen);
}

///////////////////// FUNCTIONS ////////////////////
void ui_event_CO2Icon(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_CalibrationScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CalibrationScreen_screen_init);
    }
}

void ui_event_CalibrateStart(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        //_ui_bar_set_property(ui_UpdateProgress, _UI_BAR_PROPERTY_VALUE_WITH_ANIM, 100);
        printf("start animation \n");
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_exec_cb(&a, set_update_progress_value);
        lv_anim_set_values(&a, 0, 100);
        lv_anim_set_time(&a, 5000);
        lv_anim_set_var(&a, ui_UpdateProgress);
        lv_anim_start(&a);
    }
}

static void set_update_progress_value(void *indic, int32_t v)
{
    lv_bar_set_value(ui_UpdateProgress, indic, v);
}

void ui_event_UpdateProgress(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED)
    {
        int value = lv_bar_get_value(ui_UpdateProgress);
        printf("value = %u \n", value);
    }
}

void ui_event_CalibrateButton(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_ConfirmationScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_ConfirmationScreen_screen_init);
    }
}
void ui_event_BackButton1(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_MainScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_MainScreen_screen_init);
    }
}

void ui_event_BackButton2(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        _ui_screen_change(&ui_MainScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_MainScreen_screen_init);
    }
}
