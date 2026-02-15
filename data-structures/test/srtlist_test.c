/*
Owner: Uri Naor
Date: Feb 22, 2024
*/

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */
 
#include "srtlist.h" /* srtlist */

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

static size_t tests_fails = 0;

static void RunTest(const char* test, int result, int expected);
static void IsAllPassed();
static int CmpFunc(const void *data, const void *param);
static int IsEven(const void *data, void *param);
static void TestSrtList();

int main()
{
	TestSrtList();
	return (0);
}

static void RunTest(const char* test, int result, int expected)
{
	if (result != expected)
	{	
    	printf("%s: %s\n", test, FAIL);
    	tests_fails = 1;
	}
}

static void IsAllPassed()
{	
	if (!tests_fails)
	{
		printf("All Tests: %s\n" , PASS);
	}
}

static void TestSrtList()
{   
  	int num1 = 5 , num2 = 10 , num3 = 3 , num4 = 12 , num11 = 4, num12 = 6,
  	num5 = 7, num6 = 2, num7 = 11, num8 = 1, num9 = 13, num10 = 20;
  	size_t i = 0;
  	
    srtlist_iter_t iter = {NULL};
    srtlist_t *srtlist = SrtListCreate(CmpFunc);
    srtlist_t *srtlist_src = SrtListCreate(CmpFunc);
    int merge_result[] = {1,2,3,3,4,5,5,6,7,7,7,10,10,11,12,12,13,20};
    
    tests_fails = 0;
    
    printf("TestSrtList:\n");
 
    iter = SrtListBegin(srtlist);
    RunTest("Is Empty", SrtListIsEmpty(srtlist) , 1);
    iter = SrtListInsert(srtlist, &num1);
    SrtListRemove(iter);
    iter = SrtListInsert(srtlist, &num1);
    iter = SrtListInsert(srtlist, &num2);
    RunTest("Is Empty After Insert", SrtListIsEmpty(srtlist) , 0);
        
    SrtListInsert(srtlist, &num3);
    SrtListInsert(srtlist, &num4);
    SrtListInsert(srtlist, &num5);
    RunTest("Count", SrtListCount(srtlist) , 5);
    
    iter = SrtListBegin(srtlist);
    RunTest("Insert 1", *(int *)SrtListGetData(iter), num3);
    iter = SrtListNext(iter);
    RunTest("Insert 2", *(int *)SrtListGetData(iter), num1);
    iter = SrtListNext(iter);
    RunTest("Insert 3", *(int *)SrtListGetData(iter), num5);
    iter = SrtListNext(iter);
    RunTest("Insert 4", *(int *)SrtListGetData(iter), num2);
    iter = SrtListNext(iter);
    RunTest("Insert 5", *(int *)SrtListGetData(iter), num4);
    
    iter = SrtListEnd(srtlist);
    iter = SrtListPrev(SrtListPrev(iter));
    SrtListRemove(iter);
    iter = SrtListBegin(srtlist);
    RunTest("Element 1", *(int *)SrtListGetData(iter), num3);
    iter = SrtListNext(iter);
    RunTest("Element 2", *(int *)SrtListGetData(iter), num1);
    iter = SrtListNext(iter);
    RunTest("Element 3", *(int *)SrtListGetData(iter), num5);
    iter = SrtListNext(iter);
    RunTest("Element 4", *(int *)SrtListGetData(iter), num4);
    
    iter = SrtListPrev(iter);
    SrtListPopBack(srtlist);
    RunTest("After Pop Back", *(int *)SrtListGetData(iter), num5);
    SrtListPopFront(srtlist);
    iter = SrtListBegin(srtlist);
    RunTest("After Pop Front", *(int *)SrtListGetData(iter), num1);
    
    SrtListInsert(srtlist, &num3);
    SrtListInsert(srtlist, &num2);
    SrtListInsert(srtlist, &num4);
    SrtListInsert(srtlist, &num5);
    
  	iter = SrtListFind(srtlist, SrtListBegin(srtlist), 
  					      SrtListEnd(srtlist), &num4);
  					          
    RunTest("Find" , *(int *)SrtListGetData(iter) , num4);
    
    iter = SrtListFindIf(SrtListBegin(srtlist), SrtListEnd(srtlist), IsEven, 0);
    
    RunTest("FindIf" , *(int *)SrtListGetData(iter) , num2);
    
    SrtListInsert(srtlist_src, &num1);
    SrtListInsert(srtlist_src, &num2);
    SrtListInsert(srtlist_src, &num3);
    SrtListInsert(srtlist_src, &num4);
    SrtListInsert(srtlist_src, &num5);
    SrtListInsert(srtlist_src, &num6);
    SrtListInsert(srtlist_src, &num7);
    SrtListInsert(srtlist_src, &num8);
    SrtListInsert(srtlist_src, &num9);
    SrtListInsert(srtlist_src, &num10);
    SrtListInsert(srtlist_src, &num11);
    SrtListInsert(srtlist_src, &num12);
    
    
    SrtListMerge(srtlist, srtlist_src);
    
    iter = SrtListBegin(srtlist);
    
    for (i = 0; i < 18; ++i)
    {
    	RunTest("Merge", *(int *)SrtListGetData(iter), merge_result[i]);
    	
    	iter = SrtListNext(iter);
    }
    
	SrtListDestroy(srtlist);
	SrtListDestroy(srtlist_src);
	
	IsAllPassed();
}

static int CmpFunc(const void *data, const void *param)
{
    return (*(int *)data - *(int *)param);
}

static int IsEven(const void *data, void *param)
{
	(void)param;
    return (*(int *)data % 2 == 0);
}

