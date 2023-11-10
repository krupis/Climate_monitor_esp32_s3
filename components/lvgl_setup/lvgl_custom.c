#include <stdio.h>

#include "esp_log.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lvgl.h"
#include "lvgl_custom.h"
#include "SHT40.h"





extern QueueHandle_t update_queue;
extern QueueHandle_t update_queue_point_temperature;
extern QueueHandle_t update_queue_ambient_temperature;
extern lv_obj_t *ui_BatLabel1;
extern lv_obj_t *ui_TempLabel1;
extern lv_obj_t *ui_ObjectTempLabel;
extern lv_obj_t *ui_AmbientTempLabel;
extern lv_obj_t *ui_HumidityLabel1;
extern lv_obj_t *ui_CO2Label1;




void set_point_temperature(float temperature)
{
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%.1f", temperature); // make the number into string using sprintf function
    final_temp_buf[0] = '\0';
    strcat(final_temp_buf, "+");
    strcat(final_temp_buf, float_temp_buf);
    strcat(final_temp_buf, "°");
    lv_label_set_text(ui_ObjectTempLabel, final_temp_buf);
}


void set_ambient_temperature(float temperature)
{
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%.1f", temperature); // make the number into string using sprintf function
    final_temp_buf[0] = '\0';
    strcat(final_temp_buf, "+");
    strcat(final_temp_buf, float_temp_buf);
    strcat(final_temp_buf, "°");
    lv_label_set_text(ui_AmbientTempLabel, final_temp_buf);
}

void set_temperature(float temperature)
{
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%.1f", temperature); // make the number into string using sprintf function
    final_temp_buf[0] = '\0';
    strcat(final_temp_buf, "+");
    strcat(final_temp_buf, float_temp_buf);
    strcat(final_temp_buf, "°");
    lv_label_set_text(ui_TempLabel1, final_temp_buf);
}


void set_humidity(float humidity)
{
    char temp_buf[8];
    sprintf(temp_buf, "%.1f", humidity); // make the number into string using sprintf function
    strcat(temp_buf, "%");
    lv_label_set_text(ui_HumidityLabel1, temp_buf);
}

void set_co2(int16_t co2)
{
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%u", co2); // make the number into string using sprintf function
    lv_label_set_text(ui_CO2Label1, float_temp_buf);
}

void set_battery_voltage(float battery_voltage)
{
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%.2f", battery_voltage); // make the number into string using sprintf function
    final_temp_buf[0] = '\0';
    sprintf(final_temp_buf, "%s", "Bat:"); // make the number into string using sprintf function
    strcat(final_temp_buf, float_temp_buf);
    strcat(final_temp_buf, "V");
    lv_label_set_text(ui_BatLabel1, final_temp_buf);
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


void Update_point_temperature(void *arg)
{
    float local_point_temperature_reading; 
    float average_point_temperature_reading;;
    static uint8_t avg_counter = 0;

    for (;;)
    {
        if (xQueueReceive(update_queue_point_temperature, &local_point_temperature_reading, portMAX_DELAY))
        {
            average_point_temperature_reading += local_point_temperature_reading;
            avg_counter++;
            if (avg_counter >= 10)
            {
                local_point_temperature_reading = (average_point_temperature_reading / avg_counter);
                average_point_temperature_reading = 0;
                printf("Point temperature = %.2f \n", local_point_temperature_reading);

                bsp_display_lock(0);
                set_point_temperature(local_point_temperature_reading);
                bsp_display_unlock();
                avg_counter = 0;
            }
        }
    }
}



void Update_ambient_temperature(void *arg)
{
    float local_ambient_temperature_reading; 
    float average_ambient_temperature_reading;;
    static uint8_t avg_counter = 0;

    for (;;)
    {
        if (xQueueReceive(update_queue_ambient_temperature, &local_ambient_temperature_reading, portMAX_DELAY))
        {
            average_ambient_temperature_reading += local_ambient_temperature_reading;
            avg_counter++;
            if (avg_counter >= 10)
            {
                local_ambient_temperature_reading = (average_ambient_temperature_reading / avg_counter);
                average_ambient_temperature_reading = 0;
                printf("Ambient temperature = %.2f \n", local_ambient_temperature_reading);

                bsp_display_lock(0);
                set_ambient_temperature(local_ambient_temperature_reading);
                bsp_display_unlock();
                avg_counter = 0;
            }
        }
    }
}