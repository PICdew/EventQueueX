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

#ifndef __PORT_H__
#define __PORT_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ENTER_CRITICAL_SECTION()    PORT_EnterCriticalSection()
#define EXIT_CRITICAL_SECTION()     PORT_ExitCriticalSection()

/*******************************************************************************
 * API
 ******************************************************************************/
void PORT_EnterCriticalSection(void);
void PORT_ExitCriticalSection(void);

/******************************************************************************
 * EOF
 *****************************************************************************/

#endif /* __PORT_H__ */
