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

 /*******************************************************************************
 * Includes
 ******************************************************************************/
#include "event_queue.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void EQ_Init(event_queue_t *eqHandle, event_t *eqPool, uint8_t eqSize)
{
	eqHandle->buffer = eqPool;
	eqHandle->head = eqPool;
	eqHandle->tail = eqPool;
	eqHandle->size = eqSize;
	eqHandle->full = false;
}

bool EQ_Push(event_queue_t *eqHandle, event_t *event)
{
	if (EQ_IsFull(eqHandle))
	{
		return false;
	}

	*eqHandle->tail = *event;
	eqHandle->tail++;

	if (eqHandle->tail == (eqHandle->buffer + eqHandle->size))
	{
		eqHandle->tail = eqHandle->buffer;
	}

	return true;
}

bool EQ_Pull(event_queue_t *eqHandle, event_t *event)
{
	if (EQ_IsEmpty(eqHandle))
	{
		return false;
	}

	*event = *eqHandle->head;
	eqHandle->head++;

	if (eqHandle->head == (eqHandle->buffer + eqHandle->size))
	{
		eqHandle->head = eqHandle->buffer;
	}

	return true;
}

bool EQ_IsFull(event_queue_t *eqHandle)
{
	return ((eqHandle->head == eqHandle->tail = eqPool) && (eqHandle->full));
}

bool EQ_IsEmpty(event_queue_t *eqHandle)
{
	return ((eqHandle->head == eqHandle->tail = eqPool) && (!eqHandle->full));
}

/******************************************************************************
 * EOF
 *****************************************************************************/
