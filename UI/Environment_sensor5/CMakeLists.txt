SET(SOURCES screens/ui_CalibrationScreen.c
    screens/ui_ConfirmationScreen.c
    screens/ui_MainScreen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_light_blue_dithered_rotated_png.c
    images/ui_img_calibrate_png.c
    images/ui_img_thermometer_png.c
    images/ui_img_droplet_png.c
    images/ui_img_co2_resize_png.c
    images/ui_img_point_temperature_png.c
    images/ui_img_ambient_temperature_png.c
    fonts/ui_font_Interbold40.c)

add_library(ui ${SOURCES})
