SET(SOURCES screens/ui_MainScreen.c
    screens/ui_CalibrationScreen.c
    screens/ui_ConfirmationScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_light_blue_dithered_rotated_png.c
    images/ui_img_thermometer_png.c
    images/ui_img_droplet_png.c
    images/ui_img_co2_resize_png.c
    images/ui_img_calibrate_png.c
    images/ui_img_co2_png.c
    fonts/ui_font_Interbold52.c)

add_library(ui ${SOURCES})
