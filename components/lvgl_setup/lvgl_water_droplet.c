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



LV_IMG_DECLARE(Main_screen_gradient_dithered_png)
LV_IMG_DECLARE(Main_screen_gradient3_png)
LV_IMG_DECLARE(Yellow_dithered_png)



LV_IMG_DECLARE(Home_png)
LV_IMG_DECLARE(Menu_png)
LV_IMG_DECLARE(Thermometer2_png)


// SCREEN: ui_TemperatureScreen
void ui_TemperatureScreen_screen_init(void);
lv_obj_t * ui_TemperatureScreen;
lv_obj_t * ui_TemperatureLabel1;
lv_obj_t * ui_ThermometerIcon;
lv_obj_t * ui_TempValue;
lv_obj_t * ui_HomeIcon;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Image1;
lv_obj_t * ui_ThermometerIcon1;

// SCREEN: ui_TemperatureScreen1
void ui_TemperatureScreen1_screen_init(void);
lv_obj_t * ui_TemperatureScreen1;
lv_obj_t * ui_TemperatureLabel2;
lv_obj_t * ui_ThermometerIcon2;
lv_obj_t * ui_TempValue1;
lv_obj_t * ui_HomeIcon1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Image2;
lv_obj_t * ui_ThermometerIcon3;

// SCREEN: ui_TemperatureScreen2
void ui_TemperatureScreen2_screen_init(void);
lv_obj_t * ui_TemperatureScreen2;
lv_obj_t * ui_TemperatureLabel3;
lv_obj_t * ui_ThermometerIcon4;
lv_obj_t * ui_TempValue2;
lv_obj_t * ui_HomeIcon2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Image3;
lv_obj_t * ui_ThermometerIcon5;










extern QueueHandle_t update_queue;



void set_temperature(float temperature)
{
    // char float_temp_buf[8];
    // char final_temp_buf[10];
    // sprintf(float_temp_buf, "%.1f", temperature); // make the number into string using sprintf function
    // final_temp_buf[0] = '\0';
    // strcat(final_temp_buf, "+");
    // strcat(final_temp_buf, float_temp_buf);
    // strcat(final_temp_buf, "°");
    // lv_label_set_text(ui_TemperatureLabel, final_temp_buf);
    // lv_arc_set_value(ui_TemperatureArc, (int16_t)(temperature));
}

void set_humidity(float humidity)
{
    // char temp_buf[8];
    // sprintf(temp_buf, "%.1f", humidity); // make the number into string using sprintf function
    // strcat(temp_buf, "%");
    // lv_label_set_text(ui_DropletLabel, temp_buf);
    // lv_arc_set_value(ui_HumidityArc, (int16_t)(humidity));
}




 // lv_disp_set_rotation(dispp, LV_DISP_ROT_270);

 

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













