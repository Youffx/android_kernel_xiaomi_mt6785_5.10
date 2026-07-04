// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifndef ___MT_GPUFREQ_INTERNAL_PLAT_H___
#define ___MT_GPUFREQ_INTERNAL_PLAT_H___

#define MT_GPUFREQ_POWER_CTL_ENABLE	1

#define MT_GPUFREQ_DVFS_ENABLE          0
#define MT_GPUFREQ_CUST_CONFIG          0
#define MT_GPUFREQ_CUST_INIT_OPP        (g_opp_table_segment_1[20].gpufreq_khz)

#define NUM_OF_OPP_IDX (sizeof(g_opp_table_segment_1) / \
			sizeof(g_opp_table_segment_1[0]))

#define FIXED_VSRAM_VOLT                (85000)
#define FIXED_VSRAM_VOLT_THSRESHOLD     (75000)
#define FIXED_VSRAM_VOLT_DIFF           (10000)

#define VGPU_MAX_VOLT                   (95000)
#define VGPU_MIN_VOLT                   (57500)
#define VSRAM_GPU_MAX_VOLT              (105000)
#define VSRAM_GPU_MIN_VOLT              (85000)
#define PMIC_STEP                       (625)

#define BUCK_DIFF_MAX                   (35000)
#define BUCK_DIFF_MIN                   (00000)

#define POSDIV_4_MAX_FREQ               (950000)
#define POSDIV_4_MIN_FREQ               (375000)
#define POSDIV_8_MAX_FREQ               (475000)
#define POSDIV_8_MIN_FREQ               (187500)
#define POSDIV_SHIFT                    (24)
#define DDS_SHIFT                       (14)
#define TO_MHZ_HEAD                     (100)
#define TO_MHZ_TAIL                     (10)
#define ROUNDING_VALUE                  (5)
#define MFGPLL_FIN                      (26)
#define MFGPLL_FH_PLL                   (4)
#define MFGPLL_CON1                     (g_apmixed_base + 0x254)

#define GPU_ACT_REF_POWER               (1285)
#define GPU_ACT_REF_FREQ                (900000)
#define GPU_ACT_REF_VOLT                (90000)
#define PTPOD_DISABLE_VOLT              (80000)

#define MT_GPUFREQ_BATT_OC_PROTECT              1
#define MT_GPUFREQ_BATT_OC_LIMIT_FREQ           (485000)

#define MT_GPUFREQ_BATT_PERCENT_PROTECT         0
#define MT_GPUFREQ_BATT_PERCENT_LIMIT_FREQ      (485000)

#define MT_GPUFREQ_LOW_BATT_VOLT_PROTECT        1
#define MT_GPUFREQ_LOW_BATT_VOLT_LIMIT_FREQ     (485000)

#define MT_GPUFREQ_DFD_ENABLE 0
#define MT_GPUFREQ_DFD_DEBUG 0

#define READ_REGISTER_UINT32(reg)	\
	(*(unsigned int * const)(reg))
#define WRITE_REGISTER_UINT32(reg, val)	\
	((*(unsigned int * const)(reg)) = (val))
#define INREG32(x)	\
	READ_REGISTER_UINT32((unsigned int *)((void *)(x)))
#define OUTREG32(x, y)	\
	WRITE_REGISTER_UINT32((unsigned int *)((void *)(x)), (unsigned int)(y))
#define SETREG32(x, y)	\
	OUTREG32(x, INREG32(x)|(y))
#define CLRREG32(x, y)	\
	OUTREG32(x, INREG32(x)&~(y))
#define MASKREG32(x, y, z)	\
	OUTREG32(x, (INREG32(x)&~(y))|(z))
#define DRV_Reg32(addr)				INREG32(addr)
#define DRV_WriteReg32(addr, data)	OUTREG32(addr, data)
#define DRV_SetReg32(addr, data)	SETREG32(addr, data)
#define DRV_ClrReg32(addr, data)	CLRREG32(addr, data)

