/*
Owner: Uri Naor
Date: Mar 2, 2024
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, size_t */

#include "pqueue.h"  /* pq_t */
#include "srtlist.h" /* srtlist_t */

struct pq
{
	srtlist_t *list;
};

pq_t *PQCreate(cmp_func_t cmp_func)
{
	pq_t *new_pq = NULL;
	srtlist_t *new_list = NULL;
	
	assert(cmp_func);
	
	new_pq = malloc(sizeof(pq_t));
	if (NULL == new_pq)
	{
		return (NULL);
	}

	new_list = SrtListCreate(cmp_func);
	if (NULL == new_list)
	{
		free(new_pq);

		return (NULL);
	}
	
	new_pq->list = new_list;
	
	return (new_pq);
}

void PQDestroy(pq_t *pq)
{
	assert(pq);

	SrtListDestroy(pq->list);
	
	free(pq);
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(pq);

	return (SrtListIsIterSame(SrtListInsert(pq->list, data)
						    				, SrtListEnd(pq->list)));
}

void *PQDequeue(pq_t *pq)
{	
	assert(pq);
	
	/* protect against popping from an empty list */
	if (PQIsEmpty(pq))
	{
		return NULL;
	}
	
	return (SrtListPopFront(pq->list));
}

void *PQPeek(const pq_t *pq)
{
	assert(pq);
	
	/* protect against peeking an empty list */
	if (PQIsEmpty(pq))
	{
		return NULL;
	}
	
	return (SrtListGetData(SrtListBegin(pq->list)));
}

int PQIsEmpty(const pq_t *pq)
{
	assert(pq);
	
	return (SrtListIsEmpty(pq->list));
}

size_t PQCount(const pq_t *pq)
{
	assert(pq);
	
	return (SrtListCount(pq->list));
}

void *PQErase(pq_t *pq, match_func_t match_func, void *param)
{
	srtlist_iter_t iter_to_remove;
	void *data = NULL;
	
	assert(pq);
	assert(match_func);
	
	iter_to_remove = SrtListFindIf(SrtListBegin(pq->list), SrtListEnd(pq->list),
	 				 match_func, param);				 
	if (!(SrtListIsIterSame(iter_to_remove, SrtListEnd(pq->list))))
	{
		data = SrtListGetData(iter_to_remove);

		SrtListRemove(iter_to_remove);
	}

	return (data);
}

void PQClear(pq_t *pq)
{
	assert(pq);
	
	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}
