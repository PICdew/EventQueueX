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
#include "pic16_clk.h"

static uint32_t CLK_GetSystemClkFreq(void);
static uint32_t CLK_GetPrimaryOscFreq(void);
static uint32_t CLK_GetIntOscFreq(void);

static uint32_t externalOscFreq = 0U;

static uint32_t CLK_GetSystemClkFreq(void)
{
    uint32_t frequency;

    /* System Clock from INTOSC. */
    if (OSCCON & 0x03U)
    {
        frequency = CLK_GetIntOscFreq();
    }
    /* System Clock from Main Clock. */
    else
    {
        frequency = CLK_GetPrimaryOscFreq();

        /* 4x PLL is enabled. */
        if (OSCCON & 0x80U)
        {
            frequency = frequency << 2U;
        }
    }

    return frequency;
}

static uint32_t CLK_GetPrimaryOscFreq(void)
{
    uint32_t frequency;

    /* Primary OSC from INTOSC. */
    if (!externalOscFreq)
    {
        frequency = CLK_GetIntOscFreq();
    }
    else
    {
        frequency = externalOscFreq;
    }

    return 0U;
}

static uint32_t CLK_GetIntOscFreq(void)
{
    uint32_t frequency;

    switch ((OSCCON & 0x78U) >> 3U)
    {
    case CLK_IntOscFreq_Lf_31000Hz:
        frequency = 31000U;
        break;

    case CLK_IntOscFreq_Mf_31250Hz:
    case CLK_IntOscFreq_Hf_31250Hz:
        frequency = 31250U;
        break;

    case CLK_IntOscFreq_Mf_62500Hz:
        frequency = 62500U;
        break;

    case CLK_IntOscFreq_Mf_125000Hz:
    case CLK_IntOscFreq_Hf_125000Hz:
        frequency = 125000U;
        break;

    case CLK_IntOscFreq_Mf_250000Hz:
    case CLK_IntOscFreq_Hf_250000Hz:
        frequency = 250000U;
        break;

    case CLK_IntOscFreq_Mf_500000Hz:
    case CLK_IntOscFreq_Hf_500000Hz:
        frequency = 500000U;
        break;

    case CLK_IntOscFreq_Hf_1000000Hz:
        frequency = 1000000U;
        break;

    case CLK_IntOscFreq_Hf_2000000Hz:
        frequency = 2000000U;
        break;

    case CLK_IntOscFreq_Hf_4000000Hz:
        frequency = 4000000U;
        break;

    case CLK_IntOscFreq_Hf_8000000Hz:
        frequency = 8000000U;
        break;

    case CLK_IntOscFreq_Hf_16000000Hz:
        frequency = 16000000U;
        break;

    default:
        frequency = 0U;
    }

    return frequency;
}

void CLK_SetSysClkSrc(clk_sys_clk_src_t source)
{
    uint8_t i;

    OSCCON = (OSCCON & (~0x03U)) | source;

    /* Add Delay to target clock source stable. */
    for (i = 0U; i < 20U; i++)
    {
        asm(“NOP”);
    }
}

void CLK_EnablePll(void)
{
    /* Enable 4x PLL. */
    OSCCON |= 0x80U;

    /* Wait until PLL Stable. */
    while (!(CLK_STATUS_PllReady & CLK_GetStatus()))
    {
    }
}

void CLK_DisablePll(void)
{
    /* Disable 4x PLL. */
    OSCCON &= ~0x80U;

    /* Wait until PLL is disabled. */
    while (CLK_STATUS_PllReady & CLK_GetStatus())
    {
    }
}

void CLK_SetIntOscFreq(clk_int_osc_freq_t frequency)
{
    OSCCON = (OSCCON & (~0x78U)) | (frequency << 3U);

    if (CLK_IntOscFreq_Lf_31000Hz == frequency)
    {
        while (!(CLK_STATUS_LfIntOscReady & CLK_GetStatus()))
        {
        }
    }
    else if ((frequency <= CLK_IntOscFreq_Mf_500000Hz) && (frequency != CLK_IntOscFreq_Hf_31250Hz))
    {
        while (!(CLK_STATUS_MfIntOscReady & CLK_GetStatus()))
        {
        }
    }
    else
    {
        while ((!((CLK_STATUS_HfIntOscStable)&CLK_GetStatus())) ||
               (!((CLK_STATUS_HfIntOscLocked)&CLK_GetStatus())) ||
               (!((CLK_STATUS_HfIntOscReady)&CLK_GetStatus())))
        {
        }
    }
}

void CLK_setExtOscFreq(uint32_t frequency)
{
    externalOscFreq = frequency;
}

uint8_t CLK_GetStatusFlag(void)
{
    return OSCSTAT;
}

uint32_t CLK_GetFreq(clk_name_t name)
{
    uint32_t frequency;

    switch (name)
    {
    case CLK_NAME_SystemClk:
        frequency = CLK_GetSystemClkFreq();
        break;

    case CLK_NAME_PrimaryOscClk:
        frequency = CLK_GetPrimaryOscFreq();
        break;

    case CLK_NAME_HfIntOscClk:
        frequency = 16000000U;
        break;

    case CLK_NAME_MfIntOscClk:
        frequency = 500000U;
        break;

    case CLK_NAME_LfIntOscClk:
        frequency = 31000U;
        break;

    case CLK_NAME_FrcClk:
        frequency = 600000U;
        break;

    case CLK_NAME_ExtOscClk:
        frequency = externalOscFreq;
        break;

    default:
        frequency = 0U;
        break;
    }

    return frequency;
}

void CLK_SetIntOscTurningVal(uint8_t turning)
{
    assert(turning <= 0x3FU);

    OSCTUNE = turning;
}
