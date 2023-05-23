#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"

static const char *TAG = "example";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// Please update the following configuration according to your LCD spec //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ (2 * 1000 * 1000)

#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL 1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_DATA0 39    // 6
#define EXAMPLE_PIN_NUM_DATA1 40    // 7
#define EXAMPLE_PIN_NUM_DATA2 41    // 8
#define EXAMPLE_PIN_NUM_DATA3 42    // 9
#define EXAMPLE_PIN_NUM_DATA4 45    // 10
#define EXAMPLE_PIN_NUM_DATA5 46    // 11
#define EXAMPLE_PIN_NUM_DATA6 47    // 12
#define EXAMPLE_PIN_NUM_DATA7 48    // 13
#define EXAMPLE_PIN_NUM_PCLK 8      // 5
#define EXAMPLE_PIN_NUM_CS 6        // 3
#define EXAMPLE_PIN_NUM_DC 7        // 4
#define EXAMPLE_PIN_NUM_RST 5       // 2
#define EXAMPLE_PIN_NUM_BK_LIGHT 38 // 1
#define EXAMPLE_PIN_NUM_POWER 15
#define PIN_LCD_RD 9

// The pixel number in horizontal and vertical
#define EXAMPLE_LCD_H_RES 320
#define EXAMPLE_LCD_V_RES 170
// Bit number used to represent command and parameter
#define EXAMPLE_LCD_CMD_BITS 8
#define EXAMPLE_LCD_PARAM_BITS 8

#define EXAMPLE_LVGL_TICK_PERIOD_MS 2

// Supported alignment: 16, 32, 64. A higher alignment can enables higher burst transfer size, thus a higher i80 bus throughput.
#define EXAMPLE_PSRAM_DATA_ALIGNMENT 32

void *buf1 = NULL;
void *buf2 = NULL;
size_t buff_idx = 0;
static bool trans_done = true;


extern void example_lvgl_demo_ui(lv_disp_t *disp);

static void write_color(esp_lcd_panel_handle_t panel_handle)
{
    if (!trans_done)
        return;

    trans_done = false;

    void *buff = (buff_idx++ % 2) ? buf1 : buf2;

    esp_lcd_panel_draw_bitmap(panel_handle, 50, 50, 60, 60, buff);
}

static void set_white_screen(esp_lcd_panel_handle_t panel_handle)
{
    if (!trans_done)
        return;
    trans_done = false;

    esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 320, 170, buf2);
}

static void set_black_screen(esp_lcd_panel_handle_t panel_handle)
{
    if (!trans_done)
        return;
    trans_done = false;

    esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 320, 170, buf1);
}

size_t trans_done_calls = 0;

static bool on_color_trans_done(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    trans_done = true;
    trans_done_calls++;

    return false;
}

static void tick_timer_cb(void *arg)
{
    ESP_LOGI(TAG, "trans_done_calls: %zu", trans_done_calls);

    trans_done_calls = 0;
}



static void example_lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}

static void example_increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}





