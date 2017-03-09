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
#include "mcc_generated_files/mcc.h"
#include "eqx.h"
#include "pic16_itc.h"
#include "pic16_porta.h"
#include "pic16_portc.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static event_t blink1EvtQueue[10];
static event_t blink2EvtQueue[10];

/*******************************************************************************
 * Code
 ******************************************************************************/
void blinking1(event_t event)
{
    if (0U != event.signal)
    {
        PORTA_TogglePin(PORTA_Pin_2);
        EQX_PostEvent(1U, 1U, 0);
    }
}

void blinking2(event_t event)
{
    if (0U != event.signal)
    {
        PORTA_TogglePin(PORTA_Pin_5);
    }
}

void TMR0_IrqHandler(void)
{
    EQX_PostEvent(0, 1U, 0);
}

void EQX_Start(void)
{
    TMR0_Initialize();
    ITC_ClearPendingIrq(TMR0_IRQn);
    ITC_EnableIrq(TMR0_IRQn);
    TMR0_SetInterruptHandler(TMR0_IrqHandler);

    // Enable the Peripheral Interrupts
    ITC_EnablePeripheralIrq();
    // Enable the Global Interrupts
    ITC_EnableGlobalIrq();
}

void EQX_GoToSleep(void)
{
}

void main(void)
{
    const porta_pin_config_t portaPinConfig = {
        0U,
        PORTA_Direction_Output,
        PORTA_Analog_Sel_DigitalInOut,
        PORTA_Pull_Up_Disable,
        PORTA_Open_Drain_Disable,
        PORTA_Slaw_Rate_Limited,
        PORTA_Input_Level_Ttl,
    };
    const portc_pin_config_t portcPinConfig = {
        0U,
        PORTC_Direction_Output,
        PORTC_Analog_Sel_DigitalInOut,
        PORTC_Pull_Up_Disable,
        PORTC_Open_Drain_Disable,
        PORTC_Slaw_Rate_Limited,
        PORTC_Input_Level_Ttl,
        PORTC_High_Drive_Disable,
    };

    SYSTEM_Initialize();

    PORTA_Init(PORTA_Pin_1, &portaPinConfig);
    PORTA_Init(PORTA_Pin_2, &portaPinConfig);
    PORTA_Init(PORTA_Pin_5, &portaPinConfig);
    PORTC_Init(PORTC_Pin_5, &portcPinConfig);

    EQX_Init();
    EQX_CreateTask(blinking1, 0U, blink1EvtQueue,
                   sizeof(blink1EvtQueue)/sizeof(blink1EvtQueue[0]),
                   0U, 0U);

    EQX_CreateTask(blinking2, 1U, blink2EvtQueue,
                   sizeof(blink2EvtQueue)/sizeof(blink2EvtQueue[0]),
                   0U, 0U);

    /* Give flow control to scheduler. */
    EQX_Run();
}

/******************************************************************************
 * EOF
 *****************************************************************************/
