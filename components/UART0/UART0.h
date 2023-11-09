#ifndef UART0_H
#define UART0_H


#include "driver/uart.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "esp_sntp.h"
#include <time.h>
#include <sys/time.h>
#include "lvgl_custom.h"


bool ParseSystemCmd(char *line, uint16_t cmd_size);



#define UART0_COMMAND_LINE_MAX_SIZE 1024 // Modem and system uart max command size (Max chars in one command line)

void UART0_task(void *argument);
void UART0_setup();
bool UART0_buf_is_emtpy(void);
char UART0_rx_buf_get(void);



#endif