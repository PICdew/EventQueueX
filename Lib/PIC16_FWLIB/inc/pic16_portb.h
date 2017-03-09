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

#ifndef _PIC16_PORTB_H_
#define _PIC16_PORTB_H_

#include <stdint.h>
#include <stdbool.h>

typdef enum _portb_pin {
    PORTB_Pin_0 = 0x0U,
    PORTB_Pin_1 = 0x1U,
    PORTB_Pin_2 = 0x2U,
    PORTB_Pin_3 = 0x3U,
    PORTB_Pin_4 = 0x4U,
    PORTB_Pin_5 = 0x5U,
    PORTB_Pin_6 = 0x6U,
    PORTB_Pin_7 = 0x7U,
} portb_pin_t;

typedef enum _portb_direction {
    PORTB_Direction_Output = 0x0U,
    PORTB_Direction_Input = 0x1U,
} portb_direction_t;

typedef enum _portb_analog_sel {
    PORTB_Analog_Sel_DigitalInOut = 0x0U,
    PORTB_Analog_Sel_AnalogIn = 0x1U,
} portb_analog_sel_t;

typedef enum _portb_pull_up {
    PORTB_Pull_Up_Disable = 0x0U,
    PORTB_Pull_Up_Enable = 0x1U,
} portb_pull_up_t;

typedef enum _portb_open_drain {
    PORTB_Open_Drain_Disable = 0x0U,
    PORTB_Open_Drain_Enable = 0x1U,
} portb_open_drain_t;

typedef enum _portb_slaw_rate {
    PORTB_Slaw_Rate_Limited = 0x0U,
    PORTB_Slaw_Rate_Maximum = 0x1U,
} portb_slaw_rate_t;

typedef enum _portb_input_level {
    PORTB_Input_Level_Ttl = 0x0U,
    PORTB_Input_Level_St = 0x1U,
} portb_input_level_t;

typedef struct _portb_pin_config {
    uint8_t pinVal,
    portb_direction_t direction,
    portb_analog_sel_t analogSel,
    portb_pull_up_t pullUp,
    portb_open_drain_t openDrain,
    portb_slaw_rate_t slawRate,
    portb_input_level_t inputLevel,
} portb_pin_config_t;

void PORTB_Deinit(void);
void PORTB_Init(portb_pin_t pin, const portb_pin_config_t *config);
void PORTB_Write(uint8_t portVal);
uint8_t PORTB_Read(void);
void PORTB_WritePin(portb_pin_t pin, uint8_t pinVal);
void PORTB_SetPin(portb_pin_t pin, uint8_t pinVal);
void PORTB_ClearPin(portb_pin_t pin, uint8_t pinVal);
void PORTB_TogglePin(portb_pin_t pin, uint8_t pinVal);
uint8_t PORTB_ReadPin(portb_pin_t pin);

#endif /* _PIC16_PORTB_H_ */
