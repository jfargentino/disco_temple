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
  ******************************************************************************
  * @file    itm.h
  * @brief   This file contains all the function prototypes for
  *          the itm.c file
  ******************************************************************************
  */
#ifndef __ITM_H__
#define __ITM_H__

void ITM_Init(void);

void ITM_DeInit(void);

/* @brief Send a NUL-terminated string through ITM SWO.
 * @param ptr the NUL-terminated string to sent.
 * @param max_len the maximum nb of bytes to write in case no '\0' in ptr.
 * @retval nb of bytes wrotten.
 */
int ITM_puts(char const * ptr, int max_len);

#ifdef PRINTF_USE_ITM

int __io_putchar(int ch);

#endif /* PRINTF_USE_ITM */

#endif /* __ITM_H__ */
