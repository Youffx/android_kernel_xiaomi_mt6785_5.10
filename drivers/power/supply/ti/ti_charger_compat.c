/* Youffx: stub implementations for MTK charger manager API removed in 5.10 */
#include <linux/module.h>
#include <linux/export.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/power/mtk_intf_mi.h>

struct charger_consumer *charger_manager_get_by_name(struct device *dev,
	const char *name)
{
	return NULL;
}
EXPORT_SYMBOL_GPL(charger_manager_get_by_name);

int charger_manager_enable_power_path(struct charger_consumer *consumer,
	int idx, bool en)
{
	return 0;
}
EXPORT_SYMBOL_GPL(charger_manager_enable_power_path);

int charger_manager_get_ibus(int *ibus)
{
	*ibus = 0;
	return 0;
}
EXPORT_SYMBOL_GPL(charger_manager_get_ibus);

int charger_manager_set_current_limit(int data, int type)
{
	return 0;
}
EXPORT_SYMBOL_GPL(charger_manager_set_current_limit);

int charger_manager_set_prop_system_temp_level(int level)
{
	return 0;
}
EXPORT_SYMBOL_GPL(charger_manager_set_prop_system_temp_level);

int adapter_get_cap_bq(struct pps_cap_bq *cap)
{
	return 0;
}
EXPORT_SYMBOL_GPL(adapter_get_cap_bq);

int adapter_get_pps_cap_bq(struct pps_cap_bq *cap)
{
	return 0;
}
EXPORT_SYMBOL_GPL(adapter_get_pps_cap_bq);

int adapter_set_cap_bq(int mV, int mA)
{
	return 0;
}
EXPORT_SYMBOL_GPL(adapter_set_cap_bq);

int adapter_set_cap_start_bq(int mV, int mA)
{
	return 0;
}
EXPORT_SYMBOL_GPL(adapter_set_cap_start_bq);

int adapter_set_cap_end_bq(int mV, int mA)
{
	return 0;
}
EXPORT_SYMBOL_GPL(adapter_set_cap_end_bq);

int adapter_is_support_pd_pps(void)
{
	return 0;
}
EXPORT_SYMBOL_GPL(adapter_is_support_pd_pps);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI Charger Compatibility Stubs");
MODULE_AUTHOR("Xiaomi");


