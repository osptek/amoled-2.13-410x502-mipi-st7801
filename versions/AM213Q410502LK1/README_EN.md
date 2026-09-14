<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 2.13″ AMOLED 410×502 (ST7801 · MIPI)</h1>

<p align="center"><b>AMOLED module · MIPI · ST7801 · capacitive touch</b></p>

<p align="center"><a href="./README.md">简体中文</a> | English · <a href="../../README_EN.md">Family index</a></p>

<p align="center">
  <img alt="Size: 2.13 inch" src="https://img.shields.io/badge/Size-2.13%22-3498DB?style=flat-square" />
  <img alt="Resolution: 410x502" src="https://img.shields.io/badge/Resolution-410%C3%97502-8E44AD?style=flat-square" />
  <img alt="Interface: MIPI" src="https://img.shields.io/badge/Interface-MIPI-27AE60?style=flat-square" />
  <img alt="Driver: ST7801" src="https://img.shields.io/badge/Driver-ST7801-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 2.13 inch 410×502 AMOLED MIPI module (ST7801) product image" src="./images/product.png" width="640" /></p>

## Contents

- [Overview](#overview)
- [Specifications](#specifications)
- [Sample projects](#sample-projects)
- [Repository layout](#repository-layout)
- [Resources](#resources)
- [Buy](#buy)
- [Support](#support)

---

## Overview

OSPTEK **2.13″ 410×502 AMOLED** is a **MIPI** color display module driven by **ST7801N**, with capacitive touch (**CST820**). Suited to handheld devices, wearables, and compact portrait HMI.

Spec ID (repository name): `amoled-2.13-410x502-mipi-st7801`

Current module version: **AM213Q410502LK1**. Electrical and mechanical details follow [`docs/AM213Q410502LK1.pdf`](./docs/AM213Q410502LK1.pdf).

## Specifications

| Item | Spec |
| ---- | ---- |
| Size | 2.13 inch |
| Type | AMOLED (color) |
| Resolution | 410×502 |
| Interface | MIPI |
| Driver IC | ST7801N |
| Touch driver | CST820 |

> Full outline, FPC definition, power, and timing follow the product datasheet / driver IC datasheet.

## Sample projects

| Description | Path |
| ---- | ---- |
| ESP32-P4 · ST7801 MIPI + esp-lvgl-port / LVGL9 | [`examples/esp32p4-idf5_st7801-mipi_esp-lvgl-port_lvgl9/`](./examples/esp32p4-idf5_st7801-mipi_esp-lvgl-port_lvgl9/) |
| ESP32-P4 · ST7801 MIPI + PPA landscape / LVGL9 | [`examples/esp32p4-idf5_st7801-mipi_esp-lvgl-port_lvgl9_ppa/`](./examples/esp32p4-idf5_st7801-mipi_esp-lvgl-port_lvgl9_ppa/) |
| ESP32-P4 · LVGL + TE | [`examples/esp32p4-idf5_st7801-mipi_lvgl_common_demo/`](./examples/esp32p4-idf5_st7801-mipi_lvgl_common_demo/) |
| ESP32-P4 · EAF player | [`examples/p4-idf_st7801-mipi_esp-lv-eaf-player/`](./examples/p4-idf_st7801-mipi_esp-lv-eaf-player/) |
| ESP32-P4 · ST7801 MIPI display test | [`examples/esp32p4-idf5_st7801_mipi-dsi/`](./examples/esp32p4-idf5_st7801_mipi-dsi/) |
| ESP32-P4 · CST820 touch I2C test | [`examples/esp32p4-idf5_cst820-i2c/`](./examples/esp32p4-idf5_cst820-i2c/) |
| Raspberry Pi 5 · ST7801 410×502 panel / DT overlay (display only) | [`examples/rpi5-panel-st7801-410x502/`](./examples/rpi5-panel-st7801-410x502/) |
| Raspberry Pi 5 · CST820 touch / DT overlay (touch only) | [`examples/rpi5-touch-cst820/`](./examples/rpi5-touch-cst820/) |
| Raspberry Pi 5 · ST7801 display + CST820 touch / DT overlay | [`examples/rpi5-panel-st7801-cst820-410x502/`](./examples/rpi5-panel-st7801-cst820-410x502/) |
| Raspberry Pi 5 · ST7801 410×502 LVGL demo | [`examples/rpi5-lvgl-st7801-cst820-410x502/`](./examples/rpi5-lvgl-st7801-cst820-410x502/) |

## Repository layout

```text
amoled-2.13-410x502-mipi-st7801/                                # repo root (nav: ../../README_EN.md)
└── versions/
    └── AM213Q410502LK1/                                # full materials for this part number
        ├── README.md
        ├── README_EN.md
        ├── images/
        ├── docs/
        └── examples/
```

## Resources

### Product files

| Resource | Link |
| ---- | ---- |
| Product datasheet (AM213Q410502LK1) | [`docs/AM213Q410502LK1.pdf`](./docs/AM213Q410502LK1.pdf) |
| Outline drawing (AM213Q410502LK1) | [`docs/AM213Q410502LK1_外形图.pdf`](./docs/AM213Q410502LK1_%E5%A4%96%E5%BD%A2%E5%9B%BE.pdf) |
| Driver IC datasheet (ST7801N) | [`docs/ST_7801_N_Data_Sheet_V0_3_78db6a8826.pdf`](./docs/ST_7801_N_Data_Sheet_V0_3_78db6a8826.pdf) |
| Touch IC datasheet (CST820) | [`docs/CST820_Datasheet_V1.2.pdf`](./docs/CST820_Datasheet_V1.2.pdf) |
| Init sequence (text) | [`docs/GVO2.06_410x502_ST7801N_Mipi_简码.txt`](./docs/GVO2.06_410x502_ST7801N_Mipi_%E7%AE%80%E7%A0%81.txt) |
| 2.13″ AMOLED adapter schematic | [`docs/2.13寸AMOLED转接板.png`](./docs/2.13%E5%AF%B8AMOLED%E8%BD%AC%E6%8E%A5%E6%9D%BF.png) |

### Samples

- [ESP32-P4 ST7801 MIPI + LVGL9](./examples/esp32p4-idf5_st7801-mipi_esp-lvgl-port_lvgl9/)
- [ESP32-P4 ST7801 MIPI + PPA landscape / LVGL9](./examples/esp32p4-idf5_st7801-mipi_esp-lvgl-port_lvgl9_ppa/)
- [ESP32-P4 LVGL + TE](./examples/esp32p4-idf5_st7801-mipi_lvgl_common_demo/)
- [ESP32-P4 EAF](./examples/p4-idf_st7801-mipi_esp-lv-eaf-player/)
- [ESP32-P4 display test](./examples/esp32p4-idf5_st7801_mipi-dsi/)
- [ESP32-P4 CST820 touch test](./examples/esp32p4-idf5_cst820-i2c/)
- [Raspberry Pi 5 ST7801 panel (display only)](./examples/rpi5-panel-st7801-410x502/)
- [Raspberry Pi 5 CST820 touch (touch only)](./examples/rpi5-touch-cst820/)
- [Raspberry Pi 5 ST7801 display + CST820 touch](./examples/rpi5-panel-st7801-cst820-410x502/)
- [Raspberry Pi 5 ST7801 LVGL demo](./examples/rpi5-lvgl-st7801-cst820-410x502/)

## Buy

<p align="center">
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="AliExpress store" src="https://img.shields.io/badge/AliExpress-Official_Store-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://shop110742373.taobao.com/"><img alt="Taobao store" src="https://img.shields.io/badge/Taobao-Official_Store-FF6A00?style=for-the-badge" /></a>
</p>

**Overseas (AliExpress)**

- Store: [OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

**China (Taobao)**

- Store: [鱼鹰光电工厂店](https://shop110742373.taobao.com/)

## Support

- Technical support / product inquiry: <luyu@osptek.com>
- QQ group: **985881096**
- Website: <https://osptek.com/>
- Feel free to open an Issue in this repository with any questions

---

<p align="center"><sub>© 2026 OSPTEK · Materials in this repository are licensed under CC BY 4.0</sub></p>
