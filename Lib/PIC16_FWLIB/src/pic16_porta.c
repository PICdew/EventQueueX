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
#include "pic16_porta.h"

void PORTA_Deinit(void)
{
    /* Set pins back to analog input. */
    ANSELA = 0xFFU;

    /* Set pins direction to input. */
    TRISA = 0xFFU;

    /* Set Output Latch to Low. */
    LATA = 0x0U;

    /* Set all electrical properties to default value. */
    WPUA = 0xFFU;
    ODCONA = 0x0U;
    SLRCONA = 0xFFU;
    INLVLA = 0x0U;
}

void PORTA_Init(porta_pin_t pin, const porta_pin_config_t *config)
{
    /* Set initial pin Latch value. */
    LATA = (LATA & (~(1U << pin))) | ((config->pinVal != 0U) ? (1U << pin) : 0U);

    /* Set all electrical properties. */
    SLRCONA = (SLRCONA & (~(1U << pin))) | ((config->slawRate != 0U) ? (1U << pin) : 0U);
    INLVLA = (INLVLA & (~(1U << pin))) | ((config->inputLevel != 0U) ? (1U << pin) : 0U);
    WPUA = (WPUA & (~(1U << pin))) | ((config->pullUp != 0U) ? (1U << pin) : 0U);
    ODCONA = (ODCONA & (~(1U << pin))) | ((config->openDrain != 0U) ? (1U << pin) : 0U);

    /* Set Analog/Digital input selection. */
    ANSELA = (ANSELA & (~(1U << pin))) | ((config->analogSel != 0U) ? (1U << pin) : 0U);
    /* Set Digital I/O direction. */
    TRISA = (TRISA & (~(1U << pin))) | ((config->analogSel != 0U) ? (1U << pin) : 0U);
}

void PORTA_Write(uint8_t portVal)
{
    LATA = portVal;
}

uint8_t PORTA_Read(void)
{
    return PORTA;
}

void PORTA_WritePin(porta_pin_t pin, uint8_t pinVal)
{
    LATA = (LATA & (~(1U << pin))) | ((pinVal != 0U) ? (1U << pin) : 0U);
}

void PORTA_SetPin(porta_pin_t pin)
{
    LATA |= 1U << pin;
}

void PORTA_ClearPin(porta_pin_t pin)
{
    LATA &= ~(1U << pin);
}

void PORTA_TogglePin(porta_pin_t pin)
{
    LATA ^= 1U << pin;
}

uint8_t PORTA_ReadPin(porta_pin_t pin)
{
    return (PORTA & (1U << pin)) >> pin;
}
