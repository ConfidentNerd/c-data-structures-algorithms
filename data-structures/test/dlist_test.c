/*
Owner: Uri Naor
Date: Feb 19, 2024
*/

#include <stdio.h> /* printf */
#include "dlist.h" /*  DListCreate */

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

/******************** HELPER FUNCTIONS ********************/	
static int Find(const void *data, void* param)
{
	return *(int *)data == *(int *)param;
}

/******************** TEST FUNCTIONS ********************/
int TestFlow()
{
	int data1 = 5;
	int data2 = 12;
	int data3 = 3;
	int data4 = 1;
	int data5 = 9;
	
	int val1 = 1;
	int val2 = 2;
	int val3 = 3;
	int val4 = 4;
	int val5 = 5;
	
	dlist_iter_t iter1 = NULL;
	
	dlist_t *list = DListCreate();
	dlist_t *splice_list = DListCreate();
	dlist_t *found_elements = DListCreate();
	
	dlist_iter_t from = NULL;
	dlist_iter_t to = NULL;
	dlist_iter_t where = NULL;
	
	if(DListIsEmpty(list) != 1)
	{
		printf("Empty List Case: Should be 1, but result is different.\n");
		return 1;
	}
	
	DListInsert(DListBegin(list), &data1);
	DListInsert(DListEnd(list), &data2);
	DListInsert(DListBegin(list), &data3);
	
	if(*(int *)DListGetData(DListBegin(list)) != 3)
	{
		printf("3 elements in list case: 1st element should be 3, but result is different.\n");
		return 2;
	}
	
	if(*(int *)DListGetData(DListPrev(DListEnd(list))) != 12)
	{
		printf("3 elements in list case: 3st element should be 12, but result is different.\n");
		return 3;
	}
	
	iter1 = DListNext(DListBegin(list));
	
	if(*(int *)DListGetData(iter1) != 5)
	{
		printf("3 elements in list case: 2st element should be 5, but result is different.\n");
		return 4;
	}
	
	if((*(int*)DListGetData(DListFind(DListBegin(list), DListEnd(list),
		Find, &data2)) != 12))
	{
		printf("3 elements in list case: Find 2st element should be 12, but result is different.\n");
		return 5;
	}
	
	DListRemove(DListBegin(list));
	
	if(*(int *)DListGetData(DListBegin(list)) != 5)
	{
		printf("2 elements in list case: 1st element should be 5, but result is different.\n");
		return 6;
	}
	
	if(DListCount(list) != 2)
    {
    	printf("2 elements in list case: count should be 2, but result is different.\n");
        return 7;
    }
    
    DListPushBack(list, &data5);
    DListPushBack(list, &data5);
    DListPushBack(list, &data5);
    DListPushBack(list, &data5);
    DListPushBack(list, &data5);
    
    DListPushFront(list, &data4);
    DListPushFront(list, &data4);
    DListPushFront(list, &data4);
    DListPushFront(list, &data4);
    DListPushFront(list, &data4);
    
    if(DListCount(list) != 12)
    {
    	printf("12 elements in list case: count should be 12, but result is different.\n");
        return 8;
    }
    
    DListMultiFind(DListBegin(list), DListEnd(list), Find, &data4, found_elements);
    
    if(DListCount(found_elements) != 5)
    {
    	printf("5 elements in found_elements list case: count should be 5, but result is different.\n");
        return 9;
    }
    
    if(*(int *)DListGetData(DListBegin(found_elements)) != 1)
	{
		printf("5 elements in found_elements list case: 1st element should be 1, but result is different.\n");
		return 10;
	}
	
    if(*(int *)DListGetData(DListNext(DListBegin(found_elements))) != 1)
	{
		printf("5 elements in found_elements list case: 2nd element should be 1, but result is different.\n");
		return 11;
	}
	
	   if(*(int *)DListGetData(DListPrev(DListEnd(found_elements))) != 1)
	{
		printf("5 elements in found_elements list case: 5th element should be 1, but result is different.\n");
		return 12;
	}
	
	if(*(int *)DListGetData(DListPrev(DListEnd(list))) != 9)
	{
		printf("12 elements in list case: 12th element should be 9, but result is different.\n");
		return 13;
	}
	
	DListPopBack(list);
	DListPopBack(list);
	DListPopBack(list);
	DListPopBack(list);
	DListPopBack(list);
	
	if(*(int *)DListGetData(DListPrev(DListEnd(list))) != 12)
	{
		printf("7 elements in list case: 7th element should be 12, but result is different.\n");
		return 14;
	}
	
	if(*(int *)DListGetData(DListBegin(list)) != 1)
	{
		printf("7 elements in list case: 1st element should be 1, but result is different.\n");
		return 15;
	}
	
	DListPopFront(list);
	DListPopFront(list);
	DListPopFront(list);
	DListPopFront(list);
	DListPopFront(list);
	
	if(*(int *)DListGetData(DListBegin(list)) != 5)
	{
		printf("2 elements in list case: 1st element should be 5, but result is different.\n");
		return 16;
	}
    
    DListPushBack(splice_list, &val1);
    DListPushBack(splice_list, &val2);
    DListPushBack(splice_list, &val3);
    DListPushBack(splice_list, &val4);
    DListPushBack(splice_list, &val5);
    
    where = DListNext(DListBegin(splice_list));
    from = DListNext(where);
    to = DListPrev(DListEnd(splice_list));
    
    DListSplice(from, to, where);
    
    if(*(int *)DListGetData(DListBegin(splice_list)) != 1)
	{
		printf("5 elements in splice_list case: 1st element should be 1, but result is different.\n");
		return 17;
	}
	
	if(*(int *)DListGetData(DListNext(DListBegin(splice_list))) != 3)
	{
		printf("5 elements in splice_list case: 2st element should be 3, but result is different.\n");
		return 18;
	}
	
	if(*(int *)DListGetData(DListNext(DListNext(DListBegin(splice_list)))) != 4)
	{
		printf("5 elements in splice_list case: 3st element should be 4, but result is different.\n");
		return 19;
	}
	
	if(*(int *)DListGetData(DListPrev(DListPrev(DListEnd(splice_list)))) != 2)
	{
		printf("5 elements in splice_list case: 4st element should be 2, but result is different.\n");
		return 20;
	}
	
	if(*(int *)DListGetData(DListPrev(DListEnd(splice_list))) != 5)
	{
		printf("5 elements in splice_list case: 5st element should be 5, but result is different.\n");
		return 21;
	}
	
	DListDestroy(list);
	DListDestroy(splice_list);
	DListDestroy(found_elements);
    
    return 0;
}

/******************** MAIN ********************/
int main()
{
	int test_status = TestFlow();
	
	if(test_status == 0)
	{
		printf("DList| ALL TESTS: %s\n", PASS);
	}
	else
	{
		printf("DList| %s AT %d \n", FAIL, test_status);
	}

	return 0;
}

