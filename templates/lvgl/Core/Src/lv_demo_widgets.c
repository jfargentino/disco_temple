/**
 * @file lv_demo_widgets.c
 *
 */
#include "lv_demo_widgets.h"

static void main_create(lv_obj_t * parent);
static void charts_create(lv_obj_t * parent);

static lv_obj_t * tv;
static lv_obj_t * t_main;
static lv_obj_t * t_charts;
static lv_style_t style_box;

void lv_demo_widgets(void)
{
    tv = lv_tabview_create(lv_scr_act(), NULL);
    t_main = lv_tabview_add_tab(tv, "General");
    t_charts = lv_tabview_add_tab(tv, "Charts");

    main_create(t_main);
    charts_create(t_charts);
}

static void main_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);

    lv_coord_t grid_w_meter = lv_page_get_width_grid(parent, 3, 1);
    lv_coord_t meter_h = lv_page_get_height_grid(t_charts, 2, 1);
    lv_coord_t meter_size = LV_MATH_MIN(grid_w_meter, meter_h);

    /* Voltmeter as a linear meter */
    lv_obj_t * volt_meter = lv_linemeter_create(parent, NULL);
    lv_obj_set_drag_parent(volt_meter, true);
    lv_linemeter_set_value(volt_meter, 1200);
    lv_obj_set_size(volt_meter, meter_size, meter_size);
    lv_obj_add_style(volt_meter, LV_LINEMETER_PART_MAIN, &style_box);
    lv_obj_set_style_local_value_str(volt_meter,
    		                         LV_LINEMETER_PART_MAIN,
									 LV_STATE_DEFAULT,
									 "Voltage (mV)");
    lv_obj_t * label = lv_label_create(volt_meter, NULL);
    lv_obj_align(label, volt_meter, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_local_text_font(label,
    		                         LV_LABEL_PART_MAIN,
									 LV_STATE_DEFAULT,
									 lv_theme_get_font_title());

    /* TODO
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, volt_meter);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)linemeter_anim);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_time(&a, 4000);
    lv_anim_set_playback_time(&a, 1000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
*/
    /* Currentmeter as a gauge */
    lv_obj_t * current_gauge = lv_gauge_create(parent, NULL);
    lv_obj_set_drag_parent(current_gauge, true);
    lv_obj_set_size(current_gauge, meter_size, meter_size);
    lv_obj_add_style(current_gauge, LV_GAUGE_PART_MAIN, &style_box);
    lv_obj_set_style_local_value_str(current_gauge,
    		                         LV_GAUGE_PART_MAIN,
									 LV_STATE_DEFAULT,
									 "Current (mA)");
    label = lv_label_create(current_gauge, label);
    lv_obj_align(label,
    		     current_gauge,
				 LV_ALIGN_IN_BOTTOM_MID,
				 0, grid_w_meter / 3);

    /* TODO
    lv_anim_set_var(&a, current_gauge);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)gauge_anim);
    lv_anim_start(&a);
 */
    /* Time as a horizontal bar */
    /*Create a bar and use the backgrounds value style property to display the current value*/
    lv_obj_t * time_bar_h = lv_cont_create(parent, NULL);
    lv_cont_set_fit2(time_bar_h, LV_FIT_NONE, LV_FIT_TIGHT);
    lv_obj_add_style(time_bar_h, LV_CONT_PART_MAIN, &style_box);
    lv_obj_set_style_local_value_str(time_bar_h,
    		                         LV_CONT_PART_MAIN,
									 LV_STATE_DEFAULT,
									 "Charge duration (s)");
    lv_obj_set_width(time_bar_h, grid_w_meter);

    lv_obj_t * bar = lv_bar_create(time_bar_h, NULL);
    lv_obj_set_width(bar, lv_obj_get_width_fit(time_bar_h));
    lv_obj_set_style_local_value_font(bar,
    		                          LV_BAR_PART_BG,
									  LV_STATE_DEFAULT,
									  lv_theme_get_font_small());
    lv_obj_set_style_local_value_align(bar,
    		                           LV_BAR_PART_BG,
									   LV_STATE_DEFAULT,
									   LV_ALIGN_OUT_BOTTOM_MID);
    lv_obj_set_style_local_value_ofs_y(bar,
    		                           LV_BAR_PART_BG,
									   LV_STATE_DEFAULT,
									   LV_DPI / 20);
    lv_obj_set_style_local_margin_bottom(bar,
    		                             LV_BAR_PART_BG,
										 LV_STATE_DEFAULT,
										 LV_DPI / 7);
    lv_obj_align(bar, NULL, LV_ALIGN_CENTER, 0, 0);

    /* TODO */
    //lv_task_create(bar_anim, 100, LV_TASK_PRIO_LOW, bar);
}

#define CHART_LENGTH 1024

