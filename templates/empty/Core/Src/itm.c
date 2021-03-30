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

#include "itm.h"
#include "stm32f7xx_hal.h"

void ITM_Init(void) {
	uint32_t const ITM_UNLOCK_VAL = 0xC5ACCE55;
	ITM->LAR = ITM_UNLOCK_VAL;
	// FIXME looks like some 1st chars are missing
	// ITM_SendChar(0u); does not suffice
}

void ITM_DeInit(void) {
	// TODO
	ITM->LAR = 0;
}


int ITM_puts(char const * ptr, int max_len)
{
	char const * x = ptr;
	while ((*x) && (x - ptr < max_len)) {
		ITM_SendChar((uint32_t)(*x));
		x ++;
	}
	return x - ptr;
}

#ifdef PRINTF_USE_ITM

/* Connects ITM SWO to printf output */
int __io_putchar(int ch) {
	// ITM_SendChar declared as "__STATIC_INLINE" in CMSIS core_cm7.h
    ITM_SendChar((unsigned)ch);
    return ch;
}

#endif
