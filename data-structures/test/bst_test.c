/*
Owner: Uri Naor
Date: Mar 12, 2024
*/

#include <stdio.h> /*printf*/

#include "bst.h" /*bst_t, node_t*/

static void Test();
static void Test1();

int CmpFunc(const void *data, const void *params);

int main()
{
    Test();
    Test1();

    return (0);
}

static void Test()
{
    bst_iter_t iter20 = {0}, iter40 = {0}, iter60 = {0};
    bst_iter_t iter10 = {0}, iter45 = {0};
    bst_iter_t iter_next = {0}, iter_prev = {0}, iter_find = {0};
    int add_num20 = 20, add_num40 = 40, add_num60 = 60;
    int add_num10 = 10, add_num45 = 45;
    bst_t *bst = BSTCreate(&CmpFunc);
    if (!bst)
    {
        printf("CREATE FAIL\n");
        return;
    }
    
    if (!BSTIsEmpty(bst))
    {
        printf("ISEMPTY FAIL\n");
        BSTDestroy(bst);
        return;
    }

    if (0 != BSTSize(bst))
    {
        printf("SIZE FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter20 = BSTInsert(bst, &add_num20);
    if( 20 != *(int *)BSTGetData(iter20))
    {
        printf("INSERT1 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter40 = BSTInsert(bst, &add_num40);
    if( 40 != *(int *)BSTGetData(iter40))
    {
        printf("INSERT2 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter20);
    if( 40 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT1 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_prev = BSTPrev(iter40);
    if( 20 != *(int *)BSTGetData(iter_prev))
    {
        printf("PREV1 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter60 = BSTInsert(bst, &add_num60);
    if( 60 != *(int *)BSTGetData(iter60))
    {
        printf("INSERT3 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter60);
    if(!BSTIsIterSame(BSTEnd(bst), iter_next))
    {
        printf("NEXT2 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter10 = BSTInsert(bst, &add_num10);
    if( 10 != *(int *)BSTGetData(iter10))
    {
        printf("INSERT4 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter10);
    if( 20 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT3 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    if (4 != BSTSize(bst))
    {
        printf("SIZE FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_find = BSTFind(bst, &add_num60);
    if( 60 != *(int *)BSTGetData(iter_find))
    {
        printf("FIND FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter45 = BSTInsert(bst, &add_num45);
    if( 45 != *(int *)BSTGetData(iter45))
    {
        printf("INSERT4 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    BSTRemove(iter40);
    BSTRemove(iter45);
    BSTRemove(iter60);
    if (2 != BSTSize(bst))
    {
        printf("REMOVE FAIL\n");
        BSTDestroy(bst);
        return;
    }
    BSTRemove(iter20);
    BSTRemove(iter10);
    if (!BSTIsEmpty(bst))
    {
        printf("REMOVE FAIL\n");
        BSTDestroy(bst);
        return;
    }

    BSTDestroy(bst);

    printf("PASS\n");
}

static void Test1()
{
    bst_iter_t iter20 = {0}, iter15 = {0}, iter_next = {0};
    int add_num10 = 10, add_num20 = 20, add_num15 = 15;
    int add_num30 = 30, add_num17 = 17, add_num12 = 12;
    bst_t *bst = BSTCreate(&CmpFunc);
    if (!bst)
    {
        printf("CREATE FAIL\n");
        return;
    }
    BSTInsert(bst, &add_num10);
    iter20 = BSTInsert(bst, &add_num20);
    iter15 = BSTInsert(bst, &add_num15);
    BSTInsert(bst, &add_num30);

    iter_next = BSTNext(BSTBegin(bst));
    if( 15 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT1 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter_next);
    if( 20 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT2 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter_next);
    if( 30 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT3 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter_next);
    if(!BSTIsIterSame(BSTEnd(bst), iter_next))
    {
        printf("NEXT4 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    BSTRemove(iter20);

    iter_next = BSTNext(BSTBegin(bst));
    if( 15 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT5 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter20 = BSTInsert(bst, &add_num20);
    BSTInsert(bst, &add_num17);
    BSTInsert(bst, &add_num12);

    BSTRemove(iter15);

    iter_next = BSTNext(BSTBegin(bst));
    if( 12 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT1 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter_next);
    if( 17 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT2 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter_next);
    if( 20 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT3 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter_next);
    if( 30 != *(int *)BSTGetData(iter_next))
    {
        printf("NEXT4 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    iter_next = BSTNext(iter_next);
    if(!BSTIsIterSame(BSTEnd(bst), iter_next))
    {
        printf("NEXT5 FAIL\n");
        BSTDestroy(bst);
        return;
    }

    BSTDestroy(bst);

    printf("PASS\n");
}

int CmpFunc(const void *data, const void *params)
{
    return *(int *)data - *(int *)params;
}
