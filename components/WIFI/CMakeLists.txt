idf_component_register(SRCS "WIFI.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_https_ota json esp_https_server spiffs app_update esp_wifi spi_flash fatfs vfs)