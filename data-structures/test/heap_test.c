/*
Owner: Uri Naor
Date: Mar 30, 2024
*/

#include <stdio.h> /*printf*/

#include "heap.h" /*heap_t*/

static status_t TestFlowHeap1();
static status_t TestFlowHeap2();
static status_t TestFlowHeap3();
static int CmpInts(const void *a, const void *b);

int main()
{
    status_t status = TestFlowHeap1();

    if (SUCCESS != status)
    {
        printf("test flow 1 failed!\n");
    }
    else
    {
        printf("test flow 1 SUCCESS!\n");
    }

    status = TestFlowHeap2();

    if (SUCCESS != status)
    {
        printf("test flow 2 failed!\n");
    }
    else
    {
        printf("test flow 2 SUCCESS!\n");
    }

    
    status = TestFlowHeap3();

    if (SUCCESS != status)
    {
        printf("test flow 3 failed!\n");
    }
    else
    {
        printf("test flow 3 SUCCESS!\n");
    }

    printf("exit with status = %d\n", status);
    return (0);
}

static status_t TestFlowHeap3()
{
    heap_t *heap = HeapCreate(CmpInts);
    size_t size = 0;
    int i = 0; 
    int peek = 0;
    int arr[21] = {5,1,2,0,20,13,14,3,4,7,6,8,9,10,11,15,16,17,18,19,12};  

    for (i = 20; i >= 0; --i)
    {
        if (SUCCESS != HeapPush(heap, &arr[i]))
        {
            printf("failed to push %d\n", i);
            HeapDestroy(heap);
            return FAILURE;
        }
    }

    size = HeapSize(heap);
    if (21 != size)
    {
        printf("line %d HeapSize failed! should be 21 but size = %lu\n", 
        __LINE__,size);
        HeapDestroy(heap);
        return (FAILURE);
    }

    peek = *(int*)HeapPeek(heap);
    if (0 != peek)
    {
        printf("line %d HeapPeek failed! should be 0 but peek = %d\n", 
        __LINE__, peek);
        HeapDestroy(heap);
        return (FAILURE);
    }

    for (i = 0; i < 21; ++i)
    {
        peek = *(int*)HeapPeek(heap);
        if (i != peek)
        {
            printf("line %d HeapPeek failed! should be %d but peek = %d\n",
            __LINE__, i, peek);
            HeapDestroy(heap);
            return (FAILURE);
        }

        HeapPop(heap);
        size = HeapSize(heap);
        if (21-(i+1) != (int)size)
        {
            printf("line %d HeapSize failed! should be 10 but size = %lu\n",
            __LINE__, size);
            HeapDestroy(heap);
            return (FAILURE);
        }
    }

    HeapDestroy(heap);
    return SUCCESS;
}

static status_t TestFlowHeap2()
{
    heap_t *heap = HeapCreate(CmpInts);
    size_t size = 0;
    int i = 0; 
    int peek = 0;
    int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};  

    for (i = 20; i >= 0; --i)
    {
        if (SUCCESS != HeapPush(heap, &arr[i]))
        {
            printf("failed to push %d\n", i);
            HeapDestroy(heap);
            return FAILURE;
        }
    }

    size = HeapSize(heap);
    if (21 != size)
    {
        printf("line %d HeapSize failed! should be 21 but size = %lu\n", 
        __LINE__,size);
        HeapDestroy(heap);
        return (FAILURE);
    }

    peek = *(int*)HeapPeek(heap);
    if (0 != peek)
    {
        printf("line %d HeapPeek failed! should be 0 but peek = %d\n", 
        __LINE__, peek);
        HeapDestroy(heap);
        return (FAILURE);
    }

    for (i = 0; i < 21; ++i)
    {
        peek = *(int*)HeapPeek(heap);
        if (i != peek)
        {
            printf("line %d HeapPeek failed! should be %d but peek = %d\n",
            __LINE__, i, peek);
            HeapDestroy(heap);
            return (FAILURE);
        }

        HeapPop(heap);
        size = HeapSize(heap);
        if (21-(i+1) != (int)size)
        {
            printf("line %d HeapSize failed! should be 10 but size = %lu\n",
            __LINE__, size);
            HeapDestroy(heap);
            return (FAILURE);
        }
    }

    if (!HeapIsEmpty(heap))
    {
        printf("line %d HeapIsEmpty failed! should be empty\n" , __LINE__);
        HeapDestroy(heap);
        return (FAILURE);
    }

    HeapDestroy(heap);
    return (SUCCESS);
}

static status_t TestFlowHeap1()
{
    heap_t *heap = HeapCreate(CmpInts);
    size_t size = 0; 
    int peek = 0;
    int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};  

    if (!heap)
    {
        printf("line %d HeapCreate failed!\n", __LINE__);
        return (FAILURE);
    }

    if (!HeapIsEmpty(heap))
    {
        printf("line %d HeapIsEmpty failed! should be empty\n", __LINE__);
        HeapDestroy(heap);
        return (FAILURE);
    }

    size = HeapSize(heap);
    if (0 != size)
    {
        printf("line %d HeapSize failed! should be 0 but size = %lu\n", __LINE__
        ,size);
        HeapDestroy(heap);
        return (FAILURE);
    }

    if (SUCCESS != HeapPush(heap, &arr[4]))
    {
        printf("line %d HeapPush failed!", __LINE__);
        HeapDestroy(heap);
        return (FAILURE);
    }

    size = HeapSize(heap);
    if (1 != size)
    {
        printf("line %d HeapSize failed! should be 1 but size = %lu\n",__LINE__ 
        ,size);
        HeapDestroy(heap);
        return (FAILURE);
    }

    peek = *(int*)HeapPeek(heap);
    if (4 != peek)
    {
        printf("line %d HeapPeek failed! peek should be 4 but peek = %d\n",
                __LINE__,peek);
        HeapDestroy(heap);
        return (FAILURE);
    }

    if (HeapIsEmpty(heap))
    {
        printf("line %d HeapIsEmpty failed! should'nt be empty\n",__LINE__);
        HeapDestroy(heap);
        return (FAILURE);
    }

    HeapPop(heap);

    if (!HeapIsEmpty(heap))
    {
        printf("line %d HeapIsEmpty failed! should be empty\n",__LINE__);
        HeapDestroy(heap);
        return (FAILURE);
    }
    
    size = HeapSize(heap);
    if (0 != size)
    {
        printf("line %d HeapSize failed! should be 0 but size = %lu\n", 
        __LINE__,
        size);
        HeapDestroy(heap);
        return (FAILURE);
    }

    HeapPush(heap, &arr[4]);
    HeapPush(heap, &arr[2]);

    size = HeapSize(heap);
    if (2 != size)
    {
        printf("line %d HeapSize failed! should be 2 but size = %lu\n", 
        __LINE__,
        size);
        HeapDestroy(heap);
        return (FAILURE);
    }

    peek = *(int*)HeapPeek(heap);
    if (2 != peek)
    {
        printf("line %d HeapPeek failed! peek should be 2 but peek = %d\n",
                __LINE__,peek);
        HeapDestroy(heap);
        return (FAILURE);
    }

    HeapPop(heap);
    peek = *(int*)HeapPeek(heap);
    if (4 != peek)
    {
        printf("line %d HeapPeek failed! peek should be 4 but peek = %d\n",
                __LINE__,peek);
        HeapDestroy(heap);
        return (FAILURE);
    }

    HeapDestroy(heap);
    return (SUCCESS);
}

static int CmpInts(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}
