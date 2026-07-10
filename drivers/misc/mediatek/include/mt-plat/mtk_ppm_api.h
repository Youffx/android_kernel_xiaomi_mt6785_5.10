/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */
#ifndef __MT_PPM_API_H__
#define __MT_PPM_API_H__

#include <linux/types.h>
#include <linux/cpumask.h>

enum ppm_client {
	PPM_CLIENT_DVFS = 0,
	PPM_CLIENT_HOTPLUG,
	NR_PPM_CLIENTS,
};

struct ppm_client_req {
	unsigned int cluster_num;
	unsigned int root_cluster;
	bool is_ptp_policy_activate;
	unsigned int smart_detect;
	cpumask_var_t online_core;
	struct ppm_client_limit {
		unsigned int cluster_id;
		unsigned int cpu_id;
		int min_cpufreq_idx;
		int max_cpufreq_idx;
		unsigned int min_cpu_core;
		unsigned int max_cpu_core;
		bool has_advise_freq;
		bool has_advise_core;
		int advise_cpufreq_idx;
		int advise_cpu_core;
	} *cpu_limit;
};

struct ppm_limit_data {
	int min;
	int max;
};

extern void mt_ppm_register_client(enum ppm_client client,
	void (*limit)(struct ppm_client_req req));
extern void mt_ppm_cpu_thermal_protect(unsigned int limited_power);
extern unsigned int mt_ppm_thermal_get_min_power(void);
extern unsigned int mt_ppm_thermal_get_max_power(void);
extern unsigned int mt_ppm_thermal_get_cur_power(void);
extern unsigned int mt_ppm_userlimit_cpu_core(unsigned int cluster_num,
	struct ppm_limit_data *data);
extern unsigned int mt_ppm_userlimit_cpu_freq(unsigned int cluster_num,
	struct ppm_limit_data *data);
extern unsigned int mt_ppm_forcelimit_cpu_core(unsigned int cluster_num,
	struct ppm_limit_data *data);

/* PTPOD policy */
extern void mt_ppm_ptpod_policy_activate(void);
extern void mt_ppm_ptpod_policy_deactivate(void);

#endif
