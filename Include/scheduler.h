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

#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include "event_queue.h"

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Framework related APIs */
void EQX_Init(void);
void EQX_Run(void);

#if (1 == EQX_USE_GO_TO_SLEEP)
    void EQX_GoToSleep(void);
#endif

/* Task Control APIs */
bool EQX_CreateTask(void (*TaskName)(uint8_t signal, uint8_t parameter),
                    uint8_t prio, event_t *buffer, uint8_t size);
bool EQX_DeleteTask(uint8_t prio);

/* Event handle APIs */
bool EQX_PostEvent(uint8_t prio, uint8_t signal, uint8_t parameter);
//void EQX_PostEvent(uint8_t prio, uint8_t signal);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/******************************************************************************
 * EOF
 *****************************************************************************/

#endif /* _SCHEDULER_H_ */
