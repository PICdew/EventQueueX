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
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "mcc_generated_files/mcc.h"
#include "eqx.h"
#include "vtimer.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static event_t vtimerEvtQueue[10U];

/*******************************************************************************
 * Code
 ******************************************************************************/
void TMR0_IrqHandler(void)
{
    VTIMER_Update();
}

void blinking(uint8_t name)
{
    if (0U == name)
    {
        IO_RA2_Toggle();
    }
    else if (1U == name)
    {
        IO_RA5_Toggle();
    }
    else
    {
    }
}

void EQX_Start(void)
{
    TMR0_Initialize();
    TMR0_SetInterruptHandler(TMR0_IrqHandler);

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
}

void EQX_GoToSleep(void)
{
}

void main(void)
{
    SYSTEM_Initialize();

//    ADC_Initialize();
//    ADC_SelectChannel(channel_AN4);
//    ADC_StartConversion();
//    EUSART_Initialize();

    VTIMER_Init();
    VTIMER_SetTimer(0U, 1U, blinking);
    VTIMER_SetTimer(1U, 2U, blinking);
    VTIMER_StartTimer(0U);
    VTIMER_StartTimer(1U);

    EQX_Init();
    EQX_CreateTask(VTIMER_Task, EQX_TIMER_TASK_PRIO, vtimerEvtQueue,
                   sizeof(vtimerEvtQueue)/sizeof(vtimerEvtQueue[0]),
                   0U, 0U);

    /* Give flow control to scheduler. */
    EQX_Run();
}

/******************************************************************************
 * EOF
 *****************************************************************************/