static void charts_create(lv_obj_t * parent)
{
    lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);

    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);

    lv_coord_t grid_h_chart = lv_page_get_height_grid(parent, 1, 1);
    lv_coord_t grid_w_chart = lv_page_get_width_grid(parent, disp_size <= LV_DISP_SIZE_LARGE ? 1 : 2, 1);

    lv_obj_t * chart = lv_chart_create(parent, NULL);
    lv_obj_add_style(chart, LV_CHART_PART_BG, &style_box);
    if(disp_size <= LV_DISP_SIZE_SMALL) {
        lv_obj_set_style_local_text_font(chart,
        		                         LV_CHART_PART_SERIES_BG,
										 LV_STATE_DEFAULT,
										 lv_theme_get_font_small());
    }
    lv_obj_set_drag_parent(chart, true);
    lv_obj_set_style_local_value_str(chart, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, "Line chart");
    lv_obj_set_width_margin(chart, grid_w_chart);
    lv_obj_set_height_margin(chart, grid_h_chart);
    lv_chart_set_div_line_count(chart, 3, 0);
    lv_chart_set_point_count(chart, CHART_LENGTH);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    if(disp_size > LV_DISP_SIZE_SMALL) {
        lv_obj_set_style_local_pad_left(chart,  LV_CHART_PART_BG, LV_STATE_DEFAULT, 4 * (LV_DPI / 10));
        lv_obj_set_style_local_pad_bottom(chart,  LV_CHART_PART_BG, LV_STATE_DEFAULT, 3 * (LV_DPI / 10));
        lv_obj_set_style_local_pad_right(chart,  LV_CHART_PART_BG, LV_STATE_DEFAULT, 2 * (LV_DPI / 10));
        lv_obj_set_style_local_pad_top(chart,  LV_CHART_PART_BG, LV_STATE_DEFAULT, 2 * (LV_DPI / 10));
        /*
        lv_chart_set_y_tick_length(chart, 0, 0);
        lv_chart_set_x_tick_length(chart, 0, 0);
        lv_chart_set_y_tick_texts(chart, "600\n500\n400\n300\n200", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        lv_chart_set_x_tick_texts(chart, "Jan\nFeb\nMar\nApr\nMay\nJun\nJul\nAug", 0, LV_CHART_AXIS_DRAW_LAST_TICK);
        */
    }
    lv_chart_series_t * s1 = lv_chart_add_series(chart, LV_THEME_DEFAULT_COLOR_PRIMARY);
    lv_chart_series_t * s2 = lv_chart_add_series(chart, LV_THEME_DEFAULT_COLOR_SECONDARY);

    /* load the voltage historic */
    lv_chart_set_next(chart, s1, 10);
    lv_chart_set_next(chart, s1, 90);
    lv_chart_set_next(chart, s1, 30);
    lv_chart_set_next(chart, s1, 60);
    lv_chart_set_next(chart, s1, 10);
    lv_chart_set_next(chart, s1, 90);
    lv_chart_set_next(chart, s1, 30);
    lv_chart_set_next(chart, s1, 60);
    lv_chart_set_next(chart, s1, 10);
    lv_chart_set_next(chart, s1, 90);

    /* load current historic */
    lv_chart_set_next(chart, s2, 32);
    lv_chart_set_next(chart, s2, 66);
    lv_chart_set_next(chart, s2, 5);
    lv_chart_set_next(chart, s2, 47);
    lv_chart_set_next(chart, s2, 32);
    lv_chart_set_next(chart, s2, 32);
    lv_chart_set_next(chart, s2, 66);
    lv_chart_set_next(chart, s2, 5);
    lv_chart_set_next(chart, s2, 47);
    lv_chart_set_next(chart, s2, 66);
    lv_chart_set_next(chart, s2, 5);
    lv_chart_set_next(chart, s2, 47);
}

/*
static void linemeter_anim(lv_obj_t * linemeter, lv_anim_value_t value)
{
    lv_linemeter_set_value(linemeter, value);

    static char buf[64];
    lv_snprintf(buf, sizeof(buf), "%d", value);
    lv_obj_t * label = lv_obj_get_child(linemeter, NULL);
    lv_label_set_text(label, buf);
    lv_obj_align(label, linemeter, LV_ALIGN_CENTER, 0, 0);
}

static void gauge_anim(lv_obj_t * gauge, lv_anim_value_t value)
{
    lv_gauge_set_value(gauge, 0, value);

    static char buf[64];
    lv_snprintf(buf, sizeof(buf), "%d", value);
    lv_obj_t * label = lv_obj_get_child(gauge, NULL);
    lv_label_set_text(label, buf);
    lv_obj_align(label, gauge, LV_ALIGN_IN_TOP_MID, 0, lv_obj_get_y(label));
}
*/
