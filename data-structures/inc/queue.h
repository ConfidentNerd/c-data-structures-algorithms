/*
Owner: Uri Naor
Date: Feb 16, 2024

Queue

Description:
A queue is a linear data structure that follows the First In, First Out (FIFO) 
principle. This implementation uses a singly linked list as the underlying 
container.
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates a new empty queue                                    */
/* Arguments:    none                                                         */
/* Return value: returns a pointer to the newly created queue                 */
/******************************************************************************/
queue_t *QCreate();

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  destroys the queue and frees all associated memory           */
/* Arguments:    queue - pointer to the queue                                 */
/* Return value: does not return anything                                     */
/******************************************************************************/
void QDestroy(queue_t *queue);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  inserts a new element into the back of the queue             */
/* Arguments:    queue - pointer to the queue                                 */
/*               data - pointer to the data to be added                       */
/* Return value: returns 0 on success, 1 on failure                           */
/******************************************************************************/
int QEnqueue(queue_t *queue, void *data);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes the element from the front of the queue              */
/* Arguments:    queue - pointer to the queue                                 */
/* Return value: does not return anything                                     */
/******************************************************************************/
void QDequeue(queue_t *queue);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the data of the element at the front of the queue    */
/* Arguments:    queue - pointer to the queue                                 */
/* Return value: returns a void pointer to the data                           */
/******************************************************************************/
void *QPeek(const queue_t *queue);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  returns the number of elements in the queue                  */
/* Arguments:    queue - pointer to the queue                                 */
/* Return value: returns the number of elements                               */
/******************************************************************************/
size_t QCount(const queue_t *queue);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the queue is empty                                 */
/* Arguments:    queue - pointer to the queue                                 */
/* Return value: returns 1 if empty, 0 otherwise                              */
/******************************************************************************/
int QIsEmpty(const queue_t *queue);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  appends the source queue to the end of the destination queue */
/* Arguments:    dest - pointer to the destination queue                      */
/*               src - pointer to the source queue                            */
/* Return value: does not return anything                                     */
/* Note:         the source queue becomes empty after this operation          */
/******************************************************************************/
void QAppend(queue_t *dest, queue_t *src);

#endif /*QUEUE_H*/
