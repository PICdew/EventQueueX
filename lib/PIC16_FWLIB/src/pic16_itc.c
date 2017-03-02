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

#include <xc.h>
#include <stdint.h>
#include "pic16_itc.h"

void ITC_EnableGlobalIrq(void)
{
    INTCONbits.GIE = 1U;
}

void ITC_DisableGlobalIrq(void)
{
    INTCONbits.GIE = 0U;
}

void ITC_EnablePeripheralIrq(void)
{
    INTCONbits.PEIE = 1U;
}

void ITC_DisablePeripheralIrq(void)
{
    INTCONbits.PEIE = 0U;
}

void ITC_EnableIrq(IRQn_Type irqNum)
{
    volatile uint8_t *PIE = &PIE1;

    if (irqNum <= TMR0_IRQn)
    {
        INTCON |= 1U << (irqNum + 3U);
    }
    else
    {
        PIE[(irqNum - TMR1_IRQn) / 8U] |= 1U << ((irqNum - TMR1_IRQn) % 8U);
    }
}

void ITC_DisableIrq(IRQn_Type irqNum)
{
    volatile uint8_t *PIE = &PIE1;

    if (irqNum <= TMR0_IRQn)
    {
        INTCON &= ~(1U << (irqNum + 3U));
    }
    else
    {
        PIE[(irqNum - TMR1_IRQn) / 8U] &= ~(1U << ((irqNum - TMR1_IRQn) % 8U));
    }
}

bool ITC_GetPendingIrq(IRQn_Type irqNum)
{
    volatile uint8_t *PIR = &PIR1;
    bool result = false;

    if (irqNum <= TMR0_IRQn)
    {
        result = (INTCON & (1U << irqNum)) ? true : false;
    }
    else
    {
        result = (PIR[(irqNum - TMR1_IRQn) / 8U] & (1U << ((irqNum - TMR1_IRQn) % 8U))) ? true : false;
    }

    return result;
}

void ITC_SetPendingIrq(IRQn_Type irqNum)
{
    volatile uint8_t *PIR = &PIR1;

    if (irqNum <= TMR0_IRQn)
    {
        INTCON |= 1U << irqNum;
    }
    else
    {
        PIR[(irqNum - TMR1_IRQn) / 8U] |= 1U << ((irqNum - TMR1_IRQn) % 8U);
    }
}

void ITC_ClearPendingIrq(IRQn_Type irqNum)
{
    volatile uint8_t *PIR = &PIR1;

    if (irqNum <= TMR0_IRQn)
    {
        INTCON &= ~(1U << irqNum);
    }
    else
    {
        PIR[(irqNum - TMR1_IRQn) / 8U] &= ~(1U << ((irqNum - TMR1_IRQn) % 8U));
    }
}
