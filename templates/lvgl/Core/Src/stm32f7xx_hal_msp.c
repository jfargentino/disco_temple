/*
 *   Copyright 2021 ENEGENO
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

/**
  * @file    stm32f7xx_hal_msp.c
  * @author  JFA
  * @brief   HAL MSP module.
  */ 

#include "stm32746g_discovery.h"
#include "tft.h"
#include "touchpad.h"
#include "lvgl.h"


/* Use ITM trace for LVGL logger */
#if !defined(LV_LOG_PRINTF) || (LV_LOG_PRINTF <= 0)
static void lv_log_printer (lv_log_level_t level,
							const char * file_path,
							uint32_t line_nb,
							const char * function_name,
							const char * description) {
	ITM_puts("[LV ", 4);
	switch (level) {
		case LV_LOG_LEVEL_TRACE:
		ITM_puts("DBG", 3);
		break;
		case LV_LOG_LEVEL_INFO:
	    ITM_puts("INF", 3);
		break;
		case LV_LOG_LEVEL_WARN:
	    ITM_puts("WRN", 3);
		break;
		case LV_LOG_LEVEL_ERROR:
		ITM_puts("ERR", 3);
		break;
		case LV_LOG_LEVEL_USER:
		ITM_puts("USR", 3);
		break;
		default:
		ITM_puts("???", 3);
		break;
	}
	ITM_puts("][", 2);
	ITM_puts(file_path, 256);
	ITM_puts(":", 1);
	ITM_puts(function_name, 256);
	// TODO line nb
	ITM_puts("]", 1);
	ITM_puts(description, 256);
	ITM_puts("\n", 1);
}
#endif /* !defined(LV_LOG_PRINTF) || (LV_LOG_PRINTF <= 0) */

void HAL_DBGMCU_FREEZE_ALL (void) {
	__HAL_DBGMCU_FREEZE_TIM2();
	__HAL_DBGMCU_FREEZE_TIM3();
	__HAL_DBGMCU_FREEZE_TIM4();
	__HAL_DBGMCU_FREEZE_TIM5();
	__HAL_DBGMCU_FREEZE_TIM6();
	__HAL_DBGMCU_FREEZE_TIM7();
	__HAL_DBGMCU_FREEZE_TIM12();
	__HAL_DBGMCU_FREEZE_TIM13();
	__HAL_DBGMCU_FREEZE_TIM14();
	__HAL_DBGMCU_FREEZE_LPTIM1();
	__HAL_DBGMCU_FREEZE_RTC();
	__HAL_DBGMCU_FREEZE_WWDG();
	__HAL_DBGMCU_FREEZE_IWDG();
	__HAL_DBGMCU_FREEZE_I2C1_TIMEOUT();
	__HAL_DBGMCU_FREEZE_I2C2_TIMEOUT();
	__HAL_DBGMCU_FREEZE_I2C3_TIMEOUT();
	//__HAL_DBGMCU_FREEZE_I2C4_TIMEOUT();
	__HAL_DBGMCU_FREEZE_CAN1();
	__HAL_DBGMCU_FREEZE_CAN2();
	__HAL_DBGMCU_FREEZE_TIM1();
	__HAL_DBGMCU_FREEZE_TIM8();
	__HAL_DBGMCU_FREEZE_TIM9();
	__HAL_DBGMCU_FREEZE_TIM10();
	__HAL_DBGMCU_FREEZE_TIM11();
}

/**
  * @brief  Initializes the Global MSP.
  * @retval None
  */
void HAL_MspInit(void)
{
    ITM_Init();
    // Using LED1 as defined in stm32746g_discovery.h
    BSP_LED_Init(LED1);
    lv_init();
    tft_init();
    touchpad_init();

#if !defined(LV_LOG_PRINTF) || (LV_LOG_PRINTF <= 0)
    // Connect LVGL logger to ITM trace
    lv_log_register_print_cb(lv_log_printer);
#endif

    ITM_dbg_puts ("HAL_MspInit done");
}

/**
  * @brief  DeInitializes the Global MSP.  
  * @retval None
  */
void HAL_MspDeInit(void)
{
	ITM_dbg_puts ("entering HAL_MspDeInit");
	BSP_LED_DeInit(LED1);
	lv_deinit();
	ITM_DeInit ();
}

/**
  * @brief  Initializes the PPP MSP.
  * @retval None
  */
void HAL_PPP_MspInit(void)
{
 
}

/**
  * @brief  DeInitializes the PPP MSP.  
  * @retval None
  */
void HAL_PPP_MspDeInit(void)
{

}

/**
  * @brief  SYSTICK callback.
  *         This function must overwrite the weak one from stm32f7xx_hal_cortex.c
  * @retval None
  */
void HAL_SYSTICK_Callback(void)
{
	/* Increment LVGL internal counter with the nb of ms since last call */
	lv_tick_inc(1);
}
