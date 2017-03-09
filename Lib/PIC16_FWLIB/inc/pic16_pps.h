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

#ifndef _PIC16_PPS_H_
#define _PIC16_PPS_H_

#include <stdint.h>

void PPS_Lock(void);
void PPS_Unlock(void);
void PPS_SetPinMux(uint8_t outputReg, uint8_t outputVal, uint8_t inputReg, uint8_t inputVal);

#endif /* _PIC16_PPS_H_ */
