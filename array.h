/*Copyright (c) 2014, Kyle Blake
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Neither the name of Kyle Blake nor the names of other
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Modified by Brandon Blake */

#ifndef ARRAY_H

#include "types.h"

#define DEFINE_ARRAY(type, name) \
	typedef struct name ## _array { \
		type *data; \
		usize size; \
		usize cap; \
	} name ## _array

#define DEFINE_SLICE(type, name) \
	typedef struct name ## _slice { \
		type *data; \
		usize size; \
	} name ## _slice

DEFINE_ARRAY(u8, u8);

void array_grow_(struct u8_array *array, usize size);
void array_trim_(struct u8_array *array, usize size);
void *array_bump_(struct u8_array *array, usize size);

#define array_grow(array) array_grow_((struct u8_array *) (array), sizeof((array)->data[0]))
#define array_trim(array) array_trim_((struct u8_array *) (array), sizeof((array)->data[0]))
#define array_bump(array) array_bump_((struct u8_array *) (array), sizeof((array)->data[0]))

#define array_push(array, elem) ({ \
		typeof(array) _array = (array); \
		*((typeof(_array->data))array_bump(_array)) = elem; \
	})

#define array_pop(array) ({ \
		typeof(array) _array = (array); \
		_array->data[_array->size-- - 1]; \
	})

void array_free(void *array);

#define foreach(var, array) \
	for (usize var ## _index = 0; var ## _index != (usize)-1; var ## _index = (usize)-1) \
		for (typeof((array).data) var; \
		     var ## _index < (array).size && (var = &(array).data[var ## _index], true); \
		     var ## _index++)

#define ARRAY_H
#endif
