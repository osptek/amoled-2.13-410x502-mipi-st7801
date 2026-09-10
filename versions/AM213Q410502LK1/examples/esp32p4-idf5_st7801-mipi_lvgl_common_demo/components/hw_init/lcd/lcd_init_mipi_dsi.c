/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "hw_init.h"

#if CONFIG_EXAMPLE_LCD_INTERFACE_MIPI_DSI

#include "esp_ldo_regulator.h"
#include "esp_lcd_mipi_dsi.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_st7801.h"
#include "driver/gpio.h"

static const char *TAG = "hw_lcd_init";

#define HW_LDO_MIPI_CHAN                        (3)
#define HW_LDO_MIPI_VOLTAGE_MV                  (2500)
#define HW_LCD_BIT_PER_PIXEL                    (16)
#define HW_MIPI_DPI_PX_FORMAT                   (LCD_COLOR_PIXEL_FORMAT_RGB565)
#define HW_PIN_NUM_LCD_RST                      (-1)

static esp_lcd_dsi_bus_handle_t s_mipi_dsi_bus;
static esp_lcd_panel_io_handle_t s_mipi_dbi_io;
static esp_lcd_panel_handle_t s_panel_handle;

static const st7801_lcd_init_cmd_t lcd_init_cmds[] = {
    //  {cmd, { data }, data_size, delay_ms}
    {0x11, (uint8_t []){0x00}, 0, 100},
    {0x2A, (uint8_t []){0x00,0x00,0x01,0x99}, 4, 0},
    {0x2B, (uint8_t []){0x00,0x00,0x01,0xF5}, 4, 0},
    {0x35, (uint8_t []){0x00}, 1, 0},
    {0x3A, (uint8_t []){0x77}, 1, 0},//RGB888
    {0x51, (uint8_t []){0xff}, 1, 0},
    {0x53, (uint8_t []){0x20}, 1, 0},
    {0x29, (uint8_t []){0x00}, 0, 0},
};

static void lcd_ldo_power_on(void)
{
    esp_ldo_channel_handle_t ldo_mipi_phy = NULL;
    esp_ldo_channel_config_t ldo_mipi_phy_config = {
        .chan_id = HW_LDO_MIPI_CHAN,
        .voltage_mv = HW_LDO_MIPI_VOLTAGE_MV,
    };
    ESP_ERROR_CHECK(esp_ldo_acquire_channel(&ldo_mipi_phy_config, &ldo_mipi_phy));
}

esp_err_t hw_lcd_init(esp_lcd_panel_handle_t *panel_handle, esp_lcd_panel_io_handle_t *io_handle, esp_lv_adapter_tear_avoid_mode_t tear_avoid_mode, esp_lv_adapter_rotation_t rotation)
{
    lcd_ldo_power_on();

    ESP_LOGD(TAG, "Install LCD driver");
    esp_lcd_dsi_bus_config_t bus_config = ST7801_PANEL_BUS_DSI_1CH_CONFIG();
    ESP_ERROR_CHECK(esp_lcd_new_dsi_bus(&bus_config, &s_mipi_dsi_bus));

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_dbi_io_config_t dbi_config = ST7801_PANEL_IO_DBI_CONFIG();
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_dbi(s_mipi_dsi_bus, &dbi_config, &s_mipi_dbi_io));

    ESP_LOGI(TAG, "Install LCD driver of st7801");
    esp_lcd_dpi_panel_config_t dpi_config = ST7801_410_502_PANEL_60HZ_DPI_CONFIG(HW_MIPI_DPI_PX_FORMAT);

    dpi_config.num_fbs = esp_lv_adapter_get_required_frame_buffer_count(tear_avoid_mode, rotation);
    st7801_vendor_config_t vendor_config = {
        .init_cmds = lcd_init_cmds,      // Uncomment these line if use custom initialization commands
        .init_cmds_size = sizeof(lcd_init_cmds) / sizeof(st7801_lcd_init_cmd_t),
        .flags.use_mipi_interface = 1,
        .mipi_config = {
            .dsi_bus = s_mipi_dsi_bus,
            .dpi_config = &dpi_config,
        },
    };
    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = HW_PIN_NUM_LCD_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = HW_LCD_BIT_PER_PIXEL,
        .vendor_config = &vendor_config,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7801(s_mipi_dbi_io, &panel_config, &s_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(s_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(s_panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_st7801_set_brightness(s_panel_handle, 50));

    *panel_handle = s_panel_handle;
    if (io_handle) {
        *io_handle = s_mipi_dbi_io;
    }

    return ESP_OK;
}

#endif
