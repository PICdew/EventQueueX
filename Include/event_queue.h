/*
 * Copyright (C) 2016 Wang Ge
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __EVENT_QUEUE_H__
#define __EVENT_QUEUE_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct _event
{
    uint8_t signal;
    uint8_t parameter;
} event_t;

typedef struct _event_queue
{
    event_t *buffer;
    event_t *head;
    event_t *tail;
    uint8_t  size;
    bool     full;
} event_queue_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void EvtQueue_Init(event_queue_t *evtQueueHandle, event_t *buffer, uint8_t size);
bool EvtQueue_Push(event_queue_t *evtQueueHandle, event_t *event);
bool EvtQueue_Pull(event_queue_t *evtQueueHandle, event_t *event);
bool EvtQueue_IsFull(event_queue_t *evtQueueHandle);
bool EvtQueue_IsEmpty(event_queue_t *evtQueueHandle);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/******************************************************************************
 * EOF
 *****************************************************************************/

#endif /* __EVENT_QUEUE_H__ */
