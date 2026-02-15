/*
Owner: Uri Naor
Date: Feb 16, 2024
*/

#include <stdio.h> /*printf*/

#include "queue.h" /*queue_t*/

static int TestFlowQueue();

enum STATUS
{
	SUCCESS = 0,
	FAILURE
};

int main()
{	
	printf("exit with status: %d\n", TestFlowQueue());
	return (0);
}

static int TestFlowQueue()
{
	queue_t *queue = QCreate();
	queue_t *queue2 = NULL;
	queue_t *queue3 = QCreate();
	
	int a = 1, b = 2, c = 3, d = 4, e = 5;
	
	if (!queue)
	{
		if (queue3) QDestroy(queue3);
		printf("QCreate FAILED!\n\n");
		return FAILURE;
	}
	
	if (!QIsEmpty(queue))
	{
		QDestroy(queue);
		QDestroy(queue3);
		printf("QIsEmpty FAILED\n\n");
		return FAILURE;
	}
	
	if (FAILURE == QEnqueue(queue, &a))
	{
		QDestroy(queue);
		QDestroy(queue3);
		printf("QEnqueue FAILED\n\n");
		return FAILURE;
	}
	
	if (a != *(int *)QPeek(queue))
	{
		QDestroy(queue);
		QDestroy(queue3);
		printf("QPeek FAILED\n\n");
		return FAILURE;
	}
	
	if (1 != QCount(queue))
	{
		QDestroy(queue);
		QDestroy(queue3);
		printf("QCount FAILED\n\n");
		return FAILURE;
	}
	
	if (QIsEmpty(queue))
	{
		QDestroy(queue);
		QDestroy(queue3);
		printf("QIsEmpty FAILED\n\n");
		return FAILURE;
	}
	
	queue2 = QCreate();
	QEnqueue(queue2, &b);
	QEnqueue(queue2, &c);
	QEnqueue(queue2, &d);
	QEnqueue(queue2, &e);
	
	if (4 != QCount(queue2))
	{
		QDestroy(queue);
		QDestroy(queue2);
		QDestroy(queue3);
		printf("QCount FAILED\n\n");
		return FAILURE;
	}
	
	QAppend(queue, queue2);
	
	if (5 != QCount(queue))
	{
		QDestroy(queue);
		QDestroy(queue2);
		QDestroy(queue3);
		printf("QAppend FAILED\n\n");
		return FAILURE;
	}
	
	QEnqueue(queue3, &b);
	QDequeue(queue3);
	QEnqueue(queue3, &b);
	
	if (1 != QCount(queue3))
	{
		QDestroy(queue);
		QDestroy(queue2);
		QDestroy(queue3);
		printf("Add-Remove-Add Test FAILED\n\n");
		return FAILURE;
	}
	
	QDestroy(queue);
	QDestroy(queue2);
	QDestroy(queue3);
	return SUCCESS;
}
