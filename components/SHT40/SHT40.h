#ifndef SHT40_H
#define SHT40_H


#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"

esp_err_t i2c_master_init(void);
esp_err_t Measure_temp_humidity();
void SHT40_task(void *argument);

#endif