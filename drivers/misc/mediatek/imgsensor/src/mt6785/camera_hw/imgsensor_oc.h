/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifndef __IMGSENSOR_OC_H__
#define __IMGSENSOR_OC_H__

#include "imgsensor_common.h"

enum IMGSENSOR_RETURN imgsensor_oc_init(void);
enum IMGSENSOR_RETURN imgsensor_oc_interrupt(
	enum IMGSENSOR_HW_POWER_STATUS pwr_status);

#endif
