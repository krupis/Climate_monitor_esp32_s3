| Supported Targets | ESP32 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- |
# ST7789V (T-Display-S3) from LilyGo example using LVGL 


## How to use the example

### Hardware Required

* An ESP development board
* T-Display-S3 development board (https://www.lilygo.cc/products/t-display-s3)
* An USB cable for power supply and programming

### Hardware Connection

Detailed description of T-Display-S3 development board can be found here:
https://github.com/Xinyuan-LilyGO/T-Display-S3



![ScreenShot](https://github.com/krupis/T-Display-S3-esp-idf/blob/master/images/T-DISPLAY-S3.jpg)



The GPIO number used by this example can be changed in [i80_controller_example_main.c](main/i80_controller_example_main.c).
Especially, please pay attention to the binary signal level used to turn the LCD backlight on, some LCD modules need a low level to turn it on, while others require a high level. You can change the backlight level macro `EXAMPLE_LCD_BK_LIGHT_ON_LEVEL` in [i80_controller_example_main.c](main/i80_controller_example_main.c).

### Build and Flash

Run `idf.py set-target <target-name>` to select one supported target that can run this example. This step will also apply the default Kconfig configurations into the `sdkconfig` file.

Run `idf.py menuconfig` to open a terminal UI where you can tune specific configuration for this example in the `Example Configuration` menu.

* `i80 LCD controller model`: Choose the LCD model to use by the example. If you choose `NT35510`, there will be another relevant configuration `NT35510 Data Width`, to choose the data line width for your NT35510 LCD module.

* `Allocate color data from PSRAM`: Select this option if you want to allocate the LVGL draw buffers from PSRAM.

Run `idf.py -p PORT build flash monitor` to build, flash and monitor the project. A fancy animation will show up on the LCD as expected.

The first time you run `idf.py` for the example will cost extra time as the build system needs to address the component dependencies and downloads the missing components from registry into `managed_components` folder.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

### Example Output

```bash
I (0) cpu_start: Starting scheduler on APP CPU.
I (418) example: Turn off LCD backlight
I (418) gpio: GPIO[2]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0
I (428) example: Initialize Intel 8080 bus
I (438) example: Install LCD driver of st7789
I (558) example: Turn on LCD backlight
I (558) example: Initialize LVGL library
I (558) example: Register display driver to LVGL
I (558) example: Install LVGL tick timer
I (558) example: Display LVGL animation
```

## Touch Screen Support

This example supports touch screen connected via I2C. You can enable it by running `idf.py menuconfig` and navigating to `Example Configuration -> Enable LCD touch`. When touch is enabled, there will be a new button in the GUI that can restart the animation.

These touch controllers are supported:
* [GT911](https://github.com/espressif/esp-bsp/tree/master/components/lcd_touch/esp_lcd_touch_gt911)
* [TT21100](https://github.com/espressif/esp-bsp/tree/master/components/lcd_touch/esp_lcd_touch_tt21100)
* [FT5X06](https://github.com/espressif/esp-bsp/tree/master/components/lcd_touch/esp_lcd_touch_ft5x06)


## Troubleshooting

* Can't get a stable UI when `EXAMPLE_LCD_I80_COLOR_IN_PSRAM` is enabled.

   This is because of the limited PSRAM bandwidth, compared to the internal SRAM. You can either decrease the PCLK clock `EXAMPLE_LCD_PIXEL_CLOCK_HZ` in [i80_controller_example_main.c](main/i80_controller_example_main.c) or increase the PSRAM working frequency `SPIRAM_SPEED` from the KConfig (e.g. **ESP32S3-Specific** -> **Set RAM clock speed**) or decrease the FPS in LVGL configuration. For illustration, this example has set the refresh period to 100ms in the default sdkconfig file.

For any technical queries, please open an [issue] (https://github.com/espressif/esp-idf/issues) on GitHub. We will get back to you soon.
