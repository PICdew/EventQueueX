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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "eqx.h"
#include "vtimer.h"
#include "eqx_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if (EQX_MAX_VTIMER < 1U) || (128U < EQX_MAX_VTIMER)
#error "EQX_MAX_VTIMER not defined or out of range. Valid range is 1..256"
#endif
#define NULL (0U)
#define VTIMER_TIMEOUT_EVENT_OFFSET (0x80U)

typedef struct _vtimer_handle
{
    uint16_t currentTicks;
    uint16_t desiredTicks;
    VTIMER_Callback callback;
    bool isWorking;
} vtimer_handle_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
static volatile vtimer_handle_t handle[EQX_MAX_VTIMER] = {0U};

/******************************************************************************
 * Code
 *****************************************************************************/
void VTIMER_Init(void)
{
    uint8_t i;

    for (i = 0U; i < EQX_MAX_VTIMER; i++)
    {
        handle[i].currentTicks = 0U;
        handle[i].desiredTicks = 0U;
        handle[i].callback = NULL;
        handle[i].isWorking = false;
    }
}

void VTIMER_SetTimer(uint8_t name, uint16_t tick, VTIMER_Callback callback)
{
    assert(name < EQX_MAX_VTIMER);
    assert(!handle[name].isWorking);
    assert(tick > 0U);
    assert(callback != NULL);

    handle[name].currentTicks = 0U;
    handle[name].desiredTicks = tick;
    handle[name].callback = callback;
}

void VTIMER_StartTimer(uint8_t name)
{
    uint8_t stat;

    assert(name < EQX_MAX_VTIMER);

    ENTER_CRITICAL_SECTION(stat);
    handle[name].isWorking = true;
    EXIT_CRITICAL_SECTION(stat);
}

void VTIMER_StopTimer(uint8_t name)
{
    uint8_t stat;

    assert(name < EQX_MAX_VTIMER);

    ENTER_CRITICAL_SECTION(stat);
    handle[name].isWorking = false;
    EXIT_CRITICAL_SECTION(stat);
}

uint16_t VTIMER_GetTime(uint8_t name)
{
    uint8_t stat;
    uint16_t time;

    assert(name < EQX_MAX_VTIMER);

    ENTER_CRITICAL_SECTION(stat);
    time = handle[name].currentTicks;
    EXIT_CRITICAL_SECTION(stat);

    return time;
}

void VTIMER_Task(event_t event)
{
    if (event.signal >= VTIMER_TIMEOUT_EVENT_OFFSET)
    {
        handle[event.signal - VTIMER_TIMEOUT_EVENT_OFFSET].callback();
    }
}

void VTIMER_Update(void)
{
    uint8_t i;

    for (i = 0U; i < EQX_MAX_VTIMER; i++)
    {
        if (handle[i].isWorking)
        {
            handle[i].currentTicks++;
            if (handle[i].currentTicks == handle[i].desiredTicks)
            {
                /* Auto Reload Timer Counter. */
                handle[i].currentTicks = 0U;

                /* Inform Timer Task to invoke callback function. */
#if (EQX_PARAM_SIZE > 0U)
                EQX_PostEvent(EQX_TIMER_TASK_PRIO, i + VTIMER_TIMEOUT_EVENT_OFFSET, 0U);
#else
                EQX_PostEvent(EQX_TIMER_TASK_PRIO, i + VTIMER_TIMEOUT_EVENT_OFFSET);
#endif
            }
        }
    }
}

/******************************************************************************
 * EOF
 *****************************************************************************/
