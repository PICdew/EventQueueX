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

#ifndef _PIC16_PORTA_H_
#define _PIC16_PORTA_H_

#include <stdint.h>

typedef enum _porta_pin {
    PORTA_Pin_0 = 0x0U,
    PORTA_Pin_1 = 0x1U,
    PORTA_Pin_2 = 0x2U,
    PORTA_Pin_3 = 0x3U,
    PORTA_Pin_4 = 0x4U,
    PORTA_Pin_5 = 0x5U,
    PORTA_Pin_6 = 0x6U,
    PORTA_Pin_7 = 0x7U,
} porta_pin_t;

typedef enum _porta_direction {
    PORTA_Direction_Output = 0x0U,
    PORTA_Direction_Input = 0x1U,
} porta_direction_t;

typedef enum _porta_analog_sel {
    PORTA_Analog_Sel_DigitalInOut = 0x0U,
    PORTA_Analog_Sel_AnalogIn = 0x1U,
} porta_analog_sel_t;

typedef enum _porta_pull_up {
    PORTA_Pull_Up_Disable = 0x0U,
    PORTA_Pull_Up_Enable = 0x1U,
} porta_pull_up_t;

typedef enum _porta_open_drain {
    PORTA_Open_Drain_Disable = 0x0U,
    PORTA_Open_Drain_Enable = 0x1U,
} porta_open_drain_t;

typedef enum _porta_slaw_rate {
    PORTA_Slaw_Rate_Limited = 0x0U,
    PORTA_Slaw_Rate_Maximum = 0x1U,
} porta_slaw_rate_t;

typedef enum _porta_input_level {
    PORTA_Input_Level_Ttl = 0x0U,
    PORTA_Input_Level_St = 0x1U,
} porta_input_level_t;

typedef struct _porta_pin_config {
    uint8_t pinVal;
    porta_direction_t direction;
    porta_analog_sel_t analogSel;
    porta_pull_up_t pullUp;
    porta_open_drain_t openDrain;
    porta_slaw_rate_t slawRate;
    porta_input_level_t inputLevel;
} porta_pin_config_t;

void PORTA_Deinit(void);
void PORTA_Init(porta_pin_t pin, const porta_pin_config_t *config);
void PORTA_Write(uint8_t portVal);
uint8_t PORTA_Read(void);
void PORTA_WritePin(porta_pin_t pin, uint8_t pinVal);
void PORTA_SetPin(porta_pin_t pin);
void PORTA_ClearPin(porta_pin_t pin);
void PORTA_TogglePin(porta_pin_t pin);
uint8_t PORTA_ReadPin(porta_pin_t pin);

#endif /* _PIC16_PORTA_H_ */