#ifdef CONFIG_PROC_FS
#define PROC_FOPS_RW(name)	\
	static int mt_ ## name ## _proc_open(	\
			struct inode *inode,	\
			struct file *file)	\
	{	\
		return single_open(	\
				file,	\
				mt_ ## name ## _proc_show,	\
				PDE_DATA(inode));	\
	}	\
	static const struct proc_ops mt_ ## name ## _proc_fops =	\
	{	\
		.proc_open = mt_ ## name ## _proc_open,	\
		.proc_read = seq_read,	\
		.proc_lseek = seq_lseek,	\
		.proc_release = single_release,	\
		.proc_write = mt_ ## name ## _proc_write,	\
	}
#define PROC_FOPS_RO(name)	\
	static int mt_ ## name ## _proc_open(	\
			struct inode *inode,	\
			struct file *file)	\
	{	\
		return single_open(	\
				file,	\
				mt_ ## name ## _proc_show,	\
				PDE_DATA(inode));	\
	}	\
	static const struct proc_ops mt_ ## name ## _proc_fops =	\
	{	\
		.proc_open = mt_ ## name ## _proc_open,	\
		.proc_read = seq_read,	\
		.proc_lseek = seq_lseek,	\
		.proc_release = single_release,	\
	}
#define PROC_ENTRY(name) \
	{__stringify(name), &mt_ ## name ## _proc_fops}
#endif

#define VOLT_NORMALIZATION(volt)	\
	((volt % 625) ? (volt - (volt % 625) + 625) : volt)
#ifndef MIN
#define MIN(x, y)	(((x) < (y)) ? (x) : (y))
#endif

#define GPUOP(khz, vgpu, vsram, post_divider, aging_margin)	\
	{							\
		.gpufreq_khz = khz,				\
		.gpufreq_vgpu = vgpu,				\
		.gpufreq_vsram = vsram,				\
		.gpufreq_post_divider = post_divider,		\
		.gpufreq_aging_margin = aging_margin,		\
	}

enum g_segment_id_enum {
	MT6785U_SEGMENT = 1,
	MT6785T_SEGMENT,
	MT6785_SEGMENT,
	MT6783_SEGMENT,
};

enum g_posdiv_power_enum  {
	POSDIV_POWER_1 = 0,
	POSDIV_POWER_2,
	POSDIV_POWER_4,
	POSDIV_POWER_8,
	POSDIV_POWER_16,
};
enum g_clock_source_enum  {
	CLOCK_MAIN = 0,
	CLOCK_SUB,
};

enum g_limit_enable_enum  {
	LIMIT_DISABLE = 0,
	LIMIT_ENABLE,
};

enum {
	GPUFREQ_LIMIT_PRIO_NONE,
	GPUFREQ_LIMIT_PRIO_1,
	GPUFREQ_LIMIT_PRIO_2,
	GPUFREQ_LIMIT_PRIO_3,
	GPUFREQ_LIMIT_PRIO_4,
	GPUFREQ_LIMIT_PRIO_5,
	GPUFREQ_LIMIT_PRIO_6,
	GPUFREQ_LIMIT_PRIO_7,
	GPUFREQ_LIMIT_PRIO_8
};

struct gpudvfs_limit {
	unsigned int kicker;
	char *name;
	unsigned int prio;
	unsigned int upper_idx;
	unsigned int upper_enable;
	unsigned int lower_idx;
	unsigned int lower_enable;
};

#define LIMIT_IDX_DEFAULT -1

struct gpudvfs_limit limit_table[] = {
	{KIR_STRESS,		"STRESS",	GPUFREQ_LIMIT_PRIO_8,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_PROC,			"PROC",		GPUFREQ_LIMIT_PRIO_7,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_PTPOD,			"PTPOD",	GPUFREQ_LIMIT_PRIO_6,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_THERMAL,		"THERMAL",	GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_BATT_OC,		"BATT_OC",	GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_BATT_LOW,		"BATT_LOW",	GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_BATT_PERCENT,	"BATT_PERCENT",	GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_PBM,			"PBM",		GPUFREQ_LIMIT_PRIO_5,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
	{KIR_POLICY,		"POLICY",	GPUFREQ_LIMIT_PRIO_4,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE,
		LIMIT_IDX_DEFAULT, LIMIT_ENABLE},
};

struct opp_table_info {
	unsigned int gpufreq_khz;
	unsigned int gpufreq_vgpu;
	unsigned int gpufreq_vsram;
	enum g_posdiv_power_enum gpufreq_post_divider;
	unsigned int gpufreq_aging_margin;
};
struct g_clk_info {
	struct clk *clk_mux;
	struct clk *clk_main_parent;
	struct clk *clk_sub_parent;
	struct clk *subsys_bg3d;
};
struct g_pmic_info {
	struct regulator *reg_vgpu;
	struct regulator *reg_vsram_gpu;
};

extern bool mtk_get_gpu_loading(unsigned int *pLoading);
extern unsigned int mt_get_abist_freq(unsigned int idx);

struct opp_table_info *g_opp_table;

unsigned int g_ptpod_opp_idx_table_segment[] = {
	 0, 12, 15, 18,
	20, 22, 24, 26,
	28, 30, 32, 34,
	36, 38, 40, 42
};

struct opp_table_info g_opp_table_segment_1[] = {
	GPUOP(900000, 87500, 97500, POSDIV_POWER_4, 0),
	GPUOP(897000, 86875, 96875, POSDIV_POWER_4, 0),
	GPUOP(892000, 86250, 96250, POSDIV_POWER_4, 0),
	GPUOP(888000, 85625, 95625, POSDIV_POWER_4, 0),
	GPUOP(884000, 85000, 95000, POSDIV_POWER_4, 0),
	GPUOP(880000, 84375, 94375, POSDIV_POWER_4, 0),
	GPUOP(875000, 83750, 93750, POSDIV_POWER_4, 0),
	GPUOP(871000, 83125, 93125, POSDIV_POWER_4, 0),
	GPUOP(867000, 82500, 92500, POSDIV_POWER_4, 0),
	GPUOP(862000, 81875, 91875, POSDIV_POWER_4, 0),
	GPUOP(858000, 81250, 91250, POSDIV_POWER_4, 0),
	GPUOP(854000, 80625, 90625, POSDIV_POWER_4, 0),
	GPUOP(850000, 80000, 90000, POSDIV_POWER_4, 0),
	GPUOP(835000, 79375, 89375, POSDIV_POWER_4, 0),
	GPUOP(821000, 78750, 88750, POSDIV_POWER_4, 0),
	GPUOP(806000, 78125, 88125, POSDIV_POWER_4, 0),
	GPUOP(792000, 77500, 87500, POSDIV_POWER_4, 0),
	GPUOP(778000, 76875, 86875, POSDIV_POWER_4, 0),
	GPUOP(763000, 76250, 86250, POSDIV_POWER_4, 0),
	GPUOP(749000, 75625, 85625, POSDIV_POWER_4, 0),
	GPUOP(735000, 75000, 85000, POSDIV_POWER_4, 0),
	GPUOP(720000, 74375, 85000, POSDIV_POWER_4, 0),
	GPUOP(706000, 73750, 85000, POSDIV_POWER_4, 0),
	GPUOP(691000, 73125, 85000, POSDIV_POWER_4, 0),
	GPUOP(677000, 72500, 85000, POSDIV_POWER_4, 0),
	GPUOP(663000, 71875, 85000, POSDIV_POWER_4, 0),
	GPUOP(648000, 71250, 85000, POSDIV_POWER_4, 0),
	GPUOP(634000, 70625, 85000, POSDIV_POWER_4, 0),
	GPUOP(620000, 70000, 85000, POSDIV_POWER_4, 0),
	GPUOP(595000, 69375, 85000, POSDIV_POWER_4, 0),
	GPUOP(570000, 68750, 85000, POSDIV_POWER_4, 0),
	GPUOP(545000, 68125, 85000, POSDIV_POWER_4, 0),
	GPUOP(520000, 67500, 85000, POSDIV_POWER_4, 0),
	GPUOP(495000, 66875, 85000, POSDIV_POWER_4, 0),
	GPUOP(470000, 66250, 85000, POSDIV_POWER_4, 0),
	GPUOP(445000, 65625, 85000, POSDIV_POWER_4, 0),
	GPUOP(420000, 65000, 85000, POSDIV_POWER_4, 0),
	GPUOP(395000, 64375, 85000, POSDIV_POWER_4, 0),
	GPUOP(370000, 63750, 85000, POSDIV_POWER_8, 0),
	GPUOP(345000, 63125, 85000, POSDIV_POWER_8, 0),
	GPUOP(320000, 62500, 85000, POSDIV_POWER_8, 0),
	GPUOP(295000, 61875, 85000, POSDIV_POWER_8, 0),
	GPUOP(270000, 61250, 85000, POSDIV_POWER_8, 0),
};

struct opp_table_info g_opp_table_segment_2[] = {
	GPUOP(900000, 87500, 97500, POSDIV_POWER_4, 0),
	GPUOP(897000, 86875, 96875, POSDIV_POWER_4, 0),
	GPUOP(892000, 86250, 96250, POSDIV_POWER_4, 0),
	GPUOP(888000, 85625, 95625, POSDIV_POWER_4, 0),
	GPUOP(884000, 85000, 95000, POSDIV_POWER_4, 0),
	GPUOP(880000, 84375, 94375, POSDIV_POWER_4, 0),
	GPUOP(875000, 83750, 93750, POSDIV_POWER_4, 0),
	GPUOP(871000, 83125, 93125, POSDIV_POWER_4, 0),
	GPUOP(867000, 82500, 92500, POSDIV_POWER_4, 0),
	GPUOP(862000, 81875, 91875, POSDIV_POWER_4, 0),
	GPUOP(858000, 81250, 91250, POSDIV_POWER_4, 0),
	GPUOP(854000, 80625, 90625, POSDIV_POWER_4, 0),
	GPUOP(850000, 80000, 90000, POSDIV_POWER_4, 0),
	GPUOP(835000, 79375, 89375, POSDIV_POWER_4, 0),
	GPUOP(821000, 78750, 88750, POSDIV_POWER_4, 0),
	GPUOP(806000, 78125, 88125, POSDIV_POWER_4, 0),
	GPUOP(792000, 77500, 87500, POSDIV_POWER_4, 0),
	GPUOP(778000, 76875, 86875, POSDIV_POWER_4, 0),
	GPUOP(763000, 76250, 86250, POSDIV_POWER_4, 0),
	GPUOP(749000, 75625, 85625, POSDIV_POWER_4, 0),
	GPUOP(735000, 75000, 85000, POSDIV_POWER_4, 0),
	GPUOP(720000, 74375, 85000, POSDIV_POWER_4, 0),
	GPUOP(706000, 73750, 85000, POSDIV_POWER_4, 0),
	GPUOP(691000, 73125, 85000, POSDIV_POWER_4, 0),
	GPUOP(677000, 72500, 85000, POSDIV_POWER_4, 0),
	GPUOP(663000, 71875, 85000, POSDIV_POWER_4, 0),
	GPUOP(648000, 71250, 85000, POSDIV_POWER_4, 0),
	GPUOP(634000, 70625, 85000, POSDIV_POWER_4, 0),
	GPUOP(620000, 70000, 85000, POSDIV_POWER_4, 0),
	GPUOP(595000, 69375, 85000, POSDIV_POWER_4, 0),
	GPUOP(570000, 68750, 85000, POSDIV_POWER_4, 0),
	GPUOP(545000, 68125, 85000, POSDIV_POWER_4, 0),
	GPUOP(520000, 67500, 85000, POSDIV_POWER_4, 0),
	GPUOP(495000, 66875, 85000, POSDIV_POWER_4, 0),
	GPUOP(470000, 66250, 85000, POSDIV_POWER_4, 0),
	GPUOP(445000, 65625, 85000, POSDIV_POWER_4, 0),
	GPUOP(420000, 65000, 85000, POSDIV_POWER_4, 0),
	GPUOP(395000, 64375, 85000, POSDIV_POWER_4, 0),
	GPUOP(370000, 63750, 85000, POSDIV_POWER_8, 0),
	GPUOP(345000, 63125, 85000, POSDIV_POWER_8, 0),
	GPUOP(320000, 62500, 85000, POSDIV_POWER_8, 0),
	GPUOP(295000, 61875, 85000, POSDIV_POWER_8, 0),
	GPUOP(270000, 61250, 85000, POSDIV_POWER_8, 0),
};

struct opp_table_info g_opp_table_segment_3[] = {
	GPUOP(900000, 87500, 97500, POSDIV_POWER_4, 0),
	GPUOP(897000, 86875, 96875, POSDIV_POWER_4, 0),
	GPUOP(892000, 86250, 96250, POSDIV_POWER_4, 0),
	GPUOP(888000, 85625, 95625, POSDIV_POWER_4, 0),
	GPUOP(884000, 85000, 95000, POSDIV_POWER_4, 0),
	GPUOP(880000, 84375, 94375, POSDIV_POWER_4, 0),
	GPUOP(875000, 83750, 93750, POSDIV_POWER_4, 0),
	GPUOP(871000, 83125, 93125, POSDIV_POWER_4, 0),
	GPUOP(867000, 82500, 92500, POSDIV_POWER_4, 0),
	GPUOP(862000, 81875, 91875, POSDIV_POWER_4, 0),
	GPUOP(858000, 81250, 91250, POSDIV_POWER_4, 0),
	GPUOP(854000, 80625, 90625, POSDIV_POWER_4, 0),
	GPUOP(850000, 80000, 90000, POSDIV_POWER_4, 0),
	GPUOP(835000, 79375, 89375, POSDIV_POWER_4, 0),
	GPUOP(821000, 78750, 88750, POSDIV_POWER_4, 0),
	GPUOP(806000, 78125, 88125, POSDIV_POWER_4, 0),
	GPUOP(792000, 77500, 87500, POSDIV_POWER_4, 0),
	GPUOP(778000, 76875, 86875, POSDIV_POWER_4, 0),
	GPUOP(763000, 76250, 86250, POSDIV_POWER_4, 0),
	GPUOP(749000, 75625, 85625, POSDIV_POWER_4, 0),
	GPUOP(735000, 75000, 85000, POSDIV_POWER_4, 0),
	GPUOP(720000, 74375, 85000, POSDIV_POWER_4, 0),
	GPUOP(706000, 73750, 85000, POSDIV_POWER_4, 0),
	GPUOP(691000, 73125, 85000, POSDIV_POWER_4, 0),
	GPUOP(677000, 72500, 85000, POSDIV_POWER_4, 0),
	GPUOP(663000, 71875, 85000, POSDIV_POWER_4, 0),
	GPUOP(648000, 71250, 85000, POSDIV_POWER_4, 0),
	GPUOP(634000, 70625, 85000, POSDIV_POWER_4, 0),
	GPUOP(620000, 70000, 85000, POSDIV_POWER_4, 0),
	GPUOP(595000, 69375, 85000, POSDIV_POWER_4, 0),
	GPUOP(570000, 68750, 85000, POSDIV_POWER_4, 0),
	GPUOP(545000, 68125, 85000, POSDIV_POWER_4, 0),
	GPUOP(520000, 67500, 85000, POSDIV_POWER_4, 0),
	GPUOP(495000, 66875, 85000, POSDIV_POWER_4, 0),
	GPUOP(470000, 66250, 85000, POSDIV_POWER_4, 0),
	GPUOP(445000, 65625, 85000, POSDIV_POWER_4, 0),
	GPUOP(420000, 65000, 85000, POSDIV_POWER_4, 0),
	GPUOP(395000, 64375, 85000, POSDIV_POWER_4, 0),
	GPUOP(370000, 63750, 85000, POSDIV_POWER_8, 0),
	GPUOP(345000, 63125, 85000, POSDIV_POWER_8, 0),
	GPUOP(320000, 62500, 85000, POSDIV_POWER_8, 0),
	GPUOP(295000, 61875, 85000, POSDIV_POWER_8, 0),
	GPUOP(270000, 61250, 85000, POSDIV_POWER_8, 0),
};

#endif /* ___MT_GPUFREQ_INTERNAL_PLAT_H___ */
