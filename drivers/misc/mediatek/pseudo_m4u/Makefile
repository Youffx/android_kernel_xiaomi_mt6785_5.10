# SPDX-License-Identifier: GPL-2.0
# Copyright (c) 2020 MediaTek Inc.

ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/$(MTK_PLATFORM)/include/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/pseudo_m4u/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/smi/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/geniezone/public
ccflags-y += -I$(srctree)/drivers/iommu
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/$(MTK_PLATFORM)/include/trustzone/m4u
ccflags-y += -I$(srctree)/drivers/misc/mediatek/mach/$(MTK_PLATFORM)/include/trustzone/m4u

ifneq (,$(filter $(strip $(CONFIG_MTK_PLATFORM)), "mt6785"))
obj-$(CONFIG_MTK_PSEUDO_M4U) += pseudo_m4u_v2.o pseudo_m4u_debug.o
ifeq ($(CONFIG_MTK_TEE_GP_SUPPORT),y)
ifneq (,$(filter y_n, $(CONFIG_MTK_SEC_VIDEO_PATH_SUPPORT)_$(CONFIG_MTK_SVP_ON_MTEE_SUPPORT)))
obj-$(CONFIG_MTK_PSEUDO_M4U) += pseudo_m4u_sec.o
else ifeq ($(CONFIG_MTK_CAM_SECURITY_SUPPORT),y)
obj-$(CONFIG_MTK_PSEUDO_M4U) += pseudo_m4u_sec.o
else ifeq ($(CONFIG_MTK_GZ_SUPPORT_SDSP),y)
obj-$(CONFIG_MTK_PSEUDO_M4U) += pseudo_m4u_sec.o
endif
endif
else
obj-$(CONFIG_MTK_PSEUDO_M4U) += pseudo_m4u.o
endif

ifeq ($(CONFIG_MTK_CAM_GENIEZONE_SUPPORT),y)
obj-$(CONFIG_MTK_PSEUDO_M4U) += pseudo_m4u_gz_sec.o
endif
ifeq ($(CONFIG_MTK_SVP_ON_MTEE_SUPPORT),y)
obj-$(CONFIG_MTK_PSEUDO_M4U) += pseudo_m4u_gz_sec.o
endif

ifeq ($(CONFIG_MTK_TRUSTED_MEMORY_SUBSYSTEM),y)
include $(srctree)/drivers/misc/mediatek/trusted_mem/Makefile.include
endif

obj-$(CONFIG_FPGA_EARLY_PORTING) += pseudo_m4u_ut.o
