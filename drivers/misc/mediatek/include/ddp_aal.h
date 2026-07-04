/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __DDP_AAL_H__
#define __DDP_AAL_H__

#include <linux/types.h>

enum disp_aal_id_t {
	DISP_AAL0 = 0,
	DISP_AAL1,
	DISP_AAL_TOTAL
};

void disp_aal_notify_backlight_changed(int bl_1024);

#endif
