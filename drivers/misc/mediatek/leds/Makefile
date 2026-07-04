MTK_PLATFORM := $(subst ",,$(CONFIG_MTK_PLATFORM))

subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/$(MTK_PLATFORM)/include
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/base/power/$(MTK_PLATFORM)
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/base/power/include
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/leds/$(MTK_PLATFORM)

obj-$(CONFIG_MTK_LEDS) += mtk_leds_drv.o
obj-$(CONFIG_LEDS_MTK_DISP) += leds-mtk-disp.o
obj-$(CONFIG_LEDS_MTK_PWM) += leds-mtk-pwm.o
obj-$(CONFIG_LEDS_MTK_I2C) += leds-mtk-i2c.o

obj-$(CONFIG_MTK_LEDS) += $(MTK_PLATFORM)/
