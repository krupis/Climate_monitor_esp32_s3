#include "MLX90614_custom.h"

#define MLX90614_DEFAULT_ADDRESS 0x5A // default chip address(slave address) of MLX90614

#define MLX90614_I2C_MASTER_SCL_IO 17
#define MLX90614_I2C_MASTER_SDA_IO 18





extern SemaphoreHandle_t i2c_mux;

float to = 0; // temperature of object
float ta = 0; // temperature of ambient
uint16_t dumpInfo = 0;

void MLX90614_measure_temp(void* param){
    MLX90614_SMBusInit(MLX90614_I2C_MASTER_SDA_IO, MLX90614_I2C_MASTER_SCL_IO, 50000); // sda scl and 50kHz
    for (;;)
    {
        if (xSemaphoreTake(i2c_mux, 100) == pdTRUE)
        {
            MLX90614_GetTo(MLX90614_DEFAULT_ADDRESS, &to);
            MLX90614_GetTa(MLX90614_DEFAULT_ADDRESS, &ta);
            MLX90614_GetTa(MLX90614_DEFAULT_ADDRESS, &dumpInfo);
            printf("log:%lf %lf %d\r\n", to, ta, dumpInfo);
            xSemaphoreGive(i2c_mux);
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }


}
        
