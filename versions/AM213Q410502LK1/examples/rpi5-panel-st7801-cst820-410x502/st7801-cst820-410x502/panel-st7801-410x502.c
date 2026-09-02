/*
 * ST7801 410x502 1-Lane MIPI-DSI Panel Driver for Raspberry Pi 5
 * Adapted for 2.13-inch rectangular AMOLED (Sitronix ST7801)
 *
 * This example is from the open-source sharing by engineers of Yuying Optoelectronics (鱼鹰光电)
 * on Github.com/osptek. Welcome to provide improvement suggestions.
 *
 * 本例程来源于鱼鹰光电的工程师的开源分享 Github.com/osptek，欢迎提出改进意见
 */

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <video/mipi_display.h>

struct power_on_timing {
	unsigned long post_reset;
	unsigned long reset_low;
	unsigned long after_reset;
	unsigned long slpout;
};

struct st7801_desc {
	const struct drm_display_mode *mode;
	unsigned int lanes;
	unsigned long flags;
	enum mipi_dsi_pixel_format format;
	int (*init_sequence)(struct mipi_dsi_device *dsi);
	const struct power_on_timing *pwr_timing;
	bool do_sw_reset;
};

struct st7801 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	const struct st7801_desc *desc;
	struct gpio_desc *reset;
	enum drm_panel_orientation orientation;
};

static inline struct st7801 *to_st7801(struct drm_panel *panel)
{
	return container_of(panel, struct st7801, panel);
}

/* ==================== ST7801 410x502 初始化序列 ==================== */
static int st7801_410x502_init_sequence(struct mipi_dsi_device *dsi)
{
	struct mipi_dsi_multi_context ctx = { .dsi = dsi };

	/* 0x11: Sleep Out + 100ms 延时 */
	mipi_dsi_dcs_write_seq_multi(&ctx, 0x11);
	msleep(100);

	/* 0x2A: CASET (0x00, 0x00, 0x01, 0x99) -> 410 列 */
	mipi_dsi_dcs_write_seq_multi(&ctx, 0x2A, 0x00, 0x00, 0x01, 0x99);

	/* 0x2B: PASET (0x00, 0x00, 0x01, 0xF5) -> 502 行 */
	mipi_dsi_dcs_write_seq_multi(&ctx, 0x2B, 0x00, 0x00, 0x01, 0xF5);

	/* 0x35: TE (Tearing Effect) ON */
	mipi_dsi_dcs_write_seq_multi(&ctx, 0x35, 0x00);

	/* 0x3A: Pixel Format RGB888 (24-bit) */
	mipi_dsi_dcs_write_seq_multi(&ctx, 0x3A, 0x77);

	/* 0x51: Display Brightness (0xFF Max) */
	mipi_dsi_dcs_write_seq_multi(&ctx, 0x51, 0xFF);

	/* 0x53: Write CTRL Display */
	mipi_dsi_dcs_write_seq_multi(&ctx, 0x53, 0x20);

	/* 0x29: Display ON */
	mipi_dsi_dcs_write_seq_multi(&ctx, 0x29);

	return ctx.accum_err;
}
/* ==================================================================== */

static int st7801_prepare(struct drm_panel *panel)
{
	struct st7801 *st7801 = to_st7801(panel);
	struct mipi_dsi_multi_context ctx = { .dsi = st7801->dsi };

	if (st7801->reset) {
		gpiod_set_value_cansleep(st7801->reset, 1);
		msleep(st7801->desc->pwr_timing->post_reset);
		gpiod_set_value_cansleep(st7801->reset, 0);
		msleep(st7801->desc->pwr_timing->reset_low);
		gpiod_set_value_cansleep(st7801->reset, 1);
		msleep(st7801->desc->pwr_timing->after_reset);
	}

	if (st7801->desc->do_sw_reset) {
		mipi_dsi_dcs_soft_reset_multi(&ctx);
		msleep(st7801->desc->pwr_timing->after_reset);
	}

	if (st7801->desc->init_sequence) {
		int ret = st7801->desc->init_sequence(st7801->dsi);
		if (ret)
			return ret;
	} else {
		mipi_dsi_dcs_exit_sleep_mode_multi(&ctx);
		msleep(st7801->desc->pwr_timing->slpout);
	}

	return ctx.accum_err;
}

static int st7801_enable(struct drm_panel *panel)
{
	struct mipi_dsi_multi_context ctx = { .dsi = to_mipi_dsi_device(panel->dev) };
	mipi_dsi_dcs_set_display_on_multi(&ctx);
	return ctx.accum_err;
}

static int st7801_disable(struct drm_panel *panel)
{
	struct mipi_dsi_multi_context ctx = { .dsi = to_mipi_dsi_device(panel->dev) };
	mipi_dsi_dcs_set_display_off_multi(&ctx);
	return ctx.accum_err;
}

