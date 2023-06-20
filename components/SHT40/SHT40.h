#ifndef SHT40_H
#define SHT40_H


#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"


#define SHT40_SENSOR_ADDR                             0x44
#define SHT40_TEMP_HUMID_REG_HIGH_PREC                0xFD
#define SHT40_TEMP_HUMID_REG_MED_PREC                 0xF6
#define SHT40_TEMP_HUMID_REG_LOW_PREC                 0xE0
#define SHT40_READ_SERIAL                             0x89


esp_err_t i2c_master_init(void);
esp_err_t Measure_temp_humidity(uint8_t precision);
void SHT40_task(void *argument);

struct sht40_reading_s{
    float temperature;
    float humidity;
};

#endif