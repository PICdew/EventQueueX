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

#ifndef _PIC16_ITC_H_
#define _PIC16_ITC_H_

#include <stdbool.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum _IRQn_Type {
    IOC_IRQn           = 0U,
    INT_IRQn           = 1U,
    TMR0_IRQn          = 2U,
    TMR1_IRQn          = 3U,
    TMR2_IRQn          = 4U,
    CCP1_IRQn          = 5U,
    MSSP1_IRQn         = 6U,
    EUSART_TX_IRQn     = 7U,
    EUSART_RX_IRQn     = 8U,
    ADC_IRQn           = 9U,
    TMR1_GATE_IRQn     = 10U,
    CCP2_IRQn          = 11U,
    TMR4_IRQn          = 12U,
    TMR6_IRQn          = 13U,
    MSSP1_BUS_COL_IRQn = 14U,
    Reserved0_IRQn     = 15U,
    CMP1_IRQn          = 16U,
    CMP2_IRQn          = 17U,
    OSC_FAIL_IRQn      = 18U,
    CLC1_IRQn          = 19U,
    CLC2_IRQn          = 20U,
    CLC3_IRQn          = 21U,
    CLC4_IRQn          = 22U,
    ZCD_IRQn           = 23U,
    CWG_IRQn           = 24U,
    Reserved1_IRQn     = 25U,
    Reserved2_IRQn     = 26U,
    SMT1_IRQn          = 27U,
    SMT1_ACQ_IRQn      = 28U,
    SMT1_PW_ACQ_IRQn   = 29U,
    SMT2_IRQn          = 30U,
    SMT2_ACQ_IRQn      = 31U,
    SMT2_PW_ACQ_IRQn   = 32U,
    CRC_IRQn           = 33U,
    SCAN_IRQn          = 34U,
    PID_IRQn           = 35U,
    PID_ERR_IRQn       = 36U,
    AT_IRQn            = 37U,
    Reserved3_IRQn     = 38U,
    TMR5_IRQn          = 39U,
    TMR5_GATE_IRQn     = 40U,
    TMR3_IRQn          = 41U,
    TMR3_GATE_IRQn     = 42U,
} IRQn_Type;

/*******************************************************************************
 * API
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void ITC_EnableGlobalIrq(void);
void ITC_DisableGlobalIrq(void);
void ITC_EnablePeripheralIrq(void);
void ITC_DisablePeripheralIrq(void);
void ITC_EnableIrq(IRQn_Type irqNum);
void ITC_DisableIrq(IRQn_Type irqNum);
bool ITC_GetPendingIrq(IRQn_Type irqNum);
void ITC_SetPendingIrq(IRQn_Type irqNum);
void ITC_ClearPendingIrq(IRQn_Type irqNum);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PIC16_ITC_H_ */
