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
#include "pic16_portb.h"

void PORTB_Deinit(void)
{
    /* Set pins back to analog input. */
    ANSELB = 0xFFU;

    /* Set pins direction to input. */
    TRISB = 0xFFU;

    /* Set Output Latch to Low. */
    LATB = 0x0U;

    /* Set all electrical properties to default value. */
    WPUB = 0xFFU;
    ODCONB = 0x0U;
    SLRCONB = 0xFFU;
    INLVLB = 0x0U;
}

void PORTB_Init(portb_pin_t pin, const portb_pin_config_t *config)
{
    /* Set initial pin Latch value. */
    LATB = (LATB & (~(1U << pin))) | ((config->pinVal != 0U) ? (1U << pin) : 0U);

    /* Set all electrical properties. */
    SLRCONB = (SLRCONB & (~(1U << pin))) | ((config->slawRate != 0U) ? (1U << pin) : 0U);
    INLVLB = (INLVLB & (~(1U << pin))) | ((config->inputLevel != 0U) ? (1U << pin) : 0U);
    WPUB = (WPUB & (~(1U << pin))) | ((config->pullUp != 0U) ? (1U << pin) : 0U);
    ODCONB = (ODCONB & (~(1U << pin))) | ((config->openDrain != 0U) ? (1U << pin) : 0U);

    /* Set Analog/Digital input selection. */
    ANSELB = (ANSELB & (~(1U << pin))) | ((config->analogSel != 0U) ? (1U << pin) : 0U);
    /* Set Digital I/O direction. */
    TRISB = (TRISB & (~(1U << pin))) | ((config->analogSel != 0U) ? (1U << pin) : 0U);
}

void PORTB_Write(uint8_t portVal)
{
    LATB = portVal;
}

uint8_t PORTB_Read(void)
{
    return PORTB;
}

void PORTB_WritePin(portb_pin_t pin, uint8_t pinVal)
{
    LATB = (LATB & (~(1U << pin))) | ((pinVal != 0U) ? (1U << pin) : 0U);
}

void PORTB_SetPin(portb_pin_t pin)
{
    LATB |= 1U << pin;
}

void PORTB_ClearPin(portb_pin_t pin)
{
    LATB &= ~(1U << pin);
}

void PORTB_TogglePin(portb_pin_t pin)
{
    LATB ^= 1U << pin;
}

uint8_t PORTB_ReadPin(portb_pin_t pin)
{
    return (PORTB & (1U << pin)) >> pin;
}
