#ifndef NVS_CUSTOM_H
#define NVS_CUSTOM_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"


void NVS_open();
esp_err_t get_nvs_key_value(char* key, char* return_value);
esp_err_t set_nvs_key_value(char* key,char* key_value);


#endif