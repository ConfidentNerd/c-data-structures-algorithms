/*
Owner: Uri Naor
Date: Feb 16, 2024
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */

#include "slist.h" /* SListCreate */
#include "queue.h" /* queue_t */

struct queue
{
	slist_t *list;
};

queue_t *QCreate()
{
	queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == new_queue)
	{
		printf("Allocation creating a queue has failed.\n");
		return NULL;
	}
	
	new_queue->list = SListCreate();
	if(NULL == new_queue->list)
	{
		free(new_queue);
		return NULL;
	}
	
	return (new_queue);
}


void QDestroy(queue_t *queue)
{
	assert(queue);

	SListDestroy(queue->list);
	free(queue);
}

int QEnqueue(queue_t *queue, void *data)
{
	slist_iter_t dummy_node;

	assert(queue);
	
	dummy_node = SListInsert(SListEnd(queue->list), data);
	
	return (SListIsIterSame(SListEnd(queue->list), dummy_node));
}

void QDequeue(queue_t *queue)
{
	assert(queue);
	
	SListRemove(SListBegin(queue->list));
}

void *QPeek(const queue_t *queue)
{
	assert(queue);
	
	return (SListGetData(SListBegin(queue->list)));
}

size_t QCount(const queue_t *queue)
{
	assert(queue);
	
	return (SListCount(queue->list));
}

int QIsEmpty(const queue_t *queue)
{
	assert(queue);
	
	return (SListIsEmpty(queue->list));
}

void QAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);
	
	SListAppend(dest->list, src->list);
}
