/*
Owner: Uri Naor
Date: Feb 22, 2024

Sorted Linked List

Description:
A sorted linked list is a collection of items where each item holds 
a relative position that is based upon some underlying characteristic of 
the item. This implementation uses a doubly linked list as the underlying 
container and maintains the sorted order during insertion.
*/

#ifndef SRTLIST_H
#define SRTLIST_H

#include <stddef.h> /* size_t */
#include "dlist.h" /* dlist_iter_t */

typedef struct srtlist srtlist_t;

typedef struct srtlist_iter
{
    dlist_iter_t iter;
    
    #ifndef NDEBUG 
    const srtlist_t *list;
    #endif 
} srtlist_iter_t;

typedef int (*cmp_func_t)(const void *data, const void *param);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates an empty Sorted Linked List                          */
/* Arguments:    cmp_func - function to define how to sort the list           */
/* Return value: returns a pointer to the newly created list                  */
/******************************************************************************/
srtlist_t *SrtListCreate(cmp_func_t cmp_func);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  removes the list from memory                                 */
/* Arguments:    list - pointer to the list to be removed                     */
/* Return value: does not return anything                                     */
/* Note:         removing from empty list will result in undefined behavior   */
/******************************************************************************/
void SrtListDestroy(srtlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the head of the list                      */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns a pointer to the head of the list                    */
/******************************************************************************/
srtlist_iter_t SrtListBegin(const srtlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the tail of the list                      */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns a pointer to the tail of the list                    */
/******************************************************************************/
srtlist_iter_t SrtListEnd(const srtlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the next node in the list                 */
/* Arguments:    iter - pointer to the node of interest                       */
/* Return value: returns a pointer to next node                               */
/******************************************************************************/
srtlist_iter_t SrtListNext(srtlist_iter_t iter);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the previous node in the list             */
/* Arguments:    iter - pointer to the node of interest                       */
/* Return value: returns a pointer to previous node                           */
/******************************************************************************/
srtlist_iter_t SrtListPrev(srtlist_iter_t iter);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Compares between two iterators                               */
/* Arguments:    iter1/iter2 - iterators to be compared                       */
/* Return value: returns 1 if iterators point to the same node,               */
/*               or zero otherwise                                            */
/******************************************************************************/
int SrtListIsIterSame(srtlist_iter_t iter1, srtlist_iter_t iter2);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  inserts a new node to the list in the correct sorted spot    */
/* Arguments:    list - pointer to the list                                   */
/*               data - pointer to the data to be inserted in the node        */
/* Return value: returns a pointer to the newly inserted node                 */
/* Note:         if there are elements with the same value, it inserts after  */
/******************************************************************************/
srtlist_iter_t SrtListInsert(srtlist_t *list, void* data);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes a given node from the list                           */
/* Arguments:    to_remove - a pointer to the node to be removed              */
/* Return value: returns a pointer to the next node                           */
/******************************************************************************/
srtlist_iter_t SrtListRemove(srtlist_iter_t to_remove);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  extracts the data from the node                              */
/* Arguments:    iter - the pointer to the node of interest                   */
/* Return value: returns a pointer to the data in the node                    */
/******************************************************************************/
void *SrtListGetData(srtlist_iter_t iter);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  counts the number of nodes in the list                       */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns the number of nodes in the list as size_t            */
/******************************************************************************/
size_t SrtListCount(const srtlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the given list is empty                            */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns 1 if list is empty, 0 otherwise                      */
/******************************************************************************/
int SrtListIsEmpty(const srtlist_t *list);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  finds the node with given data based on sort criteria        */
/* Arguments:    list - pointer to the list                                   */
/*               from - iterator that points to the start of range            */
/*               to - iterator that points to the end of range                */
/*               data - data to be searched for                               */
/* Return value: returns the iterator to the found node, or 'to' if not found */
/* Note:         undefined behavior if from and to are from different lists   */
/******************************************************************************/
srtlist_iter_t SrtListFind(srtlist_t *list, srtlist_iter_t from,
					srtlist_iter_t to,
					void *data);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  finds the node that holds the input data with match function */
/* Arguments:    from - iterator that points to the start of range            */
/*               to - iterator that points to the end of range                */ 
/*               is_match - function that checks for a match                  */
/*               param - pointer to the data to be searched for               */
/* Return value: returns the iterator to the found node, or 'to' if not found */
/* Note:         undefined behavior if from and to are from different lists   */
/******************************************************************************/
srtlist_iter_t SrtListFindIf(srtlist_iter_t from,              
					srtlist_iter_t to,
					match_func_t is_match,
					void *param);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  executes a given function on each of the nodes in the range  */
/* Arguments:    from - iterator that points to the start of range            */
/*               to - iterator that points to the end of range                */
/*               action - pointer to a function to be executed on each node   */
/*               param - parameter to be used as an argument for the action   */
/* Return value: returns 0 if all calls successful, non-zero otherwise        */
/* Note:         undefined behavior if from and to are from different lists   */
/******************************************************************************/
int SrtListForEach(srtlist_iter_t from,                     
				srtlist_iter_t to,
				action_func_t action,
				void *param);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes an element from the back of the list                 */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns void pointer to the data in the removed element      */
/* Note:         popping from empty list causes undefined behavior            */
/******************************************************************************/
void *SrtListPopBack(srtlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes an element from the front of the list                */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns void pointer to the data from the removed element    */
/* Note:         popping from empty list causes undefined behavior            */
/******************************************************************************/
void *SrtListPopFront(srtlist_t *list);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  merges two sorted lists into the destination list            */
/* Arguments:    dest - pointer to the destination list                       */
/*               src - pointer to the source list                             */
/* Return value: does not return anything                                     */
/* Note:         undefined behavior if compare functions differ or src empty  */
/******************************************************************************/
void SrtListMerge(srtlist_t *dest, srtlist_t *src);        

#endif /* SRTLIST_H */
