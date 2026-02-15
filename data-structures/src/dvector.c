/*
Owner: Uri Naor
Date: Feb 13, 2024
*/

#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* calloc */
#include <string.h> /* memcpy */

#include "dvector.h"

#define GROWTH_REQUIRED_PERCENT 0.75
#define SHRINK_REQUIRED_PERCENT 0.25
#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 0.5
#define SUCCESS 0
#define FAIL -1

struct dvector
{
	size_t capacity;
	size_t element_size;
	size_t size;
	void *elements;
};

/******************** FUNCTIONS ********************/
dvector_t *DVectorCreate(size_t capacity , size_t element_size)
{
	dvector_t *new_vector = (dvector_t *)malloc(sizeof(dvector_t));
	if(NULL == new_vector)
	{
		printf("Allocation creating a vector has failed.\n");
		return NULL;
	}
	
	new_vector->elements = malloc(capacity * element_size);
	if(NULL == new_vector->elements)
	{
		free(new_vector);
		printf("Allocation for elements has failed.\n");
		
		return NULL; 
	}
	
	new_vector->capacity = capacity;
	new_vector->element_size = element_size;
	new_vector->size = 0;
	
	return new_vector;
}

void DvectorDestroy(dvector_t *dvector)
{
	assert(dvector);
	
	free(dvector->elements);
	free(dvector);
}

int DvectorReserve(dvector_t *dvector, size_t capacity)
{
	/* add temp address holder */
	void *temp_address_holder = NULL;
	
	assert(dvector);
	assert(capacity);
	
	if (capacity < dvector->size)
	{
		printf("Capacity smaller than size, "
		"changing capacity to current size.\n");
		capacity = dvector->size;
	}
	
	temp_address_holder = realloc(dvector->elements, 
	capacity * dvector->element_size);
	if(NULL == temp_address_holder)
	{
		printf("Reallocation during reserve has failed.\n");
		
		return FAIL;
	}
	
	dvector->elements = temp_address_holder;
	
	dvector->capacity = capacity;
	
	return SUCCESS;
}

int DvectorPushBack(dvector_t *dvector, const void *data)
{
	void *target;
	
	assert(dvector);	
	assert(data);	
	
	target = (char *)(dvector->elements) + 
	(dvector->size * dvector->element_size);
	memcpy(target, data, dvector->element_size);
	
	++dvector->size;
	
	if(dvector->size >= (size_t)(dvector->capacity * GROWTH_REQUIRED_PERCENT))
	{
		return DvectorReserve(dvector, (size_t)(dvector->capacity * GROWTH_FACTOR));
	}
	
	return SUCCESS;
}

size_t DvectorCapacity(const dvector_t *dvector)
{
	assert(dvector);
	
	return dvector->capacity;
}

size_t DvectorSize(const dvector_t *dvector)
{
	assert(dvector);
	
	return dvector->size;
}

void DvectorPopBack(dvector_t *dvector)
{
	assert(dvector);
	
	if (0 == dvector->size)
	{
		printf("Can't pop, vector is already empty.\n");
		
		return;
	}
	
	--dvector->size;
	
	if(dvector->size <= (size_t)(dvector->capacity * SHRINK_REQUIRED_PERCENT))
	{
		DvectorReserve(dvector, (size_t)(dvector->capacity * SHRINK_FACTOR));
	}
}

void *DvectorGetAccessToElement(const dvector_t *dvector, size_t idx)
{
	assert(dvector);
	assert(idx < dvector->size);
	
	return ((char *)(dvector->elements) + (idx * dvector->element_size));
}

int DvectorShrink(dvector_t *dvector)
{
	size_t shrink_capacity = 0;
	
	assert(dvector);
	
	if ((size_t)(dvector->capacity * SHRINK_REQUIRED_PERCENT) < dvector->size ||
	    (size_t)(dvector->capacity * SHRINK_FACTOR) == 0)
	{
		printf("Can't shrink, "
		"size is bigger than 25%% of the capacity,"
		" or capacity at minimum already.\n");
		return FAIL;
	}
	
	shrink_capacity = (size_t)(dvector->capacity * SHRINK_FACTOR);
	
	return DvectorReserve(dvector, shrink_capacity);
}
