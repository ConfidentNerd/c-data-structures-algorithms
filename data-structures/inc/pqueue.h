/*
Owner: Uri Naor
Date: Mar 2, 2024

Priority Queue (Sorted List Implementation)

Description:
A priority queue is an abstract data type which is like a regular queue or 
stack data structure, but where additionally each element has a "priority" 
associated with it. In a priority queue, an element with high priority is 
served before an element with low priority. This implementation uses 
a sorted linked list as the underlying container.
*/

#ifndef P_Q
#define P_Q

#include <stddef.h> /* size_t */

typedef struct pq pq_t;
typedef int (*cmp_func_t)(const void *data, const void *param);
typedef int (*match_func_t)(const void *data, void *param);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates a new empty priority queue                          */
/* Arguments:    cmp_func - function to define the priority order             */
/* Return value: returns a pointer to the newly created priority queue        */
/******************************************************************************/
pq_t *PQCreate(cmp_func_t cmp_func);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  destroys the priority queue and frees all associated memory  */
/* Arguments:    pq - pointer to the priority queue                           */
/* Return value: does not return anything                                     */
/******************************************************************************/
void PQDestroy(pq_t *pq);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  inserts data into the priority queue according to priority   */
/* Arguments:    pq - pointer to the priority queue                           */
/*               data - pointer to the data to be inserted                    */
/* Return value: returns 0 on success, non-zero on failure                    */
/******************************************************************************/
int PQEnqueue(pq_t *pq, void *data);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes and returns the element with the highest priority     */
/* Arguments:    pq - pointer to the priority queue                           */
/* Return value: returns pointer to the removed element, or NULL if empty     */
/******************************************************************************/
void *PQDequeue(pq_t *pq);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the element with the highest priority without removal*/
/* Arguments:    pq - pointer to the priority queue                           */
/* Return value: returns pointer to the element, or NULL if empty             */
/******************************************************************************/
void *PQPeek(const pq_t *pq);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the priority queue is empty                        */
/* Arguments:    pq - pointer to the priority queue                           */
/* Return value: returns 1 if empty, 0 otherwise                              */
/******************************************************************************/
int PQIsEmpty(const pq_t *pq);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  returns the number of elements in the priority queue         */
/* Arguments:    pq - pointer to the priority queue                           */
/* Return value: returns the number of elements                               */
/******************************************************************************/
size_t PQCount(const pq_t *pq);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  removes the first element matching the given criteria        */
/* Arguments:    pq - pointer to the priority queue                           */
/*               match_func - function to define matching criteria            */
/*               param - parameter for the match function                     */
/* Return value: returns pointer to the removed element, or NULL if no match  */
/* Note:         param can be NULL.                                           */
/******************************************************************************/
void *PQErase(pq_t *pq, match_func_t match_func, void *param);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  removes all elements from the priority queue                 */
/* Arguments:    pq - pointer to the priority queue                           */
/* Return value: does not return anything                                     */
/******************************************************************************/
void PQClear(pq_t *pq);

#endif /* P_Q */
