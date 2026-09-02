<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 2.13″ AMOLED 410×502（ST7801 · MIPI）</h1>

<p align="center"><b>AMOLED 模组 · MIPI · ST7801 · 电容触摸</b></p>

<p align="center"><a href="./README_EN.md">English</a> | 简体中文 · <a href="../../README.md">规格族索引</a></p>

<p align="center">
  <img alt="Size: 2.13 inch" src="https://img.shields.io/badge/Size-2.13%22-3498DB?style=flat-square" />
  <img alt="Resolution: 410x502" src="https://img.shields.io/badge/Resolution-410%C3%97502-8E44AD?style=flat-square" />
  <img alt="Interface: MIPI" src="https://img.shields.io/badge/Interface-MIPI-27AE60?style=flat-square" />
  <img alt="Driver: ST7801" src="https://img.shields.io/badge/Driver-ST7801-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 2.13 寸 410×502 AMOLED MIPI 模组（ST7801）宣传图" src="./images/product.png" width="640" /></p>

## 目录

- [产品简介](#产品简介)
- [规格参数](#规格参数)
- [示例工程](#示例工程)
- [仓库结构](#仓库结构)
- [相关资料](#相关资料)
- [购买链接](#购买链接)
- [技术支持](#技术支持)

---

## 产品简介

OSPTEK **2.13 寸 410×502 AMOLED** 是一款 **MIPI** 接口彩色显示模组，显示驱动为 **ST7801N**，触摸驱动为 **CST820**。适合手持终端、穿戴与小型竖屏 HMI 等场景。

规格标识（仓库名）：`2.13-amoled-410x502-mipi-st7801`

当前模组版本：**AM213Q410502LK1**。电气与外形细节以 [`docs/AM213Q410502LK1.pdf`](./docs/AM213Q410502LK1.pdf) 为准。

## 规格参数

| 项目 | 规格 |
| ---- | ---- |
| 尺寸 | 2.13 英寸 |
| 类型 | AMOLED（彩色） |
| 分辨率 | 410×502 |
| 接口 | MIPI |
| 驱动 IC | ST7801N |
| 触摸驱动 | CST820 |

> 完整外形尺寸、FPC 定义、供电与时序以产品规格书 / 驱动手册为准。

## 示例工程

| 说明 | 路径 |
| ---- | ---- |
| ESP32-P4 · ST7801 MIPI + esp-lvgl-port / LVGL9 | [`examples/P4-IDF_ST7801-MIPI_ESP-LVGL-PORT_V9/`](./examples/P4-IDF_ST7801-MIPI_ESP-LVGL-PORT_V9/) |
| ESP32-P4 · LVGL + TE 防撕裂 | [`examples/with-te/p4-idf_st7801-mipi_lvgl_common_demo/`](./examples/with-te/p4-idf_st7801-mipi_lvgl_common_demo/) |
| ESP32-P4 · EAF 播放 | [`examples/eaf/p4-idf_st7801-mipi_esp-lv-eaf-player/`](./examples/eaf/p4-idf_st7801-mipi_esp-lv-eaf-player/) |
| ESP32-P4 · ST7801 MIPI 显示测试 | [`examples/display-touch-test/st7801_mipi_dsi/`](./examples/display-touch-test/st7801_mipi_dsi/) |
| ESP32-P4 · CST820 触摸 I2C 测试 | [`examples/display-touch-test/P4-IDF_CST820-I2C/`](./examples/display-touch-test/P4-IDF_CST820-I2C/) |
| Raspberry Pi 5 · ST7801 410×502 面板驱动 / DT overlay（仅显示） | [`examples/rpi5-panel-st7801-410x502/`](./examples/rpi5-panel-st7801-410x502/) |
| Raspberry Pi 5 · CST820 触摸驱动 / DT overlay（仅触摸） | [`examples/rpi5-touch-cst820/`](./examples/rpi5-touch-cst820/) |
| Raspberry Pi 5 · ST7801 显示 + CST820 触摸 / DT overlay | [`examples/rpi5-panel-st7801-cst820-410x502/`](./examples/rpi5-panel-st7801-cst820-410x502/) |
| Raspberry Pi 5 · ST7801 410×502 LVGL 演示 | [`examples/rpi5-lvgl-st7801-cst820-410x502/`](./examples/rpi5-lvgl-st7801-cst820-410x502/) |

## 仓库结构

```text
2.13-amoled-410x502-mipi-st7801/                                # 仓库根（导航见 ../../README.md）
└── versions/
    └── AM213Q410502LK1/                                # 本料号完整资料
        ├── README.md
        ├── README_EN.md
        ├── images/
        ├── docs/
        └── examples/
```

## 相关资料

### 本产品资料

| 资料 | 链接 |
| ---- | ---- |
| 产品规格书（AM213Q410502LK1） | [`docs/AM213Q410502LK1.pdf`](./docs/AM213Q410502LK1.pdf) |
| 外形图（AM213Q410502LK1） | [`docs/AM213Q410502LK1_外形图.pdf`](./docs/AM213Q410502LK1_%E5%A4%96%E5%BD%A2%E5%9B%BE.pdf) |
| 驱动 IC 数据手册（ST7801N） | [`docs/ST_7801_N_Data_Sheet_V0_3_78db6a8826.pdf`](./docs/ST_7801_N_Data_Sheet_V0_3_78db6a8826.pdf) |
| 触摸 IC 数据手册（CST820） | [`docs/CST820_Datasheet_V1.2.pdf`](./docs/CST820_Datasheet_V1.2.pdf) |
| 初始化序列（文本） | [`docs/GVO2.06_410x502_ST7801N_Mipi_简码.txt`](./docs/GVO2.06_410x502_ST7801N_Mipi_%E7%AE%80%E7%A0%81.txt) |
| 2.13 寸 AMOLED 转接板原理图 | [`docs/2.13寸AMOLED转接板.png`](./docs/2.13%E5%AF%B8AMOLED%E8%BD%AC%E6%8E%A5%E6%9D%BF.png) |

### 示例工程

- [ESP32-P4 ST7801 MIPI + LVGL9](./examples/P4-IDF_ST7801-MIPI_ESP-LVGL-PORT_V9/)
- [ESP32-P4 LVGL + TE](./examples/with-te/p4-idf_st7801-mipi_lvgl_common_demo/)
- [ESP32-P4 EAF](./examples/eaf/p4-idf_st7801-mipi_esp-lv-eaf-player/)
- [ESP32-P4 显示测试](./examples/display-touch-test/st7801_mipi_dsi/)
- [ESP32-P4 CST820 触摸测试](./examples/display-touch-test/P4-IDF_CST820-I2C/)
- [Raspberry Pi 5 ST7801 面板（仅显示）](./examples/rpi5-panel-st7801-410x502/)
- [Raspberry Pi 5 CST820 触摸（仅触摸）](./examples/rpi5-touch-cst820/)
- [Raspberry Pi 5 ST7801 显示 + CST820 触摸](./examples/rpi5-panel-st7801-cst820-410x502/)
- [Raspberry Pi 5 ST7801 LVGL 演示](./examples/rpi5-lvgl-st7801-cst820-410x502/)

## 购买链接

<p align="center">
  <a href="https://shop110742373.taobao.com/"><img alt="淘宝官方店铺" src="https://img.shields.io/badge/淘宝-官方店铺-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="速卖通官方店铺" src="https://img.shields.io/badge/速卖通-官方店铺-FF6A00?style=for-the-badge" /></a>
</p>

**国内（淘宝）**

- 店铺：[鱼鹰光电工厂店](https://shop110742373.taobao.com/)

**海外（AliExpress）**

- 店铺：[OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

## 技术支持

- 技术支持 / 产品咨询：<luyu@osptek.com>
- QQ 技术交流群：**985881096**
- 公司官网：<https://osptek.com/>
- 有任何问题，都可以在本仓库 Issues 中提问

---

<p align="center"><sub>© 2026 OSPTEK 鱼鹰光电 · 本仓库资料采用 CC BY 4.0 许可</sub></p>
