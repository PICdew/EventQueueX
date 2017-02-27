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
#include "eqx_port.h"
#include "eqx.h"
#include "event_queue.h"
#include "eqx_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if (EQX_MAX_TASKS < 1U) || (8U < EQX_MAX_TASKS)
    #error "EQX_MAX_TASKS not defined or out of range. Valid range is 1..8"
#endif
#define NULL (0U)

typedef struct _task_handle
{
    EQX_Task task;
    uint8_t priorityMask;
    event_queue_t evtQueueHandle;
} task_handle_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
extern void EQX_Start(void);
#if defined(EQX_USE_GO_TO_SLEEP) &&(1U == EQX_USE_GO_TO_SLEEP)
    void EQX_GoToSleep(void);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
static task_handle_t taskHandle[EQX_MAX_TASKS];
static uint8_t EQX_readySet = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void EQX_Init(void)
{
    uint8_t index;
    uint8_t state;

    ENTER_CRITICAL_SECTION(state);
    for (index = 0U; index < EQX_MAX_TASKS; index++)
    {
        taskHandle[index].task = NULL;
        taskHandle[index].priorityMask = 0U;
        EvtQueue_Deinit(&taskHandle[index].evtQueueHandle);
    }
    EXIT_CRITICAL_SECTION(state);
}

bool EQX_CreateTask(EQX_Task task, uint8_t prio, event_t *buffer,
                    uint8_t size, uint8_t signal, uint8_t parameter)
{
    bool result = false;
    uint8_t state;

    ENTER_CRITICAL_SECTION(state);
    if (NULL == taskHandle[prio].task)
    {
        taskHandle[prio].task = task;
        taskHandle[prio].priorityMask = 1U << prio;
        EvtQueue_Init(&taskHandle[prio].evtQueueHandle, buffer, size);
        result = EQX_PostEvent(prio, signal, parameter);
    }
    EXIT_CRITICAL_SECTION(state);

    return result;
}

bool EQX_DeleteTask(uint8_t prio)
{
    bool result = false;
    uint8_t state;

    ENTER_CRITICAL_SECTION(state);
    if (NULL != taskHandle[prio].task)
    {
        taskHandle[prio].task = NULL;
        EvtQueue_Deinit(&taskHandle[prio].evtQueueHandle);

        result = true;
    }
    EXIT_CRITICAL_SECTION(state);

    return result;
}

void EQX_Run(void)
{
    static uint8_t const log2Lkup[] = {
        0U, 1U, 2U, 2U, 3U, 3U, 3U, 3U, 4U, 4U, 4U, 4U, 4U, 4U, 4U, 4U,
        5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U, 5U,
        6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
        6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U, 6U,
        7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
        7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
        7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
        7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U, 7U,
        8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U,
        8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U,
        8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U,
        8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U,
        8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U,
        8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U,
        8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U,
        8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U, 8U,
    };
    event_t event;
    uint8_t prio;
    uint8_t state;

    EQX_Start();

    ENTER_CRITICAL_SECTION(state);
    for (;;)
    {
        if (0U != (prio = log2Lkup[EQX_readySet]))
        {
            prio -= 1U;

            for (;;)
            {
                if (EvtQueue_IsEmpty(&taskHandle[prio].evtQueueHandle))
                {
                    EQX_readySet &= ~taskHandle[prio].priorityMask;
                    break;
                }
                else
                {
                    if (EvtQueue_Pull(&taskHandle[prio].evtQueueHandle, &event) &&
                        (NULL != taskHandle[prio].task))
                    {
                        EXIT_CRITICAL_SECTION(state);

                        /* Run the task. */
                        (*taskHandle[prio].task)(event);

                        ENTER_CRITICAL_SECTION(state);
                    }
                }
            }
        }
        else
        {
            EXIT_CRITICAL_SECTION(state);
            #if defined(EQX_USE_GO_TO_SLEEP) &&(1U == EQX_USE_GO_TO_SLEEP)
                EQX_GoToSleep();
            #endif
            ENTER_CRITICAL_SECTION(state);
        }
    }
}

bool EQX_PostEvent(uint8_t prio, uint8_t signal, uint8_t parameter)
{
    bool result = false;
    event_t event;
    uint8_t state;

    ENTER_CRITICAL_SECTION(state);
    if (NULL != taskHandle[prio].task)
    {    
        if (EvtQueue_IsEmpty(&taskHandle[prio].evtQueueHandle))
        {
            EQX_readySet |= taskHandle[prio].priorityMask;
        }
        event.signal = signal;
        event.parameter = parameter;
        result = EvtQueue_Push(&taskHandle[prio].evtQueueHandle, &event);
    }
    EXIT_CRITICAL_SECTION(state);

    return result;
}

/******************************************************************************
 * EOF
 *****************************************************************************/
