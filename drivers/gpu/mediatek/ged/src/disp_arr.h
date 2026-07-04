#ifndef _DISP_ARR_H_
#define _DISP_ARR_H_

int primary_display_get_cur_refresh_rate(void);
int primary_display_get_max_refresh_rate(void);
int primary_display_get_min_refresh_rate(void);
int primary_display_set_refresh_rate(unsigned int refresh_rate);

#endif
