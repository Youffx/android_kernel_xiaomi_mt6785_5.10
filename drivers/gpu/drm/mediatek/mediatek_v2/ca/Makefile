#
#HDCP crypto ca
#

ifeq ($(CONFIG_TRUSTONIC_TEE_SUPPORT),y)
include $(srctree)/drivers/misc/mediatek/gud/Makefile.include
endif
ifeq ($(CONFIG_MICROTRUST_TEE_SUPPORT),y)
include $(srctree)/drivers/misc/mediatek/teei/Makefile.include
endif

# Youffx: tlcDpHdcp.o needs MicroTrust TEE (unported), skip until TEE backend is available
# obj-y += tlcDpHdcp.o
#ccflags-y += -DHDCP_SETKEY_FROM_KERNEL
