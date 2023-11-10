file(GLOB_RECURSE IMAGE_SOURCES assets/*.c)

idf_component_register(SRCS "ui.c" "lvgl_custom.c" "lvgl_setup.c" "ui_helpers.c" "ui_CalibrationScreen" "ui_ConfirmationScreen" "ui_MainScreen1" ${IMAGE_SOURCES}
                    INCLUDE_DIRS "include"
                    REQUIRES lvgl esp_lcd esp_timer heap driver esp_lcd_touch_cst816s SHT40)
                    

                    