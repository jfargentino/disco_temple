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
/*
 * stm32_assert.h
 *
 * Included by HAL, so keep this name
 *
 *  Created on: 26 mars 2021
 *      Author: jfa
 */

#ifndef INC_STM32_ASSERT_H_
#define INC_STM32_ASSERT_H_

#ifdef  USE_FULL_ASSERT

#include <stdint.h>

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the stringified expression, the name of the source file
  *         and the source line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define assert_param(expr) ((expr) ? (void)0 \
		                           : assert_failed( # expr, __FILE__, __LINE__))

#include <cmsis_compiler.h>

static inline void __assert_failed(char const * expr,
		                           char const * file,
                                   char const * line) {
	__disable_irq();
#ifdef ASSERT_USE_ITM
	ITM_puts(file, 256);
	ITM_puts(":", 1);
	ITM_puts(line, 8);
	ITM_puts(" ASSERTION \"", 16);
	ITM_puts(expr, 256);
	ITM_puts("\" FAILED !\n", 16);
#endif
	while (1) {

	}
}

/* two preprocessing levels are needed: one to evaluate __LINE__, the other one to
 * stringify the value.
 */
#define _assert_failed(expr,file,line) __assert_failed(expr, file, # line)
#define assert_failed(expr,file,line) _assert_failed(expr, file, line)


#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#endif /* INC_STM32_ASSERT_H_ */
