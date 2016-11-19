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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "event_queue.h"
#include "eqx_port.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void EvtQueue_Init(event_queue_t *evtQueueHandle, event_t *buffer, uint8_t size)
{
    evtQueueHandle->buffer = buffer;
    evtQueueHandle->head = buffer;
    evtQueueHandle->tail = buffer;
    evtQueueHandle->size = size;
    evtQueueHandle->full = false;
}

void EvtQueue_Deinit(event_queue_t *evtQueueHandle)
{
    evtQueueHandle->buffer = NULL;
    evtQueueHandle->head = NULL;
    evtQueueHandle->tail = NULL;
    evtQueueHandle->size = 0;
    evtQueueHandle->full = false;
}

bool EvtQueue_Push(event_queue_t *evtQueueHandle, event_t *event)
{
    bool result = false;

    ENTER_CRITICAL_SECTION();
    if (!EvtQueue_IsFull(evtQueueHandle))
    {
        *evtQueueHandle->tail = *event;
        evtQueueHandle->tail++;
        if (evtQueueHandle->tail == (evtQueueHandle->buffer + evtQueueHandle->size))
        {
            evtQueueHandle->tail = evtQueueHandle->buffer;
        }

        result = true;
    }
    EXIT_CRITICAL_SECTION();

    return result;
}

bool EvtQueue_Pull(event_queue_t *evtQueueHandle, event_t *event)
{
    bool result = false;

    ENTER_CRITICAL_SECTION();
    if (!EvtQueue_IsEmpty(evtQueueHandle))
    {
        *event = *evtQueueHandle->head;
        evtQueueHandle->head++;

        if (evtQueueHandle->head == (evtQueueHandle->buffer + evtQueueHandle->size))
        {
            evtQueueHandle->head = evtQueueHandle->buffer;
        }

        result = true;
    }
    EXIT_CRITICAL_SECTION();

    return result;
}

bool EvtQueue_IsFull(event_queue_t *evtQueueHandle)
{
    bool result;

    ENTER_CRITICAL_SECTION();
    result = ((evtQueueHandle->head == evtQueueHandle->tail) && (evtQueueHandle->full));
    EXIT_CRITICAL_SECTION();

    return result;
}

bool EvtQueue_IsEmpty(event_queue_t *evtQueueHandle)
{
    bool result;

    ENTER_CRITICAL_SECTION();
    result = ((evtQueueHandle->head == evtQueueHandle->tail) && (!evtQueueHandle->full));
    EXIT_CRITICAL_SECTION();

    return result;
}

/******************************************************************************
 * EOF
 *****************************************************************************/