void app_main(void)
{


//     gpio_config_t pwr_gpio_config = {
//         .mode = GPIO_MODE_OUTPUT,
//         .pin_bit_mask = 1ULL << EXAMPLE_PIN_NUM_POWER};
//     ESP_ERROR_CHECK(gpio_config(&pwr_gpio_config));
//     gpio_set_level(EXAMPLE_PIN_NUM_POWER, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);


// const gpio_config_t input_conf = {
    
//     .mode = GPIO_MODE_INPUT,
//     .pull_up_en = GPIO_PULLUP_ENABLE,
//     .pin_bit_mask =  1ULL << PIN_LCD_RD
// };
// ESP_ERROR_CHECK(gpio_config(&input_conf));


//     ESP_LOGI(TAG, "Turn off LCD backlight");
//     gpio_config_t bk_gpio_config = {
//         .mode = GPIO_MODE_OUTPUT,
//         .pin_bit_mask = 1ULL << EXAMPLE_PIN_NUM_BK_LIGHT};
//     ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));
//     gpio_set_level(EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL);

//     ESP_LOGI(TAG, "Initialize Intel 8080 bus");
//     esp_lcd_i80_bus_handle_t i80_bus = NULL;
//     esp_lcd_i80_bus_config_t bus_config = {
//         .clk_src = LCD_CLK_SRC_DEFAULT,
//         .dc_gpio_num = EXAMPLE_PIN_NUM_DC,
//         .wr_gpio_num = EXAMPLE_PIN_NUM_PCLK,
//         .data_gpio_nums = {
//             EXAMPLE_PIN_NUM_DATA0,
//             EXAMPLE_PIN_NUM_DATA1,
//             EXAMPLE_PIN_NUM_DATA2,
//             EXAMPLE_PIN_NUM_DATA3,
//             EXAMPLE_PIN_NUM_DATA4,
//             EXAMPLE_PIN_NUM_DATA5,
//             EXAMPLE_PIN_NUM_DATA6,
//             EXAMPLE_PIN_NUM_DATA7,
//         },
//         .bus_width = CONFIG_EXAMPLE_LCD_I80_BUS_WIDTH,
//         .max_transfer_bytes = EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES * sizeof(uint16_t),
//         .psram_trans_align = EXAMPLE_PSRAM_DATA_ALIGNMENT,
//         .sram_trans_align = 4,
//     };
//     ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_config, &i80_bus));
//     esp_lcd_panel_io_handle_t io_handle = NULL;
//     esp_lcd_panel_io_i80_config_t io_config = {
//         .cs_gpio_num = EXAMPLE_PIN_NUM_CS,
//         .pclk_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
//         .trans_queue_depth = 20,
//         .dc_levels = {
//             .dc_idle_level = 0,
//             .dc_cmd_level = 0,
//             .dc_dummy_level = 0,
//             .dc_data_level = 1,
//         },
//         .flags = {
//             .swap_color_bytes = 1, // Swap can be done in LvGL (default) or DMA
//         },
//         .on_color_trans_done = on_color_trans_done,
//         .user_ctx = NULL,
//         .lcd_cmd_bits = EXAMPLE_LCD_CMD_BITS,
//         .lcd_param_bits = EXAMPLE_LCD_PARAM_BITS,
//     };
//     ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));

//     esp_lcd_panel_handle_t panel_handle = NULL;

//     ESP_LOGI(TAG, "Install LCD driver of st7789");
//     esp_lcd_panel_dev_config_t panel_config = {
//         .reset_gpio_num = EXAMPLE_PIN_NUM_RST,
//         .rgb_endian = LCD_RGB_ENDIAN_RGB,
//         .bits_per_pixel = 16,
//     };
//     ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));

//     esp_lcd_panel_reset(panel_handle);
//     esp_lcd_panel_init(panel_handle);
//     // Set inversion, x/y coordinate order, x/y mirror according to your LCD module spec
//     // the gap is LCD panel specific, even panels with the same driver IC, can have different gap value
//     ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
//     ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, true));
//     ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, true));
//     ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 0, 35));

//     ESP_LOGI(TAG, "Turn on LCD backlight");
//     gpio_set_level(EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);

//     ESP_LOGI(TAG, "Initialize UI");
//     // alloc draw buffers used by LVGL
//     // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
//     buf1 = heap_caps_malloc(EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES * 2, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
//     buf2 = heap_caps_malloc(EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES * 2, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);

//     assert(buf1);
//     assert(buf2);

//     memset(buf1, 0x0, EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES * 2);
//     memset(buf2, 0xff, EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES * 2);

//     ESP_LOGI(TAG, "buf1@%p, buf2@%p", buf1, buf2);

//     const esp_timer_create_args_t tick_timer_args = {
//         .callback = &tick_timer_cb,
//         .name = "tick_timer"};
//     esp_timer_handle_t tick_timer = NULL;
//     ESP_ERROR_CHECK(esp_timer_create(&tick_timer_args, &tick_timer));
//     ESP_ERROR_CHECK(esp_timer_start_periodic(tick_timer, 1000000));

//     // user can flush pre-defined pattern to the screen before we turn on the screen or backlight
//     ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, false));
//     ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));





















    static lv_disp_draw_buf_t disp_buf; // contains internal graphic buffer(s) called draw buffer(s)
    static lv_disp_drv_t disp_drv;      // contains callback functions


    gpio_config_t pwr_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << EXAMPLE_PIN_NUM_POWER};
    ESP_ERROR_CHECK(gpio_config(&pwr_gpio_config));
    gpio_set_level(EXAMPLE_PIN_NUM_POWER, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);


