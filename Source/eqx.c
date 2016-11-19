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
#define NULL (0U)

typedef struct _task_handle
{
    EQX_Task task;
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

/*******************************************************************************
 * Code
 ******************************************************************************/
void EQX_Init(void)
{
    uint8_t index;

    ENTER_CRITICAL_SECTION();
    for (index = 0; index < EQX_MAX_TASKS; index++)
    {
        taskHandle[index].task = NULL;
        EvtQueue_Deinit(&taskHandle[index].evtQueueHandle);
    }
    EXIT_CRITICAL_SECTION();
}

bool EQX_CreateTask(EQX_Task task, uint8_t prio, event_t *buffer,
                    uint8_t size, uint8_t signal, uint8_t parameter)
{
    bool result = false;

    if (NULL == taskHandle[prio].task)
    {
        ENTER_CRITICAL_SECTION();
        taskHandle[prio].task = task;
        EvtQueue_Init(&taskHandle[prio].evtQueueHandle, buffer, size);
        result = EQX_PostEvent(prio, signal, parameter);
        EXIT_CRITICAL_SECTION();
    }

    return result;
}

bool EQX_DeleteTask(uint8_t prio)
{
    bool result = false;

    if (NULL != taskHandle[prio].task)
    {
        ENTER_CRITICAL_SECTION();
        taskHandle[prio].task = NULL;
        EvtQueue_Deinit(&taskHandle[prio].evtQueueHandle);
        EXIT_CRITICAL_SECTION();

        result = true;
    }

    return result;
}

void EQX_Run(void)
{
    uint8_t index;
    event_t event;

    EQX_Start();

    for (;;)
    {
        for (index = 0; index < EQX_MAX_TASKS; index++)
        {
            if (EvtQueue_Pull(&taskHandle[index].evtQueueHandle, &event))
            {
                /* Run the task. */
                (*taskHandle[index].task)(event);
            }
        }
    }
}

bool EQX_PostEvent(uint8_t prio, uint8_t signal, uint8_t parameter)
{
    bool result = false;
    event_t event;

    if (NULL != taskHandle[prio].task)
    {
        event.signal = signal;
        event.parameter = parameter;
        result = EvtQueue_Push(&taskHandle[prio].evtQueueHandle, &event);
    }

    return result;
}

/******************************************************************************
 * EOF
 *****************************************************************************/
