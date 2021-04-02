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

#include <stdio.h>
#include "stm32746g_discovery.h"
#include "itm.h"

static void SystemClock_Config(void);
static void MPU_Config(void);

static void greetings (char const * show) {
	ITM_puts ("\n", 1);
	ITM_puts (show, 256);
	ITM_puts ("\n", 1);
	ITM_puts (" compiled ", 256);
	ITM_puts (__DATE__, 256);
	ITM_puts (" by ", 256);
#if   defined ( __CC_ARM )
	ITM_puts (" ARM CC\n", 256);
#elif defined (__GNUC__)
	ITM_puts (" GNU CC\n", 256);
#elif defined (__ICCARM__)
	ITM_puts (" IAR CC\n", 256);
#elif defined (__TI_ARM__)
	ITM_puts (" TI CC\n", 256);
#else
	ITM_puts (" unknown CC\n", 256);
#endif
	/* TODO displaying HAL, CMSIS, BSP... versions */
}

// defined in stm32f7xx_hal_msp.c
extern void HAL_DBGMCU_FREEZE_ALL (void);

int main(void) {
  
    // IRQ still enabled in debug if following is commented
	// FIXME EVEN WITH ALL THE FOLLOWING, CPY_BUF_DMA_STREAM_IRQHANDLER !!!
	HAL_DBGMCU_FREEZE_ALL();

    /* Configure the MPU attributes as Write Through */
    MPU_Config();
    /* Enable I-Cache */
    SCB_EnableICache();
    /* Enable D-Cache */
    SCB_EnableDCache();

    /* STM32F7xx HAL library initialization:
         - Configure the Flash ART accelerator on ITCM interface
         - Configure the Systick to generate an interrupt each 1 msec
         - Set NVIC Group Priority to 4
         - Low Level Initialization
       Then call HAL_MspInit
       */
    HAL_Init();

    /* Configure the System clock to have a frequency of 216 MHz */
    SystemClock_Config();

    /* Application code starts here ******************************/

#if (defined PRODUCT_NAME)
    greetings (PRODUCT_NAME);
#else
    greetings ("Hello empty world !");
#endif

    unsigned long loop_nb = 0u;
    /* Infinite loop */
    ITM_dbg_puts("entering infinite loop\n");
    while (1)
    {
    	printf ("loop[%lu]...\n", loop_nb);

    	ITM_puts ("SET\n", 4);
        BSP_LED_On(LED1);
        HAL_Delay(500);

        ITM_puts ("RESET\n", 6);
        BSP_LED_Off(LED1);
        HAL_Delay(500);

        ITM_dbg_puts("one more loop done\n");
        loop_nb ++;
        assert_param(loop_nb % 10);
    }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 432;  
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;

    assert_param (HAL_RCC_OscConfig(&RCC_OscInitStruct) == HAL_OK);

    /* activate the OverDrive to reach the 216 Mhz Frequency */
    assert_param (HAL_PWREx_EnableOverDrive() == HAL_OK);
    
    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
       clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
    assert_param (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) == HAL_OK);
}

/**
  * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
  * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
  *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
    MPU_Region_InitTypeDef MPU_InitStruct;
    
    /* Disable the MPU */
    HAL_MPU_Disable();

    /* Configure the MPU attributes as WT for SRAM */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress = 0x20010000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* Enable the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

