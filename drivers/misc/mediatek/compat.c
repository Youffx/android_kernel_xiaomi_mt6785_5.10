/* Youffx: stub implementations for MTK vendor symbols not compiled in 5.10 */

/* KREE (GenieZone TrustZone) */
#include <linux/types.h>
#include <linux/module.h>
#include <linux/device.h>

int KREE_CreateSession(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_CreateSession);
int KREE_CloseSession(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_CloseSession);
int KREE_TeeServiceCall(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_TeeServiceCall);
int KREE_TeeServiceCallPlus(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_TeeServiceCallPlus);
int KREE_RegisterSharedmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_RegisterSharedmem);
int KREE_UnregisterSharedmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_UnregisterSharedmem);
int KREE_AppendSecureMultichunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_AppendSecureMultichunkmem);
int KREE_ReleaseSecureMultichunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ReleaseSecureMultichunkmem);
int KREE_ConfigSecureMultiChunkMemInfo(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ConfigSecureMultiChunkMemInfo);
int KREE_ION_AllocChunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_AllocChunkmem);
int KREE_ION_ZallocChunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_ZallocChunkmem);
int KREE_ION_ReferenceChunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_ReferenceChunkmem);
int KREE_ION_UnreferenceChunkmem(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_UnreferenceChunkmem);
int KREE_ION_QueryChunkmem_TEST(void) { return -ENOSYS; }
EXPORT_SYMBOL(KREE_ION_QueryChunkmem_TEST);
int TeeServiceCall_wake_lock(void) { return -ENOSYS; }
EXPORT_SYMBOL(TeeServiceCall_wake_lock);

/* Thermal base IO remap pointers */
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

/* Thermal functions */
int get_cpu_target_tj(void) { return 90000; }
EXPORT_SYMBOL(get_cpu_target_tj);
int mtktscpu_limited_dmips(void) { return 0; }
EXPORT_SYMBOL(mtktscpu_limited_dmips);
int tscpu_update_tempinfo(void) { return 0; }
EXPORT_SYMBOL(tscpu_update_tempinfo);
int mtk_idle_notifier_register(void) { return -ENOSYS; }
EXPORT_SYMBOL(mtk_idle_notifier_register);

/* SCP sensor hub stubs */
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

/* Performance/power management */
int perf_boost_cnt;
EXPORT_SYMBOL(perf_boost_cnt);
int perf_boost_lock;
EXPORT_SYMBOL(perf_boost_lock);
int set_taklking_flag(void) { return 0; }
EXPORT_SYMBOL(set_taklking_flag);
int pd_get_opp_capacity(void) { return 0; }
EXPORT_SYMBOL(pd_get_opp_capacity);

/* IOMMU / trusted mem */
int mtk_iommu_sec_init(void) { return -ENOSYS; }
EXPORT_SYMBOL(mtk_iommu_sec_init);
int tmem_type2sec_id(void) { return -ENOSYS; }
EXPORT_SYMBOL(tmem_type2sec_id);
int _map_user_pages(void) { return -ENOSYS; }
EXPORT_SYMBOL(_map_user_pages);

/* TZ system */
struct device *tz_system_dev;
EXPORT_SYMBOL(tz_system_dev);
int tz_system_driver;
EXPORT_SYMBOL(tz_system_driver);
