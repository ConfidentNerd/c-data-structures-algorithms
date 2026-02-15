/*
Owner: Uri Naor
Date: Feb 16, 2024

Singly Linked List

Description:
A singly linked list is a linear data structure where each element is 
a separate object. Each node of a list is comprising of two items - 
the data and a reference to the next node.
*/

#ifndef SLIST_H
#define SLIST_H

#include <stddef.h> /* size_t */

typedef struct slist slist_t;
typedef struct node * slist_iter_t;

typedef int (*match_func_t)(const void *data, void *param);
typedef int (*action_func_t)(void *data, void *param);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates an empty singly linked list                          */
/* Arguments:    none                                                         */
/* Return value: returns a pointer to the newly created list                  */
/******************************************************************************/
slist_t *SListCreate();

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  removes the list from memory                                 */
/* Arguments:    list - pointer to the list to be removed                     */
/* Return value: does not return anything                                     */
/* Note:         removing from empty list will result in undefined behavior   */
/******************************************************************************/
void SListDestroy(slist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the head of the list                      */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns a pointer to the head of the list                    */
/******************************************************************************/
slist_iter_t SListBegin(const slist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the tail of the list                      */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns a pointer to the tail of the list                    */
/******************************************************************************/
slist_iter_t SListEnd(const slist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the next node in the list                 */
/* Arguments:    iter - pointer to the node of interest                       */
/* Return value: returns a pointer to next node                               */
/******************************************************************************/
slist_iter_t SListNext(slist_iter_t iter);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Compares between two iterators                               */
/* Arguments:    iter1/iter2 - iterators to be compared                       */
/* Return value: returns 1 if iterators point to the same node,               */
/*               or zero otherwise                                            */
/******************************************************************************/
int SListIsIterSame(slist_iter_t iter1, slist_iter_t iter2);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  inserts a new node to the list                               */
/* Arguments:    where - location in the list where the new node is to be     */ 
/*                       inserted                                             */
/*               data - pointer to the data to be inserted in the node        */
/* Return value: returns a pointer to the newly inserted node                 */
/******************************************************************************/
slist_iter_t SListInsert(slist_iter_t where, void* data);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes a given node from the list                           */
/* Arguments:    to_remove - a pointer to the node to be removed              */
/* Return value: returns a pointer to the next node                           */
/* Note:         after removing a node, previous nodes held by user in        */
/*               iterators may be corrupted.                                  */
/******************************************************************************/
slist_iter_t SListRemove(slist_iter_t to_remove);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  extracts the data from the node                              */
/* Arguments:    iter - the pointer to the node of interest                   */
/* Return value: returns a pointer to the data in the node                    */
/******************************************************************************/
void *SListGetData(slist_iter_t iter);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  sets the data in the given node to specified data            */
/* Arguments:    iter - pointer to the given node                             */
/*               data - pointer to the data to be set                         */
/* Return value: does not return anything                                     */
/******************************************************************************/
void SListSetData(slist_iter_t iter, void *data);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  counts the number of nodes in the list                       */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns the number of nodes in the list as size_t            */
/******************************************************************************/
size_t SListCount(const slist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the given list is empty                            */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns 1 if list is empty, 0 otherwise                      */
/******************************************************************************/
int SListIsEmpty(const slist_t *list);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  finds the node that holds the input data within a given      */
/*               search range in the list                                     */ 
/* Arguments:    from - iterator that points to the first node in the range   */
/*               to - iterator that points to the last node in the range      */ 
/*               is_match - function that checks if the two iterators match   */
/*               param - pointer to the data to be searched for               */
/* Return value: if param is found within the range, it returns the iterator  */
/*               that points to the node where it was found. Otherwise,       */
/*               returns iterator that points to the last node in the range   */
/******************************************************************************/
slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t is_match, void *param);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  executes a given function on each of the nodes in the list   */
/* Arguments:    from - iterator that points to the first node in the list    */
/*               to - iterator that points to the last node in the list       */
/*               action - pointer to a function to be executed on each node   */
/*               param - some parameter to be used as an argument for the     */
/*                       action function                                      */
/* Return value: if the function returns successfully from all calls, return  */
/*               0. Otherwise return 1.                                       */
/******************************************************************************/
int SListForEach(slist_iter_t from, slist_iter_t to, action_func_t action, void *param);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  appends the source list to the end of the destination list   */
/* Arguments:    dest - pointer to the destination list                       */
/*               src - pointer to the source list                             */
/* Return value: does not return anything                                     */
/* Note:         the source list becomes empty after this operation           */
/******************************************************************************/
void SListAppend(slist_t *dest, slist_t *src);

#endif /* SLIST_H */
