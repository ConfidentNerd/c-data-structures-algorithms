/*
Owner: Uri Naor
Date: Mar 30, 2024

Heap

Description:
A heap is a specialized tree-based data structure that satisfies the heap 
property: in a min-heap, for any given node C, if P is a parent node of C, 
then the key (the value) of P is less than or equal to the key of C. 
This implementation provides a generic binary heap.
*/

#ifndef OL_155_6_HEAP
#define OL_155_6_HEAP

#include <stddef.h> /* size_t */

typedef struct heap heap_t;
typedef int(*heap_cmp_func_t)(const void *data, const void *params);
typedef int(*heap_match_func_t)(const void *data, const void *params);

typedef enum status
{
    SUCCESS = 0,
    FAILURE
} status_t;

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates a new empty heap                                     */
/* Arguments:    cmp_func - function to define the heap priority              */
/* Return value: returns a pointer to the newly created heap                  */
/******************************************************************************/
heap_t *HeapCreate(heap_cmp_func_t cmp_func);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  destroys the heap and frees all associated memory            */
/* Arguments:    heap - pointer to the heap                                   */
/* Return value: does not return anything                                     */
/******************************************************************************/
void HeapDestroy(heap_t *heap);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  inserts a new element into the heap                          */
/* Arguments:    heap - pointer to the heap                                   */
/*               data - pointer to the data to be inserted                    */
/* Return value: returns SUCCESS (0) if successful, FAILURE otherwise         */
/******************************************************************************/
status_t HeapPush(heap_t *heap, void *data);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  removes the top element from the heap                        */
/* Arguments:    heap - pointer to the heap                                   */
/* Return value: does not return anything                                     */
/* Note:         popping from an empty heap results in undefined behavior.    */
/******************************************************************************/
void HeapPop(heap_t *heap);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the top element of the heap without removing it      */
/* Arguments:    heap - pointer to the heap                                   */
/* Return value: returns a pointer to the top element, or NULL if empty       */
/******************************************************************************/
void *HeapPeek(const heap_t *heap);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  removes the first element matching the condition             */
/* Arguments:    heap - pointer to the heap                                   */
/*               match_func - function to define matching condition           */
/*               params - parameters for the match function                   */
/* Return value: returns pointer to the removed data, or NULL if not found    */
/******************************************************************************/
void *HeapRemove(heap_t *heap, heap_match_func_t match_func, const void *params);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the heap is empty                                  */
/* Arguments:    heap - pointer to the heap                                   */
/* Return value: returns 1 if empty, 0 otherwise                              */
/******************************************************************************/
int HeapIsEmpty(const heap_t *heap);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the number of elements in the heap                   */
/* Arguments:    heap - pointer to the heap                                   */
/* Return value: returns the number of elements                               */
/******************************************************************************/
size_t HeapSize(const heap_t *heap);

#endif /* OL_155_6_HEAP */
