#ifndef S8_H
#define S8_H


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <esp_log.h>
#include "driver/uart.h"
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "lvgl_setup.h"
#include "lvgl_custom.h"

void UART1_setup();
void get_info();


 void tx_task(void *arg);
 void rx_task(void *arg);
 unsigned short int ModBus_CRC(unsigned char * buf, int len);

#endif