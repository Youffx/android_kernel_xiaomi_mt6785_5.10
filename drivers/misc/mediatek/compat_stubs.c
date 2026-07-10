// SPDX-License-Identifier: GPL-2.0
// Stub implementations for MTK vendor symbols not compiled in 5.10

#include <linux/types.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>

/* Thermal base IO remap pointers */
#ifndef CONFIG_THERMAL
void __iomem *thermal_phy_base;
EXPORT_SYMBOL(thermal_phy_base);
void __iomem *auxadc_ts_base;
EXPORT_SYMBOL(auxadc_ts_base);
void __iomem *auxadc_ts_phy_base;
EXPORT_SYMBOL(auxadc_ts_phy_base);
void __iomem *infracfg_ao_base;
EXPORT_SYMBOL(infracfg_ao_base);
void __iomem *th_apmixed_base;
EXPORT_SYMBOL(th_apmixed_base);
void __iomem *apmixed_phy_base;
EXPORT_SYMBOL(apmixed_phy_base);
void __iomem *therm_main;
EXPORT_SYMBOL(therm_main);
void __iomem *thermal_base;
EXPORT_SYMBOL(thermal_base);
unsigned int thermal_irq_number;
EXPORT_SYMBOL(thermal_irq_number);
#endif

/* Thermal functions */
int __weak get_cpu_target_tj(void) { return 90000; }
EXPORT_SYMBOL(get_cpu_target_tj);
int __weak mtktscpu_limited_dmips(void) { return 0; }
EXPORT_SYMBOL(mtktscpu_limited_dmips);
int __weak tscpu_update_tempinfo(void) { return 0; }
EXPORT_SYMBOL(tscpu_update_tempinfo);
int __weak mtk_idle_notifier_register(void) { return -ENOSYS; }
EXPORT_SYMBOL(mtk_idle_notifier_register);
int __weak set_taklking_flag(void) { return 0; }
EXPORT_SYMBOL(set_taklking_flag);
int pd_get_opp_capacity(void) { return 0; }
EXPORT_SYMBOL(pd_get_opp_capacity);

/* SCP sensor hub */
int scp_power_monitor_register(void) { return -ENOSYS; }
EXPORT_SYMBOL(scp_power_monitor_register);
int scp_sensorHub_data_registration(void) { return -ENOSYS; }
EXPORT_SYMBOL(scp_sensorHub_data_registration);
int sensor_enable_to_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_enable_to_hub);
int sensor_disable_to_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_disable_to_hub);
int sensor_set_delay_to_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_set_delay_to_hub);
int sensor_batch_to_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_batch_to_hub);
int sensor_flush_to_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_flush_to_hub);
int sensor_cfg_to_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_cfg_to_hub);
int sensor_calibration_to_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_calibration_to_hub);
int sensor_selftest_to_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_selftest_to_hub);
int sensor_set_cmd_to_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_set_cmd_to_hub);
int sensor_get_data_from_hub(void) { return -ENOSYS; }
EXPORT_SYMBOL(sensor_get_data_from_hub);

/* CPU freq */
void mt_cpufreq_ctrl_cci_volt(unsigned int volt) { }
EXPORT_SYMBOL(mt_cpufreq_ctrl_cci_volt);
unsigned int mt_cpufreq_get_cpu_level(void) { return 0; }
EXPORT_SYMBOL(mt_cpufreq_get_cpu_level);
unsigned int mt_cpufreq_get_cur_volt(unsigned int id) { return 0; }
EXPORT_SYMBOL(mt_cpufreq_get_cur_volt);
unsigned int mt_cpufreq_get_freq_by_idx(unsigned int id, unsigned int idx) { return 0; }
EXPORT_SYMBOL(mt_cpufreq_get_freq_by_idx);
unsigned int mt_cpufreq_get_volt_by_idx(unsigned int id, unsigned int idx) { return 0; }
EXPORT_SYMBOL(mt_cpufreq_get_volt_by_idx);
int mt_cpufreq_update_volt(unsigned int id, unsigned int volt) { return 0; }
EXPORT_SYMBOL(mt_cpufreq_update_volt);

/* PPM */
void mt_ppm_ptpod_policy_activate(void) { }
EXPORT_SYMBOL(mt_ppm_ptpod_policy_activate);
void mt_ppm_ptpod_policy_deactivate(void) { }
EXPORT_SYMBOL(mt_ppm_ptpod_policy_deactivate);

/* Thermal limits */
unsigned int apthermolmt_get_cpu_power_limit(void) { return 0; }
EXPORT_SYMBOL(apthermolmt_get_cpu_power_limit);
unsigned int apthermolmt_get_gpu_power_limit(void) { return 0; }
EXPORT_SYMBOL(apthermolmt_get_gpu_power_limit);
unsigned int apthermolmt_get_vpu_power_limit(void) { return 0; }
EXPORT_SYMBOL(apthermolmt_get_vpu_power_limit);
int __weak is_cpu_power_unlimit(void) { return 1; }
EXPORT_SYMBOL(is_cpu_power_unlimit);
int get_target_tj(void) { return 90000; }
EXPORT_SYMBOL(get_target_tj);

/* Thermal PMIC */
void mtktspmic_debug_log(const char *fmt, ...) { }
EXPORT_SYMBOL(mtktspmic_debug_log);
int mtktspmic_cali_prepare(struct platform_device *pdev) { return 0; }
EXPORT_SYMBOL(mtktspmic_cali_prepare);
int mtktspmic_cali_prepare2(struct platform_device *pdev) { return 0; }
EXPORT_SYMBOL(mtktspmic_cali_prepare2);
int mtktspmic_get_from_dts(struct platform_device *pdev) { return 0; }
EXPORT_SYMBOL(mtktspmic_get_from_dts);
int mtktspmic_get_hw_temp(void) { return 25000; }
EXPORT_SYMBOL(mtktspmic_get_hw_temp);

/* ATM */
void atm_cancel_hrtimer(void) { }
EXPORT_SYMBOL(atm_cancel_hrtimer);
void atm_restart_hrtimer(void) { }
EXPORT_SYMBOL(atm_restart_hrtimer);
int tsatm_thermal_get_catm_type(void) { return 0; }
EXPORT_SYMBOL(tsatm_thermal_get_catm_type);

/* M4U */
int m4u_sec_context_init(void) { return 0; }
EXPORT_SYMBOL(m4u_sec_context_init);
int m4u_sec_context_deinit(void) { return 0; }
EXPORT_SYMBOL(m4u_sec_context_deinit);
void m4u_sec_set_context(void) { }
EXPORT_SYMBOL(m4u_sec_set_context);
int m4u_sec_ctx_get(unsigned int cmd) { return 0; }
EXPORT_SYMBOL(m4u_sec_ctx_get);
int m4u_sec_ctx_put(void *ctx) { return 0; }
EXPORT_SYMBOL(m4u_sec_ctx_put);
int m4u_exec_cmd(void *ctx) { return 0; }
EXPORT_SYMBOL(m4u_exec_cmd);

/* MAU */
int mau_get_config_info(void *cfg) { return 0; }
EXPORT_SYMBOL(mau_get_config_info);
int mau_start_monitor(int a, int b, int c, void *cfg) { return 0; }
EXPORT_SYMBOL(mau_start_monitor);
int mau_stop_monitor(int a, int b, int c, bool d) { return 0; }
EXPORT_SYMBOL(mau_stop_monitor);

/* IOMMU perf */
int iommu_perf_monitor_start(int a) { return 0; }
EXPORT_SYMBOL(iommu_perf_monitor_start);
int iommu_perf_monitor_stop(int a) { return 0; }
EXPORT_SYMBOL(iommu_perf_monitor_stop);
int iommu_perf_print_counter(int a, int b, const char *s) { return 0; }
EXPORT_SYMBOL(iommu_perf_print_counter);
int iommu_get_port_name(struct device *dev) { return 0; }
EXPORT_SYMBOL(iommu_get_port_name);

