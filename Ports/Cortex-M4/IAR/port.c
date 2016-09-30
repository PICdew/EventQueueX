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
#include "fsl_device_registers.h"
#include "port.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void PORT_EnterCriticalSection(void)
{
    __enable_irq();
}

void PORT_ExitCriticalSection(void)
{
    __disable_irq();
}

/******************************************************************************
 * EOF
 *****************************************************************************/
