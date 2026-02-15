/*
Owner: Uri Naor
Date: Mar 30, 2024
*/

#include <assert.h>
#include <stdlib.h>

#include "dvector.h"
#include "heap.h"

#define LEFT_CHILD(i) (2*(i) + 1)
#define RIGHT_CHILD(i) (2*(i) + 2)
#define PARENT(i) (((i) - 1) / 2)
#define GET_VALUE(p) ((void *)*(size_t *)(p))

/******************** STRUCTS ********************/
struct heap
{
    heap_cmp_func_t cmp_func;
    dvector_t *heap_container; 
};

/******************** FORWARD DECLARATIONS ********************/
static void HeapifyUp(heap_t *heap, size_t idx);
static void HeapifyDown(heap_t *heap, size_t idx);
static void Swap(size_t *a, size_t *b);

/******************** FUNCTIONS ********************/
heap_t *HeapCreate(heap_cmp_func_t cmp_func)
{
    heap_t *new_heap = NULL;

    assert(cmp_func);

    new_heap = (heap_t *)malloc(sizeof(heap_t));
    if (NULL == new_heap)
    {
        return (NULL);
    }

    new_heap->cmp_func = cmp_func;
    new_heap->heap_container = DVectorCreate(100, sizeof(size_t));
    if (NULL == new_heap->heap_container)
    {
        free(new_heap);
        return (NULL);
    }

    return (new_heap);
}

void HeapDestroy(heap_t *heap)
{
    assert(heap);

    DvectorDestroy(heap->heap_container);
    free(heap);
}

status_t HeapPush(heap_t *heap, void *data)
{
    status_t status = SUCCESS;

    assert(heap);
    assert(data);

    status = DvectorPushBack(heap->heap_container, &data);
    if (SUCCESS != status)
    {
        return (status);
    }
    
    HeapifyUp(heap, (DvectorSize(heap->heap_container)-1));

    return (status);
}

void HeapPop(heap_t *heap)
{
    size_t first_idx = 0;
    size_t last_idx = 0;

    assert(heap);
    assert(!HeapIsEmpty(heap));

    if (DvectorSize(heap->heap_container) == 1)
    {
        DvectorPopBack(heap->heap_container);
    }
    else
    {
        last_idx = DvectorSize(heap->heap_container) - 1;

        Swap(DvectorGetAccessToElement(heap->heap_container, first_idx), 
        DvectorGetAccessToElement(heap->heap_container, last_idx));

        DvectorPopBack(heap->heap_container);

        HeapifyDown(heap, first_idx);
    }
}

void *HeapPeek(const heap_t *heap)
{
    assert(heap);

    if (HeapIsEmpty(heap))
    {
        return NULL;
    }

    return (GET_VALUE(DvectorGetAccessToElement(heap->heap_container, 0)));
}

void *HeapRemove(heap_t *heap, heap_match_func_t match_func, const void *params)
{
    void *curr_data = NULL;
    size_t i = 0;
    size_t remove_idx = 0;
    size_t last_idx = 0;
    int found_match = 0;
    
    assert(heap);
    assert(match_func);
    assert(params);

    for (i = 0; i < HeapSize(heap); i++)
    {
        curr_data = GET_VALUE(DvectorGetAccessToElement(heap->heap_container, i));

        if(match_func(curr_data, params))
        {
            remove_idx = i;
            found_match = 1;
            break;
        }
    }

    if (found_match)
    {
        last_idx = DvectorSize(heap->heap_container) - 1;

        if (remove_idx == last_idx)
        {
            DvectorPopBack(heap->heap_container);
        }
        else
        {
            Swap(DvectorGetAccessToElement(heap->heap_container, remove_idx), 
            DvectorGetAccessToElement(heap->heap_container, last_idx));

            DvectorPopBack(heap->heap_container);

            HeapifyUp(heap, remove_idx);
            HeapifyDown(heap, remove_idx);
        }

        return (curr_data);
    }

    return NULL;
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return (0 == DvectorSize(heap->heap_container));
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return (DvectorSize(heap->heap_container));
}

/******************** HELPER FUNCTIONS ********************/
static void HeapifyUp(heap_t *heap, size_t idx)
{
    void *elem = NULL;
    void *parent_elem = NULL;
    
    assert(heap);
    assert(idx < DvectorSize(heap->heap_container));

    while (idx > 0)
    {
        elem = DvectorGetAccessToElement(heap->heap_container, idx);

        parent_elem = DvectorGetAccessToElement(heap->heap_container, 
                                                PARENT(idx));
        if (heap->cmp_func(GET_VALUE(elem), GET_VALUE(parent_elem)) < 0)
        {
            Swap((size_t *)elem, (size_t *)parent_elem);
            idx = PARENT(idx);
        }
        else
        {
            break;
        }
    }
}

static void HeapifyDown(heap_t *heap, size_t idx)
{
    size_t curr_idx = idx;
    size_t left_child_idx = LEFT_CHILD(idx);
    size_t vector_size = 0;
    dvector_t *dvector = NULL;
    void *curr_data = NULL;
    void *left_child_data = NULL;
    void *right_child_data = NULL;
    int cmp_children = 0;
    int cmp_result = -1;

    assert(heap);
    assert(idx < DvectorSize(heap->heap_container));

    vector_size = HeapSize(heap);
    dvector = heap->heap_container;

    while (0 > cmp_result && left_child_idx < vector_size)
    {        
        curr_data = DvectorGetAccessToElement(dvector, curr_idx);

        left_child_data = DvectorGetAccessToElement(
                                    dvector, left_child_idx);
        
        right_child_data = left_child_idx + 1 == vector_size ? NULL : 
        DvectorGetAccessToElement(dvector, left_child_idx + 1);

        cmp_children = NULL == right_child_data ? -1 : 
        heap->cmp_func(GET_VALUE(left_child_data), GET_VALUE(right_child_data));
        
        if (cmp_children > 0)
        {
            cmp_result = heap->cmp_func(
                         GET_VALUE(right_child_data), GET_VALUE(curr_data));

            if (cmp_result < 0)
            {
                Swap(curr_data, right_child_data); 
                curr_idx = left_child_idx + 1;  
            }
        }

        else
        {
            cmp_result = heap->cmp_func(
                GET_VALUE(left_child_data), GET_VALUE(curr_data));

            if (cmp_result < 0)
            {
                Swap(curr_data, left_child_data);
                curr_idx = left_child_idx;
            }
        }

        left_child_idx = curr_idx * 2 + 1;
    }
}

static void Swap(size_t *a, size_t *b)
{
    size_t temp = *a;
    *a = *b;
    *b = temp;
}
