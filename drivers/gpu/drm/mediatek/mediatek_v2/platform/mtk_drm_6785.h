/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#ifndef MTK_DRM_6785_H
#define MTK_DRM_6785_H

#include <linux/clk.h>
#include <linux/iopoll.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/regmap.h>

#ifndef DRM_CMDQ_DISABLE
#include <linux/soc/mediatek/mtk-cmdq-ext.h>
#else
#include "../mtk-cmdq-ext.h"
#endif

#include "../mtk_drm_ddp.h"
#include "../mtk_drm_crtc.h"
#include "../mtk_drm_drv.h"
#include "../mtk_drm_ddp_comp.h"
#include "../mtk_dump.h"
#include "../mtk_disp_ovl.h"
#include "../mtk_disp_wdma.h"
#include "../mtk_mipi_tx.h"
#include "../mtk_disp_dsc.h"
#include "../mtk_disp_postmask.h"
#include "../mtk_disp_rdma.h"
#include "../mtk_disp_rsz.h"
#include "../mtk_disp_aal.h"
#include "../mtk_disp_ccorr.h"
#include "../mtk_disp_color.h"
#include "../mtk_disp_dither.h"
#include "../mtk_dsi.h"

#define MT6785_DISP_OVL0_MOUT_EN		0xf08
#define MT6785_DISP_OVL0_2L_MOUT_EN		0xf04

#define MT6785_DISP_REG_CONFIG_DISP_OVL0_2L_MOUT_EN	0xf04
#define MT6785_DISP_REG_CONFIG_DISP_OVL0_MOUT_EN	0xf08
#define MT6785_DISP_REG_CONFIG_DISP_RSZ0_MOUT_EN	0xf10
#define MT6785_DISP_REG_CONFIG_DISP_DITHER0_MOUT_EN	0xf00

#define MT6785_DISP_REG_CONFIG_DISP_RSZ0_SEL_IN		0xf7c
#define MT6785_DISP_REG_CONFIG_DISP_RDMA0_SEL_IN	0xf78
#define MT6785_DISP_REG_CONFIG_DSI0_SEL_IN		0xf8c
#define MT6785_DISP_REG_CONFIG_DISP_WDMA0_SEL_IN	0xf84

#define MT6785_DISP_REG_CONFIG_DISP_RDMA0_SOUT_SEL_IN	0xf44
#define MT6785_DISP_REG_CONFIG_DISP_RDMA0_RSZ_IN_SOUT_SEL_IN	0xf40
#define MT6785_DISP_REG_CONFIG_DISP_COLOR_OUT_SEL_IN	0xf68
#define MT6785_DISP_REG_CONFIG_DPI0_SEL_IN		0xf88

#define MT6785_OVL0_2L_MOUT_TO_DISP_RDMA0_SEL		BIT(0)
#define MT6785_OVL0_2L_MOUT_TO_DISP_RSZ0_SEL		BIT(1)
#define MT6785_OVL0_2L_MOUT_TO_DISP_WDMA0_SEL		BIT(2)

#define MT6785_OVL0_MOUT_TO_DISP_RDMA0_SEL		BIT(0)
#define MT6785_OVL0_MOUT_TO_DISP_RSZ0_SEL		BIT(1)
#define MT6785_OVL0_MOUT_TO_DISP_WDMA0_SEL		BIT(2)

#define MT6785_RSZ0_MOUT_TO_DISP_RDMA0_SEL		BIT(0)
#define MT6785_RSZ0_MOUT_TO_DISP_WDMA0_SEL		BIT(1)

#define MT6785_DITHER0_MOUT_TO_DISP_DSI0_SEL		BIT(0)
#define MT6785_DITHER0_MOUT_TO_DISP_WDMA0_SEL		BIT(1)

#define MT6785_RSZ0_FROM_DISP_OVL0_2L			(0)
#define MT6785_RSZ0_FROM_DISP_OVL0			(1)

#define MT6785_SEL_IN_RDMA0_FROM_DISP_OVL0		(0)
#define MT6785_SEL_IN_RDMA0_FROM_DISP_RSZ0		(1)
#define MT6785_SEL_IN_RDMA0_FROM_DISP_OVL0_2L		(2)

#define MT6785_SEL_IN_DSI0_FROM_DISP_RDMA0_SOUT		(0)
#define MT6785_SEL_IN_DSI0_FROM_DISP_DITHER0		(1)

