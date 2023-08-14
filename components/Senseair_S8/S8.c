#include "S8.h"

static const int RX_BUF_SIZE = 1024;

#define TXD_PIN 43
#define RXD_PIN 44

#define UART UART_NUM_2
int num = 0;

unsigned long int ReadCRC, DataCRC;     // Control-ReturnCodes to compare Readed against Calculated

char CO2req[] = {0xFE, 0x04, 0x00, 0x03, 0x00, 0x01, 0xD5, 0xC5};   // Request CO2-Value
char ABCreq[] = {0xFE, 0X03, 0X00, 0X1F, 0X00, 0X01, 0XA1, 0XC3};   // Request ABC-Interval in [h] 1f in Hex -> 31 dezimal
char FWreq[] = {0xFE, 0x04, 0x00, 0x1C, 0x00, 0x01, 0xE4, 0x03};    // Readout FirmWareversion    
char ID_Hi[] = {0xFE, 0x04, 0x00, 0x1D, 0x00, 0x01, 0xB5, 0xC3};    // Sensor ID hi    
char ID_Lo[] = {0xFE, 0x04, 0x00, 0x1E, 0x00, 0x01, 0x45, 0xC3};    // Sensor ID lo    // in Hex 071dbfe4


extern lv_obj_t *ui_TemperatureLabel1;


#define BUF_SIZE (1024)
void UART1_setup()
{
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,

    };

    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(UART, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(UART, RX_BUF_SIZE, 0, 0, NULL, 0));
}




unsigned short int ModBus_CRC(unsigned char * buf, int len)
{
  unsigned short int crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++) {
    crc ^= (unsigned short int)buf[pos];   // XOR byte into least sig. byte of crc
    for (int i = 8; i != 0; i--) {         // Loop over each bit
      if ((crc & 0x0001) != 0) {           // If the LSB is set
        crc >>= 1;                         // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;  
} 

static int send_Req(const char* data, int Req_len)
{
    const int txBytes = uart_write_bytes(UART, data, Req_len);
    return txBytes;
}

void tx_task(void *arg)
{
    static const char *TX_TASK_TAG = "Transfer_TASK";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    while (1) {
        printf("Sending data \n");
        send_Req(CO2req, 8);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}


static void set_co2(int16_t co2)
{
    printf("set co2 \n");
    char float_temp_buf[8];
    char final_temp_buf[10];
    sprintf(float_temp_buf, "%u", co2); // make the number into string using sprintf function


    lv_label_set_text(ui_TemperatureLabel1, float_temp_buf);
    //lv_arc_set_value(ui_TemperatureArc, (int16_t)(temperature));
}

void rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "Receive_TASK";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
        // Configure a temporary buffer for the incoming data
    uint8_t* vResponse = (uint8_t*) malloc(BUF_SIZE+1);
    while (1) {
        
        // Read data from the UART
        const int rxBytes = uart_read_bytes(UART, vResponse, BUF_SIZE, 1000 / portTICK_PERIOD_MS);
        if (rxBytes > 0) {
            vResponse[rxBytes] = 0;
            for(int i = 0; i <7;i++){
                printf("Response[%i] = %.2x \n",i,vResponse[i]);
            }
            
            ReadCRC = (uint16_t)vResponse[6] * 256 + (uint16_t)vResponse[5];
            DataCRC = ModBus_CRC(vResponse, 5);
            if (DataCRC == ReadCRC) {
                ESP_LOGI(RX_TASK_TAG, "CO2 %d ", vResponse[3] * 256 + vResponse[4]);
                    bsp_display_lock(0);
                    set_co2(vResponse[3] * 256 + vResponse[4]);
                    bsp_display_unlock();
            } else 
            {
                ESP_LOGI(RX_TASK_TAG, "CRC-Fehler %ld ungleich %ld", ReadCRC, DataCRC);
            }
        }
    }
    free(vResponse);
}






void get_info()
{
    uint8_t* vResponse = (uint8_t*) malloc(BUF_SIZE+1);
    //  Read ABC-Period - automativ Baseline Correction 
    send_Req(ABCreq, 8);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    int rxBytes = uart_read_bytes(UART, vResponse, BUF_SIZE, 1000 / portTICK_PERIOD_MS);
    ReadCRC = (uint16_t)vResponse[6] * 256 + (uint16_t)vResponse[5];
    DataCRC = ModBus_CRC(vResponse, 5);
    if (DataCRC == ReadCRC) {
        ESP_LOGI("Info", "ABC-Period %d ", vResponse[3] * 256 + vResponse[4]);
    }
        else          
    {
        ESP_LOGI("Error", "CRC-Fehler %ld ungleich %ld", ReadCRC, DataCRC);
    }
    
    //  Read Firmware 
    send_Req(FWreq, 8);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    rxBytes = uart_read_bytes(UART, vResponse, BUF_SIZE, 1000 / portTICK_PERIOD_MS);
    ReadCRC = (uint16_t)vResponse[6] * 256 + (uint16_t)vResponse[5];
    DataCRC = ModBus_CRC(vResponse, 5);
    if (DataCRC == ReadCRC) {
        ESP_LOGI("Info", "Firmware: %d ", vResponse[3] * 256 + vResponse[4]);
    }
        else
    {
        ESP_LOGI("Error", "CRC-Fehler %ld ungleich %ld", ReadCRC, DataCRC);
    }
    
//  Read Sensor ID - Unique ID of the S8 Sensor like 071dbfe4
    send_Req(ID_Hi, 8);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    rxBytes = uart_read_bytes(UART, vResponse, BUF_SIZE, 1000 / portTICK_PERIOD_MS);
    if (DataCRC == ReadCRC) {
        ESP_LOGI("Info", "Sensor-ID %d%d ", vResponse[3] , vResponse[4]);
    }
        else          
    {
        ESP_LOGI("Error", "CRC-Fehler %ld ungleich %ld", ReadCRC, DataCRC);
    }
    send_Req(ID_Lo, 8);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    rxBytes = uart_read_bytes(UART, vResponse, BUF_SIZE, 1000 / portTICK_PERIOD_MS);
    ESP_LOGI("Info", "Sensor-ID %d%d ", vResponse[3] , vResponse[4]);
}