const gpio_config_t input_conf = {
    
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pin_bit_mask =  1ULL << PIN_LCD_RD
};
ESP_ERROR_CHECK(gpio_config(&input_conf));


    ESP_LOGI(TAG, "Turn off LCD backlight");
    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << EXAMPLE_PIN_NUM_BK_LIGHT};
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));
    gpio_set_level(EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL);



    ESP_LOGI(TAG, "Initialize Intel 8080 bus");
    esp_lcd_i80_bus_handle_t i80_bus = NULL;
    esp_lcd_i80_bus_config_t bus_config = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .dc_gpio_num = EXAMPLE_PIN_NUM_DC,
        .wr_gpio_num = EXAMPLE_PIN_NUM_PCLK,
        .data_gpio_nums = {
            EXAMPLE_PIN_NUM_DATA0,
            EXAMPLE_PIN_NUM_DATA1,
            EXAMPLE_PIN_NUM_DATA2,
            EXAMPLE_PIN_NUM_DATA3,
            EXAMPLE_PIN_NUM_DATA4,
            EXAMPLE_PIN_NUM_DATA5,
            EXAMPLE_PIN_NUM_DATA6,
            EXAMPLE_PIN_NUM_DATA7,
        },
        .bus_width = CONFIG_EXAMPLE_LCD_I80_BUS_WIDTH,
        .max_transfer_bytes = EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES * sizeof(uint16_t),
        .psram_trans_align = EXAMPLE_PSRAM_DATA_ALIGNMENT,
        .sram_trans_align = 4,
    };
    ESP_ERROR_CHECK(esp_lcd_new_i80_bus(&bus_config, &i80_bus));
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = EXAMPLE_PIN_NUM_CS,
        .pclk_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 20,
        .dc_levels = {
            .dc_idle_level = 0,
            .dc_cmd_level = 0,
            .dc_dummy_level = 0,
            .dc_data_level = 1,
        },
        .flags = {
            .swap_color_bytes = 1, // Swap can be done in LvGL (default) or DMA
        },
        .on_color_trans_done = on_color_trans_done,
        .user_ctx = NULL,
        .lcd_cmd_bits = EXAMPLE_LCD_CMD_BITS,
        .lcd_param_bits = EXAMPLE_LCD_PARAM_BITS,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));

    esp_lcd_panel_handle_t panel_handle = NULL;


    ESP_LOGI(TAG, "Install LCD driver of st7789");
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = EXAMPLE_PIN_NUM_RST,
        .rgb_endian = LCD_RGB_ENDIAN_RGB,
        .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));

    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_init(panel_handle);

    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, true));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, true));
    ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 0, 35));

    esp_lcd_panel_io_tx_param(io_handle, 0xF2, (uint8_t[]) { 0 }, 1); // 3Gamma function disable
    esp_lcd_panel_io_tx_param(io_handle, 0x26, (uint8_t[]) { 1 }, 1); // Gamma curve 1 selected
    esp_lcd_panel_io_tx_param(io_handle, 0xE0, (uint8_t[]) {          // Set positive gamma
        0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00 }, 15);
    esp_lcd_panel_io_tx_param(io_handle, 0xE1, (uint8_t[]) {          // Set negative gamma
        0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F }, 15);


    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    ESP_LOGI(TAG, "Turn on LCD backlight");
    gpio_set_level(EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();

    lv_color_t *buf1 = NULL;
    lv_color_t *buf2 = NULL;

    buf1 = heap_caps_malloc(EXAMPLE_LCD_H_RES * 100 * sizeof(lv_color_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
    assert(buf1);

    buf2 = heap_caps_malloc(EXAMPLE_LCD_H_RES * 100 * sizeof(lv_color_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
    assert(buf2);

    ESP_LOGI(TAG, "buf1@%p, buf2@%p", buf1, buf2);
    // initialize LVGL draw buffers
    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, EXAMPLE_LCD_H_RES * 100);



    ESP_LOGI(TAG, "Register display driver to LVGL");
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = EXAMPLE_LCD_H_RES;
    disp_drv.ver_res = EXAMPLE_LCD_V_RES;
    disp_drv.flush_cb = example_lvgl_flush_cb;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.user_data = panel_handle;
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

    ESP_LOGI(TAG, "Install LVGL tick timer");
    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    const esp_timer_create_args_t lvgl_tick_timer_args = {
        .callback = &example_increase_lvgl_tick,
        .name = "lvgl_tick"
    };
    esp_timer_handle_t lvgl_tick_timer = NULL;
    ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000));

    ESP_LOGI(TAG, "Display LVGL animation");
    example_lvgl_demo_ui(disp);

    while (1) {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        vTaskDelay(10 / portTICK_PERIOD_MS);
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();
    }





















    //set_white_screen(panel_handle);



    // while (1)
    // {
    //     write_color(panel_handle);

    //     vTaskDelay(pdMS_TO_TICKS(10));
    // }
}