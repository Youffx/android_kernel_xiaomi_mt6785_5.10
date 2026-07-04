/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __MTKFB_H__
#define __MTKFB_H__

#include <linux/types.h>

void mtkfb_set_backlight_level(unsigned int level);
int disp_bls_set_backlight(int level_1024);
void disp_pq_notify_backlight_changed(int bl_1024);

#endif
