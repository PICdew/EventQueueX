/*
 * Copyright (C) 2016 Wang Ge
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdint.h>
#include <xc.h>
#include "eqx_port.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
 static volatile uint8_t criticalSectionNestCounter = 0;
 static volatile uint8_t globalInterruptEnableBackup = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/
void PORT_EnterCriticalSection(void)
{
    if (0 == criticalSectionNestCounter)
    {
        /* Save origional interrupt enable bit. */
        globalInterruptEnableBackup = INTCONbits.GIE;

        /* Disable Interrupt. */
        INTCONbits.GIE = 0;
    }

    /* Increase use count. */
    criticalSectionNestCounter++;
}

void PORT_ExitCriticalSection(void)
{
    /* Decrease use count. */
    criticalSectionNestCounter--;

    if (0 == criticalSectionNestCounter)
    {
        /* Load origional interrupt enable bit. */
        INTCONbits.GIE = globalInterruptEnableBackup;
    }
}

/******************************************************************************
 * EOF
 *****************************************************************************/
