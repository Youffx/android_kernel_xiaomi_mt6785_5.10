# SPDX-License-Identifier: GPL-2.0
#
# Copyright (C) 2021 MediaTek Inc.
#

obj-$(CONFIG_MTK_CONNFEM) += connfem.o

ccflags-y += -D CONNFEM_DBG=0 -I$(src)/include

connfem-objs += connfem_module.o
connfem-objs += connfem_api.o
connfem-objs += connfem_container.o
connfem-objs += connfem_dt_parser.o
connfem-objs += connfem_epaelna.o
connfem-objs += connfem_subsys_bt.o
connfem-objs += connfem_subsys_wifi.o