void ui_TemperatureScreen2_screen_init(void)
{
    ui_TemperatureScreen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_TemperatureScreen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_TemperatureScreen2, &Yellow_dithered_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureLabel3 = lv_label_create(ui_TemperatureScreen2);
    lv_obj_set_width(ui_TemperatureLabel3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureLabel3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TemperatureLabel3, 52);
    lv_obj_set_y(ui_TemperatureLabel3, -59);
    lv_obj_set_align(ui_TemperatureLabel3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TemperatureLabel3, "Temperature");
    lv_obj_set_style_text_color(ui_TemperatureLabel3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TemperatureLabel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureLabel3, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ThermometerIcon4 = lv_img_create(ui_TemperatureScreen2);
    lv_img_set_src(ui_ThermometerIcon4, &Thermometer2_png);
    lv_obj_set_width(ui_ThermometerIcon4, LV_SIZE_CONTENT);   /// 106
    lv_obj_set_height(ui_ThermometerIcon4, LV_SIZE_CONTENT);    /// 102
    lv_obj_set_x(ui_ThermometerIcon4, 15);
    lv_obj_set_y(ui_ThermometerIcon4, 29);
    lv_obj_set_align(ui_ThermometerIcon4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ThermometerIcon4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ThermometerIcon4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TempValue2 = lv_label_create(ui_TemperatureScreen2);
    lv_obj_set_width(ui_TempValue2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TempValue2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TempValue2, -107);
    lv_obj_set_y(ui_TempValue2, 11);
    lv_obj_set_align(ui_TempValue2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TempValue2, "+25");
    lv_obj_set_style_text_color(ui_TempValue2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TempValue2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TempValue2, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HomeIcon2 = lv_img_create(ui_TemperatureScreen2);
    lv_img_set_src(ui_HomeIcon2, &Home_png);
    lv_obj_set_width(ui_HomeIcon2, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_HomeIcon2, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_HomeIcon2, 106);
    lv_obj_set_y(ui_HomeIcon2, 28);
    lv_obj_set_align(ui_HomeIcon2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_HomeIcon2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_HomeIcon2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label3 = lv_label_create(ui_TemperatureScreen2);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, -87);
    lv_obj_set_y(ui_Label3, 57);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "Indoor");
    lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image3 = lv_img_create(ui_TemperatureScreen2);
    lv_img_set_src(ui_Image3, &Menu_png);
    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image3, -116);
    lv_obj_set_y(ui_Image3, -54);
    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ThermometerIcon5 = lv_img_create(ui_TemperatureScreen2);
    lv_img_set_src(ui_ThermometerIcon5, &Thermometer2_png);
    lv_obj_set_width(ui_ThermometerIcon5, LV_SIZE_CONTENT);   /// 106
    lv_obj_set_height(ui_ThermometerIcon5, LV_SIZE_CONTENT);    /// 102
    lv_obj_set_x(ui_ThermometerIcon5, 15);
    lv_obj_set_y(ui_ThermometerIcon5, 29);
    lv_obj_set_align(ui_ThermometerIcon5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ThermometerIcon5, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ThermometerIcon5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}






void ui_TemperatureScreen1_screen_init(void)
{
    ui_TemperatureScreen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_TemperatureScreen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_TemperatureScreen1, &Main_screen_gradient3_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureLabel2 = lv_label_create(ui_TemperatureScreen1);
    lv_obj_set_width(ui_TemperatureLabel2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureLabel2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TemperatureLabel2, 52);
    lv_obj_set_y(ui_TemperatureLabel2, -59);
    lv_obj_set_align(ui_TemperatureLabel2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TemperatureLabel2, "Temperature");
    lv_obj_set_style_text_color(ui_TemperatureLabel2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TemperatureLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureLabel2, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ThermometerIcon2 = lv_img_create(ui_TemperatureScreen1);
    lv_img_set_src(ui_ThermometerIcon2, &Thermometer2_png);
    lv_obj_set_width(ui_ThermometerIcon2, LV_SIZE_CONTENT);   /// 106
    lv_obj_set_height(ui_ThermometerIcon2, LV_SIZE_CONTENT);    /// 102
    lv_obj_set_x(ui_ThermometerIcon2, 15);
    lv_obj_set_y(ui_ThermometerIcon2, 29);
    lv_obj_set_align(ui_ThermometerIcon2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ThermometerIcon2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ThermometerIcon2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TempValue1 = lv_label_create(ui_TemperatureScreen1);
    lv_obj_set_width(ui_TempValue1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TempValue1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TempValue1, -107);
    lv_obj_set_y(ui_TempValue1, 11);
    lv_obj_set_align(ui_TempValue1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TempValue1, "+25");
    lv_obj_set_style_text_color(ui_TempValue1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TempValue1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TempValue1, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HomeIcon1 = lv_img_create(ui_TemperatureScreen1);
    lv_img_set_src(ui_HomeIcon1, &Home_png);
    lv_obj_set_width(ui_HomeIcon1, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_HomeIcon1, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_HomeIcon1, 106);
    lv_obj_set_y(ui_HomeIcon1, 28);
    lv_obj_set_align(ui_HomeIcon1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_HomeIcon1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_HomeIcon1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label2 = lv_label_create(ui_TemperatureScreen1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, -87);
    lv_obj_set_y(ui_Label2, 57);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Indoor");
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image2 = lv_img_create(ui_TemperatureScreen1);
    lv_img_set_src(ui_Image2, &Menu_png);
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image2, -116);
    lv_obj_set_y(ui_Image2, -54);
    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ThermometerIcon3 = lv_img_create(ui_TemperatureScreen1);
    lv_img_set_src(ui_ThermometerIcon3, &Thermometer2_png);
    lv_obj_set_width(ui_ThermometerIcon3, LV_SIZE_CONTENT);   /// 106
    lv_obj_set_height(ui_ThermometerIcon3, LV_SIZE_CONTENT);    /// 102
    lv_obj_set_x(ui_ThermometerIcon3, 15);
    lv_obj_set_y(ui_ThermometerIcon3, 29);
    lv_obj_set_align(ui_ThermometerIcon3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ThermometerIcon3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ThermometerIcon3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}

void ui_TemperatureScreen_screen_init(void)
{
    ui_TemperatureScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_TemperatureScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_TemperatureScreen, &Main_screen_gradient_dithered_png,
                                LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TemperatureLabel1 = lv_label_create(ui_TemperatureScreen);
    lv_obj_set_width(ui_TemperatureLabel1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TemperatureLabel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TemperatureLabel1, 52);
    lv_obj_set_y(ui_TemperatureLabel1, -59);
    lv_obj_set_align(ui_TemperatureLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TemperatureLabel1, "Temperature");
    lv_obj_set_style_text_color(ui_TemperatureLabel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TemperatureLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TemperatureLabel1, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ThermometerIcon = lv_img_create(ui_TemperatureScreen);
    lv_img_set_src(ui_ThermometerIcon, &Thermometer2_png);
    lv_obj_set_width(ui_ThermometerIcon, LV_SIZE_CONTENT);   /// 106
    lv_obj_set_height(ui_ThermometerIcon, LV_SIZE_CONTENT);    /// 102
    lv_obj_set_x(ui_ThermometerIcon, 15);
    lv_obj_set_y(ui_ThermometerIcon, 29);
    lv_obj_set_align(ui_ThermometerIcon, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ThermometerIcon, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ThermometerIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TempValue = lv_label_create(ui_TemperatureScreen);
    lv_obj_set_width(ui_TempValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TempValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_TempValue, -107);
    lv_obj_set_y(ui_TempValue, 11);
    lv_obj_set_align(ui_TempValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TempValue, "+25");
    lv_obj_set_style_text_color(ui_TempValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TempValue, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TempValue, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HomeIcon = lv_img_create(ui_TemperatureScreen);
    lv_img_set_src(ui_HomeIcon, &Home_png);
    lv_obj_set_width(ui_HomeIcon, LV_SIZE_CONTENT);   /// 100
    lv_obj_set_height(ui_HomeIcon, LV_SIZE_CONTENT);    /// 100
    lv_obj_set_x(ui_HomeIcon, 106);
    lv_obj_set_y(ui_HomeIcon, 28);
    lv_obj_set_align(ui_HomeIcon, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_HomeIcon, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_HomeIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label1 = lv_label_create(ui_TemperatureScreen);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -87);
    lv_obj_set_y(ui_Label1, 57);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Indoor");
    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image1 = lv_img_create(ui_TemperatureScreen);
    lv_img_set_src(ui_Image1, &Menu_png);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image1, -116);
    lv_obj_set_y(ui_Image1, -54);
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ThermometerIcon1 = lv_img_create(ui_TemperatureScreen);
    lv_img_set_src(ui_ThermometerIcon1, &Thermometer2_png);
    lv_obj_set_width(ui_ThermometerIcon1, LV_SIZE_CONTENT);   /// 106
    lv_obj_set_height(ui_ThermometerIcon1, LV_SIZE_CONTENT);    /// 102
    lv_obj_set_x(ui_ThermometerIcon1, 15);
    lv_obj_set_y(ui_ThermometerIcon1, 29);
    lv_obj_set_align(ui_ThermometerIcon1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ThermometerIcon1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ThermometerIcon1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}


void display_widgets(){
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_TemperatureScreen_screen_init();
     ui_TemperatureScreen1_screen_init();
     ui_TemperatureScreen2_screen_init();
    //ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_TemperatureScreen2);
}