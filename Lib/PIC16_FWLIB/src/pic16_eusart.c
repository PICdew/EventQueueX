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
#include <assert.h>
#include "pic16_eusart.h"

void EUSART_Init(const eusart_config_t *config, uint32_t sourceClk_Hz)
{
    uint32_t baudRateGen;

    assert(config);
    assert(sourceClk_Hz);

    /* Clean all EUSART Register to default value. */
    RC1STA = 0x0U;      /* Disable UART Module and Receiver. */
    TX1STA = 0x0U;      /* Disable UART Transmiter. */
    BAUD1CON = 0x0U;    /* Clean Baud Rate & Advanced Feature Control Register. */
    SP1BRGH = 0x0U;     /* Clean Baud Rate Generator Low Register. */
    SP1BRGL = 0x0U;     /* Clean Baud Rate Generator High Register. */

    /* Set desired baud rate. */
    baudRateGen = ((sourceClk_Hz / config->baudRate_Bps) >> 2U) - 1U;
    if (baudRateGen > 0xFFFFU)
    {
        baudRateGen = ((sourceClk_Hz / config->baudRate_Bps) >> 4U) - 1U;
    }
    else
    {
        TX1STA |= 0x04U; /* Select High Baud Rate Mode. */
    }
    BAUD1CON |= 0x08U; /* Use 16-bit Baud Rate Generator. */
    SP1BRGH = (uint8_t)((baudRateGen & 0xFF00) >> 8U);
    SP1BRGL = (uint8_t)(baudRateGen & 0xFF);

    /* Set EUSART features. */
    if (EUSART_DataBits_9 == config->dataBitsCount)
    {
        TX1STA |= 0x40U;
        RC1STA |= 0x40U;
    }

    /* Set TX Invertion. */
    if (config->invertTx)
    {
        BAUD1CON |= 0x10U;
    }

    /* Enable EUSART. */
    RC1STA |= 0x80U;
}

void EUSART_Deinit(void)
{
    RC1STA = 0x0U;      /* Disable UART Module and Receiver. */
    TX1STA = 0x0U;      /* Disable UART Transmiter. */
    BAUD1CON = 0x0U;    /* Clean Baud Rate & Advanced Feature Control Register. */
    SP1BRGH = 0x0U;     /* Clean Baud Rate Generator Low Register. */
    SP1BRGL = 0x0U;     /* Clean Baud Rate Generator High Register. */
}

void EUSART_EnableTx(bool enable)
{
    TX1STA = (enable) ? (TX1STA | 0x20U) : (TX1STA & (~0x20U));
}

void EUSART_EnableRx(bool enable)
{
    RC1STA = (enable) ? (RC1STA | 0x10U) : (RC1STA & (~0x10U));
}

uint8_t EUSART_GetStatusFlag(void)
{
    uint32_t flags;

    flags = (TX1STA & 0x02U) ? EUSART_Status_TxShiftRegEmpty : 0U;
    flags |= (RC1STA & 0x02U) ? EUSART_Status_RxOverrunErr : 0U;
    flags |= (RC1STA & 0x04U) ? EUSART_Status_RxFramingErr : 0U;
    flags |= (BAUD1CON & 0x40U) ? EUSART_Status_RxIdle : 0U;
    flags |= (BAUD1CON & 0x80U) ? EUSART_Status_AutoBaudOverflowErr : 0U;

    return flags;
}

void EUSART_SendData(uint8_t data)
{
    TX1REG = data;
}

uint8_t EUSART_ReceiveData(void)
{
    return RC1REG;
}

void EUSART_SendData9(uint16_t data)
{
    TX1STA = (data & 0x100U) ? (TX1STA | 0x01U) : (TX1STA & (~0x01U));
    TX1REG = data & 0xFF;
}

uint16_t EUSART_ReceiveData9(void)
{
    uint16_t result;

    result = (RC1STA & 0x01U) ? 0x100U : 0x0U;
    result|= RC1REG;

    return result;
}
