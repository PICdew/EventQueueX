/*
 *  Copyright 2016 Wang Ge
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
 */

#ifndef __VTIMER_H__
#define __VTIMER_H__

#include <stdint.h>
#include <stdbool.h>
#include "eqx.h"

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void VTIMER_Init(void);
void VTIMER_SetTimer(uint8_t name, uint16_t msec, void *callback);
void VTIMER_KillTimer(uint8_t name);
bool VTIMER_TimerElapsed(uint8_t name);
void VTIMER_Task(event_t event);
void VTIMER_UpdateHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VTIMER_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/