#define MT6785_WDMA0_SEL_IN_FROM_DISP_DITHER0		(0)
#define MT6785_WDMA0_SEL_IN_FROM_DISP_RSZ0		(1)
#define MT6785_WDMA0_SEL_IN_FROM_DISP_OVL0_2L		(2)
#define MT6785_WDMA0_SEL_IN_FROM_DISP_OVL0		(3)

#define MT6785_RDMA0_SOUT_TO_DISP_COLOR0		BIT(0)

#define MT6785_DISP_MUTEX0_MOD0	0x30
#define MT6785_DISP_MUTEX0_SOF	0x2c

#define MT6785_MUTEX_MOD_DISP_OVL0		BIT(0)
#define MT6785_MUTEX_MOD_DISP_OVL0_2L		BIT(1)
#define MT6785_MUTEX_MOD_DISP_RDMA0		BIT(2)
#define MT6785_MUTEX_MOD_DISP_RSZ0		BIT(3)
#define MT6785_MUTEX_MOD_DISP_COLOR0		BIT(4)
#define MT6785_MUTEX_MOD_DISP_CCORR0		BIT(5)
#define MT6785_MUTEX_MOD_DISP_AAL0		BIT(7)
#define MT6785_MUTEX_MOD_DISP_GAMMA0		BIT(8)
#define MT6785_MUTEX_MOD_DISP_POSTMASK0		BIT(9)
#define MT6785_MUTEX_MOD_DISP_DITHER0		BIT(10)
#define MT6785_MUTEX_MOD_DISP_DSI0		BIT(14)
#define MT6785_MUTEX_MOD_DISP_WDMA0		BIT(15)
#define MT6785_MUTEX_MOD_DISP_PWM0		BIT(16)

#define MT6785_MUTEX_SOF_SINGLE_MODE	0
#define MT6785_MUTEX_SOF_DSI0		1
#define MT6785_MUTEX_EOF_DSI0		(MT6785_MUTEX_SOF_DSI0 << 6)

extern const struct mtk_disp_ovl_data mt6785_ovl_driver_data;
extern const struct mtk_disp_wdma_data mt6785_wdma_driver_data;
extern const struct mtk_disp_rdma_data mt6785_rdma_driver_data;
extern const struct mtk_disp_rsz_data mt6785_rsz_driver_data;
extern const struct mtk_disp_postmask_data mt6785_postmask_driver_data;
extern const struct mtk_disp_aal_data mt6785_aal_driver_data;
extern const struct mtk_disp_ccorr_data mt6785_ccorr_driver_data;
extern const struct mtk_disp_color_data mt6785_color_driver_data;
extern const struct mtk_disp_dither_data mt6785_dither_driver_data;
extern const struct mtk_dsi_driver_data mt6785_dsi_driver_data;
extern const struct mtk_mmsys_driver_data mt6785_mmsys_driver_data;
extern const struct mtk_disp_ddp_data mt6785_ddp_driver_data;
extern const struct mtk_mmsys_reg_data mt6785_mmsys_reg_data;
extern const struct mtk_mipitx_data mt6785_mipitx_data;

int mtk_ddp_mout_en_MT6785(const struct mtk_mmsys_reg_data *data,
			   enum mtk_ddp_comp_id cur, enum mtk_ddp_comp_id next,
			   unsigned int *addr);
int mtk_ddp_sel_in_MT6785(const struct mtk_mmsys_reg_data *data,
			  enum mtk_ddp_comp_id cur, enum mtk_ddp_comp_id next,
			  unsigned int *addr);
int mtk_ddp_sout_sel_MT6785(const struct mtk_mmsys_reg_data *data,
			    enum mtk_ddp_comp_id cur, enum mtk_ddp_comp_id next,
			    unsigned int *addr);
int mtk_ddp_ovl_bg_blend_en_MT6785(const struct mtk_mmsys_reg_data *data,
			   enum mtk_ddp_comp_id cur, enum mtk_ddp_comp_id next,
			   unsigned int *addr);
void mutex_dump_analysis_mt6785(struct mtk_disp_mutex *mutex);
void mmsys_config_dump_analysis_mt6785(void __iomem *config_regs);
#endif /* MTK_DRM_6785_H */
