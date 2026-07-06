/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */
#ifndef __MT_CPUFREQ_H__
#define __MT_CPUFREQ_H__

#include <linux/types.h>

extern void mt_cpufreq_thermal_protect(unsigned int limited_power);
extern void mt_cpufreq_thermal_5A_limit(bool enable);
extern unsigned int mt_cpufreq_get_max_power(void);
extern unsigned int mt_cpufreq_get_min_power(void);

#endif
