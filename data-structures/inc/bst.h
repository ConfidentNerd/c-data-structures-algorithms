/*
Owner: Uri Naor
Date: Mar 12, 2024

Binary Search Tree

Description:
A Binary Search Tree (BST) is a node-based binary tree data structure which has 
the following properties:
- The left subtree of a node contains only nodes with keys lesser than 
  the node's key.
- The right subtree of a node contains only nodes with keys greater than 
  the node's key.
- The left and right subtree each must also be a binary search tree.
*/

#ifndef BST_H
#define BST_H

#include <stddef.h> /* size_t */

typedef int (*cmp_func_t)(const void *data, const void *param);
typedef int (*action_func_t)(void *data, void *param);

typedef struct node *bst_iter_t;
typedef struct tree bst_t;

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates an empty Binary Search Tree                          */
/* Arguments:    cmp_func - function to define how to sort the tree           */
/* Return value: returns a pointer to the newly created tree                  */
/******************************************************************************/
bst_t *BSTCreate(cmp_func_t cmp_func);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  removes the tree from memory                                 */
/* Arguments:    bst - pointer to the tree to be removed                      */
/* Return value: does not return anything                                     */
/******************************************************************************/
void BSTDestroy(bst_t *bst);

/* Complexity: O(log n) (WC O(n))                                            */
/******************************************************************************/
/* Description:  returns pointer to the first node in the tree (smallest)     */
/* Arguments:    bst - pointer to the tree                                    */
/* Return value: returns a pointer to the first node in the tree              */
/******************************************************************************/
bst_iter_t BSTBegin(const bst_t *bst);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns pointer to the end of the tree (dummy node)          */
/* Arguments:    bst - pointer to the tree                                    */
/* Return value: returns a pointer to the end of the tree                     */
/******************************************************************************/
bst_iter_t BSTEnd(const bst_t *bst);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  returns pointer to the next node in the tree                 */
/* Arguments:    iter - pointer to the node of interest                       */
/* Return value: returns a pointer to next node                               */
/******************************************************************************/
bst_iter_t BSTNext(bst_iter_t iter);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  returns pointer to the previous node in the tree             */
/* Arguments:    iter - pointer to the node of interest                       */
/* Return value: returns a pointer to previous node                           */
/******************************************************************************/
bst_iter_t BSTPrev(bst_iter_t iter);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  finds the node that holds the input data                     */
/* Arguments:    bst - pointer to the tree                                    */
/*               params - pointer to the data to be searched for              */
/* Return value: returns the iterator that points to the node where it was    */
/*               found. Otherwise, returns BSTEnd(bst)                        */
/******************************************************************************/
bst_iter_t BSTFind(const bst_t *bst, void *params);

/* Complexity: O(log n) (WC O(n))                                            */
/******************************************************************************/
/* Description:  inserts a new node to the tree in the correct spot           */
/* Arguments:    bst - pointer to the tree                                    */
/*               data - pointer to the data to be inserted in the node        */
/* Return value: returns a pointer to the newly inserted node                 */
/******************************************************************************/
bst_iter_t BSTInsert(bst_t *bst, void *data);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  removes a given node from the tree                           */
/* Arguments:    iter - a pointer to the node to be removed                   */
/* Return value: does not return anything                                     */
/******************************************************************************/
void BSTRemove(bst_iter_t iter);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  counts the number of nodes in the tree                       */
/* Arguments:    bst - pointer to the tree                                    */
/* Return value: returns the number of nodes in the tree as size_t            */
/******************************************************************************/
size_t BSTSize(const bst_t *bst);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the given tree is empty                            */
/* Arguments:    bst - pointer to the tree                                    */
/* Return value: returns 1 if tree is empty, 0 otherwise                      */
/******************************************************************************/
int BSTIsEmpty(const bst_t *bst);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  extracts the data from the node                              */
/* Arguments:    iter - the pointer to the node of interest                   */
/* Return value: returns a pointer to the data in the node                    */
/******************************************************************************/
void *BSTGetData(bst_iter_t iter);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Compares between two iterators                               */
/* Arguments:    iter1/iter2 - iterators to be compared                       */
/* Return value: returns 1 if iterators point to the same node,               */
/*               or zero otherwise                                            */
/******************************************************************************/
int BSTIsIterSame(bst_iter_t iter1, bst_iter_t iter2);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  executes a given function on each of the nodes in the tree   */
/* Arguments:    from - iterator that points to the first node in the range   */
/*               to - iterator that points to the end of the range            */
/*               action_func - pointer to a function to be executed           */
/*               params - parameter to be used as an argument for the action  */
/* Return value: if the function returns successfully from all calls, return  */
/*               0. Otherwise returns the status code of the failed action    */
/******************************************************************************/
int BSTForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func, void *params);

#endif /* BST_H */
