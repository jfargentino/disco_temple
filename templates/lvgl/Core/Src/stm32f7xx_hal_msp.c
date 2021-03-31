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
	lv_tick_inc(1);
}
