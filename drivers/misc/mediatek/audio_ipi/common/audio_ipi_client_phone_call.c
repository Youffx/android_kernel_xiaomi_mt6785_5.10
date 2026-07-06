// SPDX-License-Identifier: GPL-2.0
//
// Copyright (c) 2016 MediaTek Inc.

#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>

#include "audio_ipi_client_phone_call.h"
#include "audio_task_manager.h"

void phone_call_recv_message(struct ipi_msg_t *p_ipi_msg)
{
}

void phone_call_task_unloaded(void)
{
}

void audio_ipi_client_phone_call_init(void)
{
	audio_task_register_callback(
		TASK_SCENE_PHONE_CALL,
		phone_call_recv_message,
		phone_call_task_unloaded);
}

void audio_ipi_client_phone_call_deinit(void)
{
}
