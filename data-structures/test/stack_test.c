/*
Owner: Uri Naor
Date: Feb 7, 2024
*/

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

#include <stdio.h> /* printf */
#include "stack.h"

/******************** TESTS ********************/

int main()
{
	int a = 45;
	float b = 7.2;
	
	stack_t *stack = StackCreate(20, 4);
	
	printf("Created stack of capacity 20, that holds 4 byte elements.\n");
	printf("Testing Capacity: Capacity 20 case:"
	" should be 20: %s\n", (StackCapacity(stack)) == 20 ? PASS : FAIL);
	printf("Testing Top: %zu\n", StackSize(stack));
	printf("pushing int 45 and float 7.2\n");
	StackPush(stack, &a);
	StackPush(stack,&b);
	printf("Testing Top: %zu\n", StackSize(stack));
	printf("Is Empty: %d\n", StackIsEmpty(stack));
	printf("Peeking - 7.2 float case: should be 7.2: %s\n", 
	*(float *)(StackPeek(stack)) > 7.1 && 
	*(float *)(StackPeek(stack)) < 7.3 ? PASS : FAIL);
	printf("Popping\n");
	StackPop(stack);
	printf("Peeking - 45 int case:, should be 45: %s\n", 
	*(int *)(StackPeek(stack)) == 45 ? PASS : FAIL);
	printf("Top: %zu\n", StackSize(stack));
	printf("Is Empty: %d\n", StackIsEmpty(stack));
	printf("Popping\n");
	StackPop(stack);
	printf("Peeking - Empty case:, should be NULL: %s\n", 
	(StackPeek(stack)) == NULL ? PASS : FAIL);
	printf("Top: %zu\n", StackSize(stack));
	printf("Is Empty: %d\n", StackIsEmpty(stack));
	StackDestroy(stack);
	
	return 0;
}
