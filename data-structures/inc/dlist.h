/*
Owner: Uri Naor
Date: Feb 19, 2024

Doubly Linked List

Description:
A doubly linked list (DLL) is a type of a linked list in which each node 
contains a pointer to the previous node as well as 
the next node of the linked list.
*/

#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

typedef struct dlist dlist_t;
typedef struct dlist_node *dlist_iter_t;

/******************************************************************************/
/* Description:  match is a function that checks if there is a match          */
/* between 2 values of a certain data type. We pass it as a     */
/* callback to DListFind and DListMultiFind.                    */
/* Arguments:    data - void ptr to a data we're looking for.                 */
/* param - void ptr of a parameter we check match with.         */
/* Return value: returns an int, 1 if there is a match 0 if not               */
/******************************************************************************/
typedef int (*match_func_t)(const void *data, void *param);

/******************************************************************************/
/* Description:  action is a function that performs an action on the          */
/* iterators with a specific data, it is passed as a callback   */
/* to the DListForEach function.                                */
/* Arguments:    data - void ptr to the data of the desired node              */
/* param - void ptr of the parameter of the desired change      */
/* Return value: returns an int, 1 if action successful 0 if not              */
/******************************************************************************/
typedef int (*action_func_t)(void *data, void *param);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates an empty Doubly Linked List                          */
/* Arguments:    no arguments                                                 */
/* Return value: returns a pointer to the newly created list                  */
/******************************************************************************/
dlist_t *DListCreate();

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  removes the list from memory                                 */
/* Arguments:    list - pointer to the list to be removed                     */
/* Return value: does not return anything                                     */
/* Note:         removing from empty list will result in undefined behavior   */
/******************************************************************************/
void DListDestroy(dlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the head of the list                      */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns a pointer to the head of the list                    */
/******************************************************************************/
dlist_iter_t DListBegin(const dlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the tail of the list                      */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns a pointer to the tail of the list                    */
/******************************************************************************/
dlist_iter_t DListEnd(const dlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the next node in the list                 */
/* Arguments:    iter - pointer to the node of interest                       */
/* Return value: returns a pointer to next node                               */
/******************************************************************************/
dlist_iter_t DListNext(dlist_iter_t iter);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the previous node in the list             */
/* Arguments:    iter - pointer to the node of interest                       */
/* Return value: returns a pointer to previous node                           */
/******************************************************************************/
dlist_iter_t DListPrev(dlist_iter_t iter);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Compares between two iterators                               */
/* Arguments:    iter1/iter2 - iterators to be compared                       */
/* Return value: returns 1 if iterators point to the same node,               */
/* or zero otherwise                                            */
/******************************************************************************/
int DListIsIterSame(dlist_iter_t iter1, dlist_iter_t iter2);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  inserts a new node to the list                               */
/* Arguments:    where - location in the list where the new node is to be     */ 
/* inserted.                                                    */
/* data - pointer to the data to be inserted in the node        */
/* Return value: returns a pointer to the newly inserted node                 */
/******************************************************************************/
dlist_iter_t DListInsert(dlist_iter_t where, void* data);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes a given node from the list                           */
/* Arguments:    to_remove - a pointer to the node to be removed              */
/* Return value: returns a pointer to the next node                           */
/* Note:         after removing a node, previous nodes held by user in        */
/* iterators may be corrupted.                                  */
/******************************************************************************/
dlist_iter_t DListRemove(dlist_iter_t to_remove);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  extracts the data from the node                              */
/* Arguments:    iter - the pointer to the node of interest                   */
/* Return value: returns a pointer to the data in the node                    */
/******************************************************************************/
void *DListGetData(dlist_iter_t iter);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  sets the data in the given node to specified data            */
/* Arguments:    iter - pointer to the given node                             */
/* data - pointer to the data to be set                         */
/* Return value: does not return anything                                     */
/******************************************************************************/
void DListSetData(dlist_iter_t iter, void *data);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  counts the number of nodes in the list                       */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns the number of nodes in the list as size_t            */
/******************************************************************************/
size_t DListCount(const dlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the given list is empty                            */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns 1 if list is empty, 0 otherwise                      */
/******************************************************************************/
int DListIsEmpty(const dlist_t *list);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  finds the node that holds the input data within a given      */
/* search range in the list                                     */ 
/* Arguments:    from - iterator that points to the first node in the         */
/* search range                                                 */
/* to - iterator that points to the last node in the            */
/* search range                                                 */ 
/* is_match - function that checks if the two iterators match   */
/* param - pointer to the data to be searched for               */
/* Return value: if param is found within the range, it returns the iterator  */
/* that points to the node where it was found. Otherwise,       */
/* returns iterator that points to the last node in the range   */
/******************************************************************************/
dlist_iter_t DListFind(dlist_iter_t from,
                    dlist_iter_t to,
                    match_func_t is_match,
                    void *param);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  executes a given function on each of the nodes in the list   */
/* Arguments:    from - iterator that points to the first node in the list    */
/* to - iterator that points to the last node in the list       */
/* action - pointer to a function to be executed on each node   */
/* param - some parameter to be used as an argument for the     */
/* action function                                              */
/* Return value: if the function returns successfully from all calls, return  */
/* 0. Otherwise return 1.                                       */
/******************************************************************************/
int DListForEach(dlist_iter_t from,
                dlist_iter_t to,
                action_func_t action,
                void *param);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  moves a given range of elements in one list                  */
/* into a different location in the same list,                  */
/* or in a location in another list                             */
/* Arguments:    from - the beginning of the range                            */
/* to - the end of the range that is excluded                   */
/* from the move                                           */
/* where - the position in the target list before               */
/* which the elements will be inserted                  */
/* Return value: None                                                         */
/* Note:         inserting invalid from, to and where arguments               */
/* will lead to undefined behavior                              */
/******************************************************************************/
void DListSplice(dlist_iter_t from, 
                dlist_iter_t to,
                dlist_iter_t where);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  finds all nodes that hold the input data within a given      */
/* search range in the list                                     */ 
/* Arguments:    from - iterator that points to the first node in the         */
/* search range                                                 */
/* to - iterator that points to the last node in the            */
/* search range                                                 */ 
/* is_match - function that checks if the two iterators match   */
/* param - pointer to the data to be searched for               */
/* found_elements - a list ptr that points to list of found     */
/* elements                                    */
/* Return value: returns an integer status code (e.g., 0 for success,         */
/* non-zero for failure).                                       */
/******************************************************************************/
int DListMultiFind(dlist_iter_t from,
                dlist_iter_t to,
                match_func_t is_match,
                void *param, dlist_t *found_elements);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  inserts an element at the end of the list                    */
/* Arguments:    list - pointer to the list                                   */
/* data - data to be inserted into the list                     */  
/* Return value: returns an iterator to the element inserted                  */
/******************************************************************************/
dlist_iter_t DListPushBack(dlist_t *list, void *data);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes an element from the back of the list                 */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns void pointer to the data in the                      */
/* removed element                                              */  
/* Note:         popping from empty list causes undefined behavior            */
/******************************************************************************/
void *DListPopBack(dlist_t *list);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  inserts an element to the front of the list                  */
/* Arguments:    list - pointer to the list                                   */
/* data - data to be inserted into the list                     */
/* Return value: returns an iterator to the newly inserted node               */
/******************************************************************************/
dlist_iter_t DListPushFront(dlist_t *list, void *data);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes an element from the front of the list                */
/* Arguments:    list - pointer to the list                                   */
/* Return value: returns void pointer to the data from the                    */
/* removed element                                              */
/* Note:         popping from empty list causes undefined behavior            */
/******************************************************************************/
void *DListPopFront(dlist_t *list);

#endif /* DLIST_H */
