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

#ifndef _PIC16_EUSART_H_
#define _PIC16_EUSART_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum _eusart_status {
    EUSART_Status_TxShiftRegEmpty = 0x1U,
    EUSART_Status_RxOverrunErr = 0x2U,
    EUSART_Status_RxFramingErr = 0x4U,
    EUSART_Status_RxIdle = 0x8U,
    EUSART_Status_AutoBaudOverflowErr = 0x10U,
} eusart_status_t;

typedef enum _eusart_data_bits {
    EUSART_DataBits_8 = 0x0U,
    EUSART_DataBits_9 = 0x1U,
} eusart_data_bits_t;

typedef struct _eusart_config
{
    uint32_t baudRate_Bps;
    eusart_data_bits_t dataBitsCount;
    bool invertTx;
} eusart_config_t;

void EUSART_Init(const eusart_config_t *config, uint32_t sourceClk_Hz);
void EUSART_Deinit(void);
void EUSART_EnableTx(bool enable);
void EUSART_EnableRx(bool enable);
uint8_t EUSART_GetStatusFlag(void);
void EUSART_ClearStatusFlag(uint8_t flag);
void EUSART_SendData(uint8_t data);
uint8_t EUSART_ReceiveData(void);
void EUSART_SendData9(uint16_t data);
uint16_t EUSART_ReceiveData9(void);

#endif /* _PIC16_EUSART_H_ */
