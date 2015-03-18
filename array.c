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

#include <stdlib.h>

#include "array.h"

void array_grow_(struct u8_array *array, usize size) {
	if (array->cap == 0) {
		array->cap = 64;
		array->data = malloc(array->cap * size);
	} else {
		// XXX This causes the buffer to crawl forward in memory. This
		// should be a big deal, but I can't get it to actually cause
		// problems, nor to do any better with smaller factors.
		array->cap = array->cap * 2;
		array->data = realloc(array->data, array->cap * size);
	}
}

void array_trim_(struct u8_array *array, usize size) {
	if (array->cap) {
		array->cap = array->size;
		array->data = realloc(array->data, array->cap * size);
	}
}

void *array_bump_(struct u8_array *array, usize size) {
	if (array->size == array->cap) {
		array_grow_(array, size);
	}
	array->size++;
	return &array->data[(array->size - 1) * size];
}

void array_free(void *array) {
	struct u8_array *array2 = array;
	free(array2->data);
}
