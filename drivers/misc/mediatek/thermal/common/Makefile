ifeq ($(CONFIG_MACH_MT6785),y)
PDIR = mt6785
else
PDIR = $(CONFIG_MTK_PLATFORM)
endif

THERMAL_CHIP_DRIVER_DIR := $(srctree)/drivers/misc/mediatek/thermal/$(PDIR)
ccflags-y  += -I$(THERMAL_CHIP_DRIVER_DIR)/inc
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/base/power/$(PDIR)
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/base/power/include/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/include/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/gpu/hal/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/thermal/fakeHeader/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/thermal/common/inc/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/base/power/eem_v1/inc/
ccflags-y  += -I$(srctree)/drivers/gpu/mediatek/gpufreq/include/

obj-$(CONFIG_MTK_LEGACY_THERMAL) += mtk_thermal_platform.o
# obj-$(CONFIG_MTK_LEGACY_THERMAL) += ap_thermal_limit.o
obj-$(CONFIG_MTK_LEGACY_THERMAL) += mtk_thermal_timer.o
obj-$(CONFIG_MTK_LEGACY_THERMAL) += thermal_zones/
