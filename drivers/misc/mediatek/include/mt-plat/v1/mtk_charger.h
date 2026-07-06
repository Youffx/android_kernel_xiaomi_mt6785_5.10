/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2021 MediaTek Inc.
 */
#ifndef __MTK_CHARGER_H__
#define __MTK_CHARGER_H__

#include <linux/types.h>
#include <linux/device.h>
#include <linux/notifier.h>
#include <linux/list.h>

/* charger_manager notify charger_consumer */
enum {
	CHARGER_NOTIFY_EOC,
	CHARGER_NOTIFY_START_CHARGING,
	CHARGER_NOTIFY_STOP_CHARGING,
	CHARGER_NOTIFY_ERROR,
	CHARGER_NOTIFY_NORMAL,
};

enum {
	MAIN_CHARGER = 0,
	SLAVE_CHARGER = 1,
	TOTAL_CHARGER = 2,
	DIRECT_CHARGER = 10,
	MAIN_DIVIDER_CHARGER = 20,
	SLAVE_DIVIDER_CHARGER = 21,
};

struct charger_consumer {
	struct device *dev;
	void *cm;
	struct notifier_block *pnb;
	struct list_head list;
	bool hv_charging_disabled;
};

extern struct charger_consumer *charger_manager_get_by_name(
	struct device *dev, const char *supply_name);
extern int charger_manager_get_charger_temperature(
	struct charger_consumer *consumer, int idx,
	int *tchg_min, int *tchg_max);
extern int charger_manager_get_input_current_limit(
	struct charger_consumer *consumer, int idx, int *input_current_uA);
extern int charger_manager_set_input_current_limit(
	struct charger_consumer *consumer, int idx, int input_current_uA);
extern int charger_manager_set_charging_current_limit(
	struct charger_consumer *consumer, int idx, int charging_current_uA);
extern int charger_manager_get_current_charging_type(
	struct charger_consumer *consumer);
extern int register_charger_manager_notifier(
	struct charger_consumer *consumer, struct notifier_block *nb);
extern int unregister_charger_manager_notifier(
	struct charger_consumer *consumer, struct notifier_block *nb);
extern int charger_manager_enable_charging(
	struct charger_consumer *consumer, int idx, bool en);
extern bool is_power_path_supported(void);
extern int charger_get_vbus(void);
extern bool mt_charger_plugin(void);

#endif /* __MTK_CHARGER_H__ */
