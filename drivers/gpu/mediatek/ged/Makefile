#
# Copyright (C) 2015 MediaTek Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#

GED_TOP = $(srctree)/drivers/gpu/mediatek/ged
MTK_TOP = $(srctree)/drivers/misc/mediatek/
GPU_TOP = $(srctree)/drivers/gpu/mediatek/
VIDEOX_TOP = $(srctree)/drivers/misc/mediatek/video/$(MTK_PLATFORM)/videox

subdir-ccflags-y += -Wno-error

ccflags-y += \
        -Wno-unused-variable \
        -Wno-unused-function

# ccflags-y += -DMTK_CPUFREQ
# ccflags-y += -DGED_KPI_DEBUG
ccflags-y += -DMTK_GPUFREQ_V2
ccflags-y += -DMTK_GED_KPI
ccflags-y += -DMET_USER_EVENT_SUPPORT -DMTK_GPU_DVFS
ccflags-y += -DGED_DVFS_DEBUG_BUF
ccflags-y += -DMTK_GPU_BM_2

ifeq ($(CONFIG_MTK_ENABLE_GMO), y)
ccflags-y += -DGED_BUFFER_LOG_DISABLE
endif

ifeq ($(CONFIG_MTK_GPU_COMMON_DVFS_SUPPORT),y)
ccflags-y += -DENABLE_COMMON_DVFS \
             -DENABLE_TIMER_BACKUP
endif

ifeq ($(CONFIG_MTK_FTRACE_DEFAULT_ENABLE),y)
ccflags-y += -DENABLE_GED_SYSTRACE_UTIL
endif

ifeq ($(CONFIG_MTK_GPUFREQ_V2),y)
ccflags-y += -DGED_DCS_POLICY
endif

ifeq ($(CONFIG_MACH_MT6785),y)
ccflags-y += -DMTK_GED_KPI
ccflags-y += -DGED_KPI_CPU_BOOST
ifeq ($(CONFIG_MTK_GPU_COMMON_DVFS_SUPPORT),y)
ccflags-y += -DGED_ENABLE_FB_DVFS
ccflags-y += -DGED_ENABLE_DYNAMIC_DVFS_MARGIN
ccflags-y += -DGED_CONFIGURE_LOADING_BASE_DVFS_STEP
ccflags-y += -DGED_ENABLE_TIMER_BASED_DVFS_MARGIN
endif
ccflags-y += -I$(srctree)/drivers/misc/mediatek/cmdq/v3
ccflags-y += -I$(srctree)/drivers/misc/mediatek/cmdq/v3/mt6785
ccflags-y += \
	-I$(MTK_TOP)/base/power/mt6785/ \
	-I$(srctree)/drivers/misc/mediatek/video/mt6785/videox \
	-I$(srctree)/drivers/misc/mediatek/video/mt6785/dispsys \
	-I$(srctree)/drivers/misc/mediatek/sspm/mt6785
endif

ccflags-y += \
		-I$(srctree)/include/ \
		-I$(MTK_TOP)/include/ \
		-I$(GED_TOP)/include/ \
		-I$(GPU_TOP)/hal/ \
		-I$(GPU_TOP)/ \
		-I$(srctree)/drivers/misc/mediatek/lcm/inc/ \
		-I$(srctree)/drivers/gpu/mediatek/gpufreq/ \
		-I$(srctree)/drivers/gpu/mediatek/gpufreq/v1/include/ \
		-I$(srctree)/drivers/gpu/mediatek/gpufreq/v2/include/ \
		-I$(srctree)/drivers/misc/mediatek/performance/fpsgo_v3 \
		-I$(VIDEOX_TOP)/ \
		-I$(srctree)/drivers/gpu/drm/mediatek/mediatek_v2/ \
		-I$(srctree)/drivers/gpu/mediatek/gpueb/include/ \
		-I$(srctree)/drivers/dma-buf/heaps/
ccflags-y += \
		-I$(srctree)/drivers/misc/mediatek/cmdq/v3
ifeq ($(CONFIG_DEBUG_FS),y)
ccflags-y += -DGED_DEBUG_FS
ged-y += \
	src/ged_debugFS.o
endif

ged-y += \
	src/ged.o \
	src/ged_base.o \
	src/ged_main.o \
	src/ged_sysfs.o \
	src/ged_hal.o \
	src/ged_log.o \
	src/ged_bridge.o \
	src/ged_monitor_3D_fence.o \
	src/ged_hashtable.o \
	src/ged_thread.o

ged-$(CONFIG_SYNC_FILE) += src/ged_sync.o

obj-$(CONFIG_MTK_GPU_SUPPORT) += ged.o
