#ifndef ST7801_INIT_CMDS_H
#define ST7801_INIT_CMDS_H

#include "esp_lcd_st7801.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==================== ST7801 初始化命令数组 ====================
static st7801_lcd_init_cmd_t lcd_init_cmds[] = {
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

static const size_t lcd_init_cmds_size = sizeof(lcd_init_cmds) / sizeof(st7801_lcd_init_cmd_t);

#ifdef __cplusplus
}
#endif

#endif // ST7801_INIT_CMDS_H