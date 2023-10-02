#ifndef GPIO_H
#define GPIO_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "esp_log.h"


#define EXAMPLE_ADC1_CHAN3          ADC_CHANNEL_3
#define EXAMPLE_ADC_ATTEN           ADC_ATTEN_DB_11


void ADC_Setup();

float Get_ADC_Voltage(uint16_t channel);
void Measure_bat_voltage(void *argument);


#endif