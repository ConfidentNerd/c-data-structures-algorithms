/*
Owner: Uri Naor
Date: Mar 2, 2024
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, size_t */

#include "heap.h" /* heap_t * */
#include "pqueue_heap.h"

struct pq
{
	heap_t *heap;
};

pq_t *PQCreate(cmp_func_t cmp_func)
{
	pq_t *new_pq = NULL;
	heap_t *new_heap = NULL;
	
	assert(cmp_func);
	
	new_pq = malloc(sizeof(pq_t));
	if (NULL == new_pq)
	{
		return (NULL);
	}

	new_heap = HeapCreate((heap_cmp_func_t)cmp_func);
	if (NULL == new_heap)
	{
		free(new_pq);

		return (NULL);
	}
	
	new_pq->heap = new_heap;
	
	return (new_pq);
}

void PQDestroy(pq_t *pq)
{
	assert(pq);

	HeapDestroy(pq->heap);
	
	free(pq);
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(pq);
	assert(data);

	return (HeapPush(pq->heap, data));
}

void *PQDequeue(pq_t *pq)
{
    void *data = NULL;

	assert(pq);
	
	if (PQIsEmpty(pq)) 
	{
		return NULL;
	}
    
    data = HeapPeek(pq->heap);
    HeapPop(pq->heap);

	return(data);
}

void *PQPeek(const pq_t *pq)
{
	assert(pq);
	
	return (HeapPeek(pq->heap));
}

int PQIsEmpty(const pq_t *pq)
{
	assert(pq);
	
	return (HeapIsEmpty(pq->heap));
}

size_t PQCount(const pq_t *pq)
{
	assert(pq);
	
	return (HeapSize(pq->heap));
}

void *PQErase(pq_t *pq, match_func_t match_func, void *param)
{
	assert(pq);
	assert(match_func);
	assert(param);

	return (HeapRemove(pq->heap, (heap_match_func_t)match_func, param));
}

void PQClear(pq_t *pq)
{
	assert(pq);
	
	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}
