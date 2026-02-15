/*
Owner: Uri Naor
Date: Feb 7, 2024
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */

typedef struct stack
{
	size_t capacity;
	size_t element_size;
	size_t top;
	void *elements;
} stack_t;

stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *new_stack = (stack_t *)calloc(1, sizeof(stack_t)
	+ capacity * element_size);
	if(NULL == new_stack)
	{
		printf("Allocation creating a stack has failed.\n");
		
		return NULL;
	}
	
	new_stack->elements = (void *)((char *)new_stack + sizeof(stack_t));
	
	new_stack->capacity = capacity;
	new_stack->element_size = element_size;
	new_stack->top = 0;
	
	return new_stack;
}

void StackDestroy(stack_t *stack)
{
	assert(stack);
	
	free(stack);
}

void StackPush(stack_t *stack, void *element)
{
	void *target;
	
	assert(stack);	
	assert(element);	
	
	if(stack->top == stack->capacity)
	{
		printf("Can't push. Stack is full.\n");
		return;
	}
	
	target = (char *)(stack->elements) + (stack->top * stack->element_size);
	memcpy(target, element, stack->element_size);
	
	stack->top++;
}

void StackPop(stack_t *stack)
{
	assert(stack);
	
	if (0 == stack->top)
	{		
		return;
	}
	
	stack->top--;
}

void *StackPeek(const stack_t *stack)
{
	assert(stack);
	
	if(0 == stack->top)
	{		
		return NULL;		
	}
	
	return (char *)(stack->elements) + ((stack->top-1) * stack->element_size);
}

int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	
	return (0 == stack->top);
}

size_t StackCapacity(const stack_t *stack)
{
	assert(stack);
	
	return stack->capacity;
}

size_t StackSize(const stack_t *stack)
{
	assert(stack);
	
	return stack->top;
}

