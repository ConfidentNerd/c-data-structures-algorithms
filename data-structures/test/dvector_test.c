/*
Owner: Uri Naor
Date: Feb 13, 2024
*/

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

#include <stdio.h> /* printf */
#include "dvector.h"

/******************** TESTS ********************/
int main()
{
	int a = 45;
	float b = 7.2;
	
	dvector_t *dvector = DVectorCreate(10, 4);
	printf("Created vector of capacity 10, that holds 4 byte elements.\n");
	printf("Testing Capacity: Capacity 10 case:"
	" should be 10: %s\n", (DvectorCapacity(dvector)) == 10 ? PASS : FAIL);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("pushing int 45 and float 7.2\n");
	DvectorPushBack(dvector, &a);
	DvectorPushBack(dvector,&b);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	
	printf("Getting Element  - int idx 0 case: should be 45: %s\n", 
	*(int *)(DvectorGetAccessToElement(dvector, 0)) == 45 ? PASS : FAIL);
	
	printf("Getting Element  - float idx 1 case: should be 7.2: %s\n", 
	*(float *)(DvectorGetAccessToElement(dvector, 1)) > 7.1 && 
	*(float *)(DvectorGetAccessToElement(dvector, 1)) < 7.3 ? PASS : FAIL);
	
	printf("\nPushing until capacity auto expands\n");
	DvectorPushBack(dvector, &a);
	DvectorPushBack(dvector, &a);
	DvectorPushBack(dvector, &a);
	DvectorPushBack(dvector, &a);
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: Capacity 10 case:"
	" should be 10: %s\n", (DvectorCapacity(dvector)) == 10 ? PASS : FAIL);
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: Capacity 20 case:"
	" should be 20: %s\n", (DvectorCapacity(dvector)) == 20 ? PASS : FAIL);
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: Capacity 20 case:"
	" should be 20: %s\n", (DvectorCapacity(dvector)) == 20 ? PASS : FAIL);
	
	printf("\nPopping to check capacity auto shrinks\n");
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPopBack(dvector);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	
	printf("Pushing to check capacity auto growth\n");
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	DvectorPushBack(dvector, &a);
	printf("Testing Size: %lu\n", DvectorSize(dvector));
	printf("Testing Capacity: %lu\n", DvectorCapacity(dvector));
	
	printf("Calling destroy\n");
	DvectorDestroy(dvector);
	
	return 0;
}