static int st7801_unprepare(struct drm_panel *panel)
{
	struct st7801 *st7801 = to_st7801(panel);
	struct mipi_dsi_multi_context ctx = { .dsi = st7801->dsi };

	mipi_dsi_dcs_enter_sleep_mode_multi(&ctx);
	if (st7801->reset)
		gpiod_set_value_cansleep(st7801->reset, 0);

	return ctx.accum_err;
}

static int st7801_get_modes(struct drm_panel *panel, struct drm_connector *connector)
{
	struct st7801 *st7801 = to_st7801(panel);
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, st7801->desc->mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;

	drm_connector_set_orientation_from_panel(connector, panel);
	return 1;
}

static enum drm_panel_orientation st7801_get_orientation(struct drm_panel *panel)
{
	return to_st7801(panel)->orientation;
}

static const struct drm_panel_funcs st7801_funcs = {
	.prepare = st7801_prepare,
	.enable = st7801_enable,
	.disable = st7801_disable,
	.unprepare = st7801_unprepare,
	.get_modes = st7801_get_modes,
	.get_orientation = st7801_get_orientation,
};

static const struct drm_display_mode st7801_mode = {
	.clock = 14800,			/* 14.8 MHz */

	.hdisplay = 410,
	.hsync_start = 410 + 20,		/* hsync_front_porch = 20 */
	.hsync_end   = 410 + 20 + 4,		/* hsync_pulse_width = 4 */
	.htotal      = 410 + 20 + 4 + 20,	/* hsync_back_porch  = 20 -> HTotal: 454 */

	.vdisplay = 502,
	.vsync_start = 502 + 20,		/* vsync_front_porch = 20 */
	.vsync_end   = 502 + 20 + 4,		/* vsync_pulse_width = 4 */
	.vtotal      = 502 + 20 + 4 + 20,	/* vsync_back_porch  = 20 -> VTotal: 546 */

	.width_mm = 33,				/* 2.13寸 逻辑物理宽度 (mm) */
	.height_mm = 41,			/* 2.13寸 逻辑物理高度 (mm) */

	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
};

static const struct power_on_timing st7801_pwr_timing = {
	.post_reset = 20,
	.reset_low = 20,
	.after_reset = 120,
	.slpout = 400,
};

static const struct st7801_desc st7801_desc = {
	.mode = &st7801_mode,
	.lanes = 1,					/* 单通道 MIPI-DSI */
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.init_sequence = st7801_410x502_init_sequence,
	.pwr_timing = &st7801_pwr_timing,
	.do_sw_reset = true,
};

static int st7801_probe(struct mipi_dsi_device *dsi)
{
	struct st7801 *st7801;
	const struct st7801_desc *desc;
	int ret;

	st7801 = devm_kzalloc(&dsi->dev, sizeof(*st7801), GFP_KERNEL);
	if (!st7801)
		return -ENOMEM;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->mode_flags = desc->flags;
	dsi->format = desc->format;
	dsi->lanes = desc->lanes;

	st7801->panel.prepare_prev_first = true;
	st7801->reset = devm_gpiod_get_optional(&dsi->dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(st7801->reset)) {
		dev_err(&dsi->dev, "Failed to get reset GPIO\n");
		return PTR_ERR(st7801->reset);
	}

	ret = of_drm_get_panel_orientation(dsi->dev.of_node, &st7801->orientation);
	if (ret < 0)
		st7801->orientation = DRM_MODE_PANEL_ORIENTATION_NORMAL;

	drm_panel_init(&st7801->panel, &dsi->dev, &st7801_funcs, DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&st7801->panel);
	if (ret)
		return ret;

	drm_panel_add(&st7801->panel);

	mipi_dsi_set_drvdata(dsi, st7801);
	st7801->dsi = dsi;
	st7801->desc = desc;

	ret = mipi_dsi_attach(dsi);
	if (ret)
		drm_panel_remove(&st7801->panel);

	return ret;
}

static void st7801_remove(struct mipi_dsi_device *dsi)
{
	struct st7801 *st7801 = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_remove(&st7801->panel);
}

static const struct of_device_id st7801_of_match[] = {
	{ .compatible = "sitronix,st7801-410x502", .data = &st7801_desc },
	{ }
};
MODULE_DEVICE_TABLE(of, st7801_of_match);

static struct mipi_dsi_driver st7801_driver = {
	.probe = st7801_probe,
	.remove = st7801_remove,
	.driver = {
		.name = "panel-st7801-410x502",
		.of_match_table = st7801_of_match,
	},
};
module_mipi_dsi_driver(st7801_driver);

MODULE_AUTHOR("Adapted for ST7801 2.13-inch 410x502");
MODULE_DESCRIPTION("Sitronix ST7801 410x502 1-Lane MIPI-DSI Panel Driver");
MODULE_LICENSE("GPL");
