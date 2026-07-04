ccflags-y += -I$(srctree)

ifeq ($(CONFIG_MACH_MT6785),y)
PDIR = mt6785
else
PDIR = $(CONFIG_MTK_PLATFORM)
endif

THERMAL_CHIP_DRIVER_DIR := $(srctree)/drivers/misc/mediatek/thermal/$(PDIR)
ccflags-y  += -I$(THERMAL_CHIP_DRIVER_DIR)/inc
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/include/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/thermal/fakeHeader/
ccflags-y  += -I$(srctree)/drivers/gpu/mediatek/gpufreq/include/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/gpu/hal/
ccflags-y  += -I$(srctree)/drivers/gpu/mediatek/gpufreq/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/base/power/$(PDIR)
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/base/power/include/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/base/power/include/gpufreq_v1/
ccflags-y  += -I$(srctree)/drivers/misc/mediatek/flashlight/

obj-$(CONFIG_MTK_LEGACY_THERMAL) += mtk_thermal_monitor.o
obj-$(CONFIG_MTK_LEGACY_THERMAL) += mtk_cooler_shutdown.o
obj-$(CONFIG_MTK_LEGACY_THERMAL) += mtk_cooler_kshutdown.o
obj-$(CONFIG_MTK_LEGACY_THERMAL) += mtk_cooler_cam.o
obj-$(CONFIG_MTK_LEGACY_THERMAL) += common/
obj-$(CONFIG_MTK_LEGACY_THERMAL) += $(PDIR)/
