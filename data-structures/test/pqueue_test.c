/*
Owner: Uri Naor
Date: Mar 2, 2024
*/

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

#include <stdio.h> /* printf */

#include "pqueue.h" /* pq_t */

/**************** FORWARD DECLARATIONS ****************/
static int CmpFunc(const void *data, const void *param);
static int MatchFunc(const void *data, void *param);

/******************** TESTS ********************/
int TestFlow()
{
	pq_t *new_pq = PQCreate(CmpFunc);
	int array[] = {5, 3, 2, 1, 7, 12, 8, 0, -6, -67, 172, 3, 9};
	int temp = 0;
	
	if(!PQIsEmpty(new_pq))
	{
		printf("Testing IsEmpty & Create: "
		"Empty PQ case: Should be true, but result is false.\n");
		PQDestroy(new_pq);
		return 1;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[0]))
	{
		printf("Pushing first item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 2;
	}
	
	if(PQIsEmpty(new_pq))
	{
		printf("Testing IsEmpty: "
		"one element in Q case: Should be false, but result is true.\n");
		PQDestroy(new_pq);
		return 3;
	}
	
	if(5 != *(int *)PQPeek(new_pq))
	{
		printf("Testing PQPeek: "
		"one element in Q case: Should be 5, but result is different.\n");
		PQDestroy(new_pq);
		return 4;
	}
	
	if(1 != PQCount(new_pq))
	{
		printf("Testing PQCount: "
		"one element in Q case: Should be 1, but result is different.\n");
		PQDestroy(new_pq);
		return 5;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[1]))
	{
		printf("Pushing 2nd item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 6;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[2]))
	{
		printf("Pushing 3rd item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 7;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[3]))
	{
		printf("Pushing 4th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 8;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[4]))
	{
		printf("Pushing 5th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 9;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[5]))
	{
		printf("Pushing 6th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 10;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[6]))
	{
		printf("Pushing 7th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 11;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[7]))
	{
		printf("Pushing 8th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 12;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[8]))
	{
		printf("Pushing 9th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 13;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[9]))
	{
		printf("Pushing 10th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 14;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[10]))
	{
		printf("Pushing 11th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 15;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[11]))
	{
		printf("Pushing 12th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 16;
	}
	
	if(0 != PQEnqueue(new_pq, (void *)&array[12]))
	{
		printf("Pushing 13th item to queue case: Should work, but failed.\n");
		PQDestroy(new_pq);
		return 17;
	}
	
	temp = *(int *)PQDequeue(new_pq);
	if(-67 != temp)
	{
		printf("Testing PQDequeue: "
		"13 elements in Q case: Should be -67, but result is %d.\n", temp);
		PQDestroy(new_pq);
		return 18;
	}
	
	temp = *(int *)PQDequeue(new_pq);
	if(-6 != temp)
	{
		printf("Testing PQDequeue: "
		"12 elements in Q case: Should be -6, but result is %d.\n", temp);
		PQDestroy(new_pq);
		return 19;
	}
	
	temp = *(int *)PQDequeue(new_pq);
	if(0 != temp)
	{
		printf("Testing PQDequeue: "
		"11 elements in Q case: Should be 0, but result is %d.\n", temp);
		PQDestroy(new_pq);
		return 20;
	}
	
	temp = *(int *)PQDequeue(new_pq);
	if(1 != temp)
	{
		printf("Testing PQDequeue: "
		"10 elements in Q case: Should be 1, but result is %d.\n", temp);
		PQDestroy(new_pq);
		return 21;
	}
	
	temp = *(int *)PQDequeue(new_pq);
	if(2 != temp)
	{
		printf("Testing PQDequeue: "
		"9 elements in Q case: Should be 2, but result is %d.\n", temp);
		PQDestroy(new_pq);
		return 22;
	}
	
	temp = *(int *)PQDequeue(new_pq);
	if(3 != temp)
	{
		printf("Testing PQDequeue: "
		"8 elements in Q case: Should be 3, but result is %d.\n", temp);
		PQDestroy(new_pq);
		return 23;
	}
	
	temp = *(int *)PQDequeue(new_pq);
	if(3 != temp)
	{
		printf("Testing PQDequeue: "
		"7 elements in Q case: Should be 3, but result is %d.\n", temp);
		PQDestroy(new_pq);
		return 24;
	}
	
	temp = *(int *)PQDequeue(new_pq);
	if(5 != temp)
	{
		printf("Testing PQDequeue: "
		"6 elements in Q case: Should be 5, but result is %d.\n", temp);
		PQDestroy(new_pq);
		return 25;
	}
	
	if(5 != PQCount(new_pq))
	{
		printf("Testing PQCount: "
		"5 elements in Q case: Should be 5, but result is different.\n");
		PQDestroy(new_pq);
		return 26;
	}
	
	if(7 != *(int *)PQPeek(new_pq))
	{
		printf("Testing PQPeek: "
		"5 elements in Q case: Should be 7, but result is different.\n");
		PQDestroy(new_pq);
		return 27;
	}
	
	temp = *(int *)PQErase(new_pq, MatchFunc, &array[12]);
	if(9 != temp)
	{
		printf("Testing PQErase: "
		"5 element in Q case: Should be 9, but result is %d.\n", temp);
		PQDestroy(new_pq);
		return 28;
	}
	
	if(4 != PQCount(new_pq))
	{
		printf("Testing PQCount: "
		"4 elements in Q case: Should be 4, but result is different.\n");
		PQDestroy(new_pq);
		return 29;
	}
	
	PQClear(new_pq);
	
	if(!PQIsEmpty(new_pq))
	{
		printf("Testing IsEmpty after PQClear: "
		"Empty Q case: Should be true, but result is false.\n");
		PQDestroy(new_pq);
		return 30;
	}
	
	PQDestroy(new_pq);
	
	return 0;
}

/******************** MAIN ********************/
int main()
{
	int test_status = TestFlow();
	
	if(test_status == 0)
	{
		printf("PQ| ALL TESTS: %s\n", PASS);
	}
	else
	{
		printf("PQ| %s AT %d \n", FAIL, test_status);
	}

	return 0;
}

/******************** HELPER FUNCTIONS ********************/
static int CmpFunc(const void *data, const void *param)
{
    return (*(int *)data - *(int *)param);
}

static int MatchFunc(const void *data, void *param)
{
    return (*(int *)data == *(int *)param);
}
