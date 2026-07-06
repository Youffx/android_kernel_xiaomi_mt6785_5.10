ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat
ccflags-y += -I$(srctree)/drivers/misc/mediatek/base/power/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/base/power/include/upower_v2
ccflags-y += -I$(srctree)/drivers/misc/mediatek/base/power/eem_v2/$(MTK_PLATFORM)/inc
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/$(MTK_PLATFORM)/include/mach

obj-y += mtk_unified_power.o
obj-y += mtk_unified_power_internal.o
obj-y += mtk_unified_power_api.o
obj-$(CONFIG_MACH_MT6785) += mtk_unified_power_mt6785.o
