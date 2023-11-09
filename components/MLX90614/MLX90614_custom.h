#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "esp_log.h"
#include "MLX90614_API.h"
#include "MLX90614_SMBus_Driver.h"  


void MLX90614_measure_temp(void* param);