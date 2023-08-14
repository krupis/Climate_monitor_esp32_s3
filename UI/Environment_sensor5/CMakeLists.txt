SET(SOURCES screens/ui_MainMenu1.c
    screens/ui_SettingsScreen.c
    screens/ui_HumidityScreen.c
    screens/ui_TemperatureScreen.c
    screens/ui_CO2Screen.c
    screens/ui_PasswordScreen.c
    ui.c
    ui_helpers.c
    images/ui_img_main_screen_gradient_dithered_png.c
    images/ui_img_settings_png.c
    images/ui_img_light_blue_dithered_png.c
    images/ui_img_droplet2_png.c
    images/ui_img_home_png.c
    images/ui_img_menu_png.c
    images/ui_img_main_screen_gradient3_png.c
    images/ui_img_thermometer2_png.c
    images/ui_img_yellow_dithered_png.c
    images/ui_img_co2_new_png.c)

add_library(ui ${SOURCES})
