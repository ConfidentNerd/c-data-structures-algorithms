/*
Owner: Uri Naor
Date: Feb 19, 2024
*/

#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */

#include "cbuff.h" /* freespace */

#define READ_IDX (buffer->read % buffer->capacity)
#define WRITE_IDX ((buffer->size + buffer->read) % buffer->capacity)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

enum STATUS
{
	FAIL = (-1),
	SUCCESS
};

struct cbuff
{
	size_t read;
	size_t size;
	size_t capacity;
	char byte[1];
};

cbuff_t *CBuffCreate(size_t capacity)
{
	cbuff_t *new_buff = malloc(offsetof(cbuff_t, byte) + capacity);
	if (NULL == new_buff)
	{
		return NULL;
	}
	
	new_buff->capacity = capacity;
	new_buff->size = 0;
	new_buff->read = 0;
	
	return (new_buff);
}

void CBuffDestroy(cbuff_t *buffer)
{
	assert(buffer);

	free(buffer);
}

ssize_t CBuffRead(cbuff_t *buffer, void *dest, size_t count)
{
	size_t first_pass_count = buffer->capacity - READ_IDX;
	size_t to_read = 0;
	size_t available_to_read = CBuffSize(buffer);
	
	assert(buffer);
	assert(dest);
	
	if (CBuffIsEmpty(buffer))
	{
		return FAIL;
	}
	
	count = MIN(count, available_to_read);
	to_read = count;

	first_pass_count = MIN(first_pass_count, count);

	memcpy(dest, buffer->byte + READ_IDX, first_pass_count);
		
	to_read -= first_pass_count;
		
	memcpy((char*)dest + first_pass_count, 
	buffer->byte, to_read);
	
	buffer->size -= count;
	buffer->read = (buffer->read + count) % buffer->capacity; 
	
	return count;
}

ssize_t CBuffWrite(cbuff_t *buffer, const void *src, size_t count)
{
	size_t first_pass_count = buffer->capacity - WRITE_IDX;
	size_t to_write = count;
	size_t free_space = CBuffFreeSpace(buffer);
	
	assert(buffer);
	assert(src);
	
	if (0 == free_space)
	{
		return FAIL;
	}
	
	count = MIN(count, free_space);
	to_write = count;
	
	first_pass_count = MIN(first_pass_count, count);
		
	memcpy(buffer->byte + WRITE_IDX, src, first_pass_count);
		
	to_write -= first_pass_count;
		
	memcpy(buffer->byte, ((char *)src) + first_pass_count, to_write);
	
	buffer->size += count;
	
	return count;
}

int CBuffIsEmpty(const cbuff_t *buffer)
{
	assert(buffer);
	
	return (0 == buffer->size);
}

size_t CBuffSize(const cbuff_t *buffer)
{
	assert(buffer);

	return (buffer->size);
}

size_t CBuffFreeSpace(const cbuff_t *buffer)
{
	assert(buffer);

	return (buffer->capacity - buffer->size);
}
