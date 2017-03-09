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

#ifndef _PIC16_PORTC_H_
#define _PIC16_PORTC_H_

#include <stdint.h>

typedef enum _portc_pin {
    PORTC_Pin_0 = 0x0U,
    PORTC_Pin_1 = 0x1U,
    PORTC_Pin_2 = 0x2U,
    PORTC_Pin_3 = 0x3U,
    PORTC_Pin_4 = 0x4U,
    PORTC_Pin_5 = 0x5U,
    PORTC_Pin_6 = 0x6U,
    PORTC_Pin_7 = 0x7U,
} portc_pin_t;

typedef enum _portc_direction {
    PORTC_Direction_Output = 0x0U,
    PORTC_Direction_Input = 0x1U,
} portc_direction_t;

typedef enum _portc_analog_sel {
    PORTC_Analog_Sel_DigitalInOut = 0x0U,
    PORTC_Analog_Sel_AnalogIn = 0x1U,
} portc_analog_sel_t;

typedef enum _portc_pull_up {
    PORTC_Pull_Up_Disable = 0x0U,
    PORTC_Pull_Up_Enable = 0x1U,
} portc_pull_up_t;

typedef enum _portc_open_drain {
    PORTC_Open_Drain_Disable = 0x0U,
    PORTC_Open_Drain_Enable = 0x1U,
} portc_open_drain_t;

typedef enum _portc_slaw_rate {
    PORTC_Slaw_Rate_Limited = 0x0U,
    PORTC_Slaw_Rate_Maximum = 0x1U,
} portc_slaw_rate_t;

typedef enum _portc_input_level {
    PORTC_Input_Level_Ttl = 0x0U,
    PORTC_Input_Level_St = 0x1U,
} portc_input_level_t;

typedef enum _portc_high_drive {
    PORTC_High_Drive_Disable = 0x0U,
    PORTC_High_Drive_Enable = 0x1U,
} portc_high_drive_t;

typedef struct _portc_pin_config {
    uint8_t pinVal;
    portc_direction_t direction;
    portc_analog_sel_t analogSel;
    portc_pull_up_t pullUp;
    portc_open_drain_t openDrain;
    portc_slaw_rate_t slawRate;
    portc_input_level_t inputLevel;
    portc_high_drive_t highDrive;
} portc_pin_config_t;

void PORTC_Deinit(void);
void PORTC_Init(portc_pin_t pin, const portc_pin_config_t *config);
void PORTC_Write(uint8_t portVal);
uint8_t PORTC_Read(void);
void PORTC_WritePin(portc_pin_t pin, uint8_t pinVal);
void PORTC_SetPin(portc_pin_t pin);
void PORTC_ClearPin(portc_pin_t pin);
void PORTC_TogglePin(portc_pin_t pin);
uint8_t PORTC_ReadPin(portc_pin_t pin);

#endif /* _PIC16_PORTC_H_ */
