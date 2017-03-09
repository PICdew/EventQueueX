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
#include "pic16_portc.h"

void PORTC_Deinit(void)
{
    /* Set pins back to analog input. */
    ANSELC = 0xFFU;

    /* Set pins direction to input. */
    TRISC = 0xFFU;

    /* Set Output Latch to Low. */
    LATC = 0x0U;

    /* Set all electrical properties to default value. */
    WPUC = 0xFFU;
    ODCONC = 0x0U;
    SLRCONC = 0xFFU;
    INLVLC = 0x0U;
    HIDRVC = 0x0U;
}

void PORTC_Init(portc_pin_t pin, const portc_pin_config_t *config)
{
    /* Set initial pin Latch value. */
    LATC = (LATC & (~(1U << pin))) | ((config->pinVal != 0U) ? (1U << pin) : 0U);

    /* Set all electrical properties. */
    SLRCONC = (SLRCONC & (~(1U << pin))) | ((config->slawRate != 0U) ? (1U << pin) : 0U);
    INLVLC = (INLVLC & (~(1U << pin))) | ((config->inputLevel != 0U) ? (1U << pin) : 0U);
    WPUC = (WPUC & (~(1U << pin))) | ((config->pullUp != 0U) ? (1U << pin) : 0U);
    ODCONC = (ODCONC & (~(1U << pin))) | ((config->openDrain != 0U) ? (1U << pin) : 0U);
    HIDRVC = (HIDRVC & (~(1U << pin))) | ((config->highDrive != 0U) ? (1U << pin) : 0U);

    /* Set Analog/Digital input selection. */
    ANSELC = (ANSELC & (~(1U << pin))) | ((config->analogSel != 0U) ? (1U << pin) : 0U);
    /* Set Digital I/O direction. */
    TRISC = (TRISC & (~(1U << pin))) | ((config->analogSel != 0U) ? (1U << pin) : 0U);
}

void PORTC_Write(uint8_t portVal)
{
    LATC = portVal;
}

uint8_t PORTC_Read(void)
{
    return PORTC;
}

void PORTC_WritePin(portc_pin_t pin, uint8_t pinVal)
{
    LATC = (LATC & (~(1U << pin))) | ((pinVal != 0U) ? (1U << pin) : 0U);
}

void PORTC_SetPin(portc_pin_t pin)
{
    LATC |= 1U << pin;
}

void PORTC_ClearPin(portc_pin_t pin)
{
    LATC &= ~(1U << pin);
}

void PORTC_TogglePin(portc_pin_t pin)
{
    LATC ^= 1U << pin;
}

uint8_t PORTC_ReadPin(portc_pin_t pin)
{
    return (PORTC & (1U << pin)) >> pin;
}
