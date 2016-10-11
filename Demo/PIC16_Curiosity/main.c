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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <xc.h>
#include <stdint.h>
#include "scheduler.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static event_t blinkEvtQueue[10];

/*******************************************************************************
 * Code
 ******************************************************************************/
void blinking(uint8_t signal, uint8_t parameter)
{
}

void main(void)
{
	EQX_Init();
	EQX_CreateTask(blinking, 0, blinkEvtQueue, sizeof(blinkEvtQueue)/sizeof(blinkEvtQueue[0]));
    EQX_CreateTask(blinking, 1, blinkEvtQueue, sizeof(blinkEvtQueue)/sizeof(blinkEvtQueue[0]));
    EQX_PostEvent(0, 0, 0);
    EQX_DeleteTask(1);

	/* Give flow control to scheduler. */
	EQX_Run();
}

/******************************************************************************
 * EOF
 *****************************************************************************/
