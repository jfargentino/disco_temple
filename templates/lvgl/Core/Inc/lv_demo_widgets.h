/**
 * @file lv_demo_widgets.h
 *
 */

#ifndef LV_DEMO_WIDGETS_H
#define LV_DEMO_WIDGETS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#if LV_VERSION_CHECK(7, 7, 1) == 0
#error "lv_examples: Wrong lvgl version"
#endif

void lv_demo_widgets(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_WIDGETS_H*/
