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

#ifndef _PIC16_CLK_H_
#define _PIC16_CLK_H_

#include <stdint.h>

typedef enum _clk_sys_clk_src {
    CLK_SysClkSrc_MainOsc = 0x0U,
    CLK_SysClkSrc_IntOsc = 0x10U,
} clk_sys_clk_src_t;

typedef enum _clk_int_osc_freq {
    CLK_IntOscFreq_Lf_31000Hz = 0x0U,
    CLK_IntOscFreq_Mf_31250Hz = 0x2U,
    CLK_IntOscFreq_Hf_31250Hz = 0x3U,
    CLK_IntOscFreq_Mf_62500Hz = 0x4U,
    CLK_IntOscFreq_Mf_125000Hz = 0x5U,
    CLK_IntOscFreq_Mf_250000Hz = 0x6U,
    CLK_IntOscFreq_Mf_500000Hz = 0x7U,
    CLK_IntOscFreq_Hf_125000Hz = 0x8U,
    CLK_IntOscFreq_Hf_250000Hz = 0x9U,
    CLK_IntOscFreq_Hf_500000Hz = 0xAU,
    CLK_IntOscFreq_Hf_1000000Hz = 0xBU,
    CLK_IntOscFreq_Hf_2000000Hz = 0xCU,
    CLK_IntOscFreq_Hf_4000000Hz = 0xDU,
    CLK_IntOscFreq_Hf_8000000Hz = 0xEU,
    CLK_IntOscFreq_Hf_16000000Hz = 0xFU,
} clk_int_osc_freq_t;

typedef enum _clk_status {
    CLK_STATUS_HfIntOscStable = 0x1U,
    CLK_STATUS_LfIntOscReady = 0x2U,
    CLK_STATUS_MfIntOscReady = 0x4U,
    CLK_STATUS_HfIntOscLocked = 0x8U,
    CLK_STATUS_HfIntOscReady = 0x10U,
    CLK_STATUS_MainOscReady = 0x20U,
    CLK_STATUS_PllReady = 0x40U,
} clk_status_t;

typedef enum _clk_name {
    CLK_NAME_SystemClk,
    CLK_NAME_PrimaryOscClk,
    CLK_NAME_HfIntOscClk,
    CLK_NAME_MfIntOscClk,
    CLK_NAME_LfIntOscClk,
    CLK_NAME_FrcClk,
    CLK_NAME_ExtOscClk,
} clk_name_t;

void CLK_SetSysClkSrc(clk_sys_clk_src_t source);
void CLK_SetIntOscFreq(clk_int_osc_freq_t frequency);
void CLK_setExtOscFreq(uint32_t frequency);
void CLK_EnablePll(void);
void CLK_DisablePll(void);
uint8_t CLK_GetStatusFlag(void);
uint32_t CLK_GetFreq(clk_name_t name);
void CLK_SetIntOscTurningVal(uint8_t turning);

#endif /* _PIC16_CLK_H_ */
