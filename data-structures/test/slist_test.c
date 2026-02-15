/*
Owner: Uri Naor
Date: Feb 16, 2024
*/

#include <stdio.h> /* printf */
#include "slist.h" /*  SListCreate */

#define PASS (0)
#define FAIL (1)

static int Find(const void *data, void* param)
{
	return *(int *)data == *(int *)param;
}

int TestSlist()
{
    int data = 6, data2 = 10;
	slist_t *list = SListCreate();
    size_t count = 0;
     
    SListInsert(SListBegin(list), &data);
    SListInsert(SListEnd(list), &data2);

    if(*(int *)SListGetData(SListBegin(list)) != 6)
    {
        printf("Insert + GetData + Begin Fail");
        return FAIL;
    }

    if (*(int *)SListGetData(SListNext(SListBegin(list))) != 10)
    {
        printf("Next : Fail");
        return FAIL;
    }
    
    if ((*(int*)SListGetData(SListFind(SListBegin(list), SListEnd(list), Find, &data)) != 6))
    {
        printf("Find : Fail");
        return FAIL;
    }

    SListRemove(SListBegin(list));

    if((*(int *)SListGetData(SListBegin(list)) != 10))
    {
        printf("Remove : Fail");
        return FAIL;
    }
    
    if(SListCount(list) != 1)
    {
        printf("Count size 1 : Fail");
        return FAIL;
    }
    
    SListInsert(SListBegin(list), &data);
    SListInsert(SListEnd(list), &data2);
    SListInsert(SListEnd(list), &data2);
    SListInsert(SListEnd(list), &data2);
    SListInsert(SListEnd(list), &data2);
    SListInsert(SListEnd(list), &data2);

    if(SListCount(list) != 7)
    {
        printf("Count size 7 : Fail");
        return FAIL;
    }
    
    SListSetData(SListBegin(list), &data2);

    if(*(int *)SListGetData(SListBegin(list)) != 10)
    {
        printf("SetData : Fail");
        return FAIL;
    }
   
    if(SListIsEmpty(list))
    {
        printf("IsEmpty when fill: Fail");
        return FAIL;
    }
    
    for (count = SListCount(list); count != 0; --count)
    {
        SListRemove(SListBegin(list));
    }

    if(!SListIsEmpty(list))
    {
        printf("IsEmpty when empty: Fail");
        return FAIL;
    }
    
    SListDestroy(list);

    return (PASS);
}

int main()
{
    if(!TestSlist())
     printf("\n SList Test : %s", "Pass\n");

	return 0;
}

