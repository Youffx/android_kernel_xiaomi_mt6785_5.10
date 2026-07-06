# SPDX-License-Identifier: GPL-2.0
# Copyright (c) 2019 MediaTek Inc.

ifneq (,$(filter $(CONFIG_MTK_PLATFORM), "mt6785"))

THERMAL_CHIP_DRIVER_DIR := $(srctree)/drivers/misc/mediatek/thermal/mt6785
PDIR := mt6785

ccflags-y  += -I$(THERMAL_CHIP_DRIVER_DIR)/inc
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/base/power/$(PDIR)
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/base/power/include/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/include/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/gpu/hal/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/thermal/common/inc/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/base/power/eem_v1/inc/
ccflags-y  += -I$(srctree)/drivers/gpu/mediatek/gpufreq/include/
ccflags-y  += -I$(srctree)/drivers/gpu/mediatek/mt-plat/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/dramc/$(PDIR)
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/thermal/fakeHeader/

obj-$(CONFIG_THERMAL) += mtk_ts_battery.o
obj-$(CONFIG_THERMAL) += mtk_ts_bts.o
obj-$(CONFIG_THERMAL) += mtk_ts_btsmdpa.o
obj-$(CONFIG_THERMAL) += mtk_ts_cpu_noBank.o
obj-$(CONFIG_THERMAL) += mtk_ts_pa.o
obj-$(CONFIG_THERMAL) += mtk_ts_pa_thput.o
obj-$(CONFIG_THERMAL) += mtk_ts_pmic.o
obj-$(CONFIG_THERMAL) += mtk_ts_charger_v1.o

ifneq ($(CONFIG_MTK_COMBO_WIFI),)
ifneq ($(filter "MT76%", $(CONFIG_MTK_COMBO_CHIP)),)
    obj-$(CONFIG_THERMAL) += mtk_ts_wmt_766x.o
else
    obj-$(CONFIG_THERMAL) += mtk_ts_wmt.o
endif
endif

obj-$(CONFIG_THERMAL) += mtk_tsAll.o
obj-$(CONFIG_THERMAL) += mtk_ts_imgsensor.o

endif