/* MTK IOMMU */
int mtk_iommu_atf_test(int a, int b) { return 0; }
EXPORT_SYMBOL(mtk_iommu_atf_test);
int mtk_iommu_dump_iova_space(struct device *dev) { return 0; }
EXPORT_SYMBOL(mtk_iommu_dump_iova_space);
int mtk_iommu_dump_reg(int a, int b, int c, const char *s) { return 0; }
EXPORT_SYMBOL(mtk_iommu_dump_reg);
int mtk_iommu_dump_sec_larb(int a, int b) { return 0; }
EXPORT_SYMBOL(mtk_iommu_dump_sec_larb);
int mtk_iommu_get_larb_port_count(int a) { return 0; }
EXPORT_SYMBOL(mtk_iommu_get_larb_port_count);
int mtk_iommu_get_pgtable_base_addr(unsigned long *pa) { return -ENOSYS; }
EXPORT_SYMBOL(mtk_iommu_get_pgtable_base_addr);
int mtk_iommu_get_port_id(struct device *dev) { return 0; }
EXPORT_SYMBOL(mtk_iommu_get_port_id);
int mtk_iommu_get_iova_space(struct device *dev, unsigned long *a, unsigned long *b, int c) { return 0; }
EXPORT_SYMBOL(mtk_iommu_get_iova_space);
int mtk_iommu_iova_to_pa(struct device *dev, int a, int b, unsigned long *c) { return 0; }
EXPORT_SYMBOL(mtk_iommu_iova_to_pa);
int mtk_iommu_power_support(struct device *dev) { return 0; }
EXPORT_SYMBOL(mtk_iommu_power_support);
int mtk_iommu_power_switch_by_id(struct device *dev, int a) { return 0; }
EXPORT_SYMBOL(mtk_iommu_power_switch_by_id);
int mtk_iommu_put_iova_space(struct device *dev, int a) { return 0; }
EXPORT_SYMBOL(mtk_iommu_put_iova_space);
int mtk_iommu_switch_acp(int a) { return 0; }
EXPORT_SYMBOL(mtk_iommu_switch_acp);
int mtk_iommu_switch_tf_test(int a) { return 0; }
EXPORT_SYMBOL(mtk_iommu_switch_tf_test);
void mtk_iommu_tlb_flush_all(struct device *dev) { }
EXPORT_SYMBOL(mtk_iommu_tlb_flush_all);
void mtk_iommu_trace_log(struct device *dev, const char *s, ...) { }
EXPORT_SYMBOL(mtk_iommu_trace_log);
void mtk_switch_secure_debug_func(void) { }
EXPORT_SYMBOL(mtk_switch_secure_debug_func);
void __mtk_dump_reg_for_hang_issue(int a, const char *s) { }
EXPORT_SYMBOL(__mtk_dump_reg_for_hang_issue);
void mtk_dump_reg_for_hang_issue(void *data) { }
EXPORT_SYMBOL(mtk_dump_reg_for_hang_issue);
void mtk_dump_main_tlb(int a, int b, void *c) { }
EXPORT_SYMBOL(mtk_dump_main_tlb);
void mtk_dump_pfh_tlb(int a, void *b) { }
EXPORT_SYMBOL(mtk_dump_pfh_tlb);
void mtk_dump_victim_tlb(int a, const char *s) { }
EXPORT_SYMBOL(mtk_dump_victim_tlb);

/* TCPU misc */
int __weak tscpu_cpu_dmips(int cpu) { return 0; }
EXPORT_SYMBOL(tscpu_cpu_dmips);
int __weak wakeup_ta_algo(int flow_state) { return 0; }
EXPORT_SYMBOL(wakeup_ta_algo);
int __weak report_custom_config_port(struct device *dev) { return 0; }
EXPORT_SYMBOL(report_custom_config_port);
int __weak report_custom_iommu_leakage(struct device *dev) { return 0; }
EXPORT_SYMBOL(report_custom_iommu_leakage);
int TARGET_TJS;
EXPORT_SYMBOL(TARGET_TJS);

/* Adaptive thermal */
int __weak adaptive_cpu_power_limit(int limit) { return 0; }
EXPORT_SYMBOL(adaptive_cpu_power_limit);
int __weak adaptive_gpu_power_limit(int limit) { return 0; }
EXPORT_SYMBOL(adaptive_gpu_power_limit);
const char *__weak adaptive_cooler_name(void) { return "stub"; }
EXPORT_SYMBOL(adaptive_cooler_name);
