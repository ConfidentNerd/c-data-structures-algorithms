/*
Owner: Uri Naor
Date: Mar 24, 2024

AVL Tree

Description:
An AVL tree (named after inventors Adelson-Velsky and Landis) is a 
self-balancing binary search tree. In an AVL tree, the heights of the two 
child subtrees of any node differ by at most one; if at any time they differ 
by more than one, rebalancing is done to restore this property.
*/

#ifndef OL_155_6_AVL
#define OL_155_6_AVL

#include <stddef.h> /* size_t */

typedef enum traverse
{
    PRE_ORDER = 0,
    IN_ORDER = 1,
    POST_ORDER = 2
} traversal_order_t;

typedef struct tree avl_t;
typedef int (*cmp_func_t)(const void *avl_data, const void *user_data);
typedef int (*action_func_t)(void *avl_data, void *params);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates a new empty AVL Tree                                 */
/* Arguments:    cmp_func - comparison function for sorting elements          */
/* Return value: returns a pointer to the newly created AVL tree              */
/******************************************************************************/
avl_t *AVLCreate(cmp_func_t cmp_func);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  destroys the AVL tree and frees all associated memory        */
/* Arguments:    avl - pointer to the AVL tree                                */
/* Return value: does not return anything                                     */
/******************************************************************************/
void AVLDestroy(avl_t *avl);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  inserts a new element into the AVL tree                      */
/* Arguments:    avl - pointer to the AVL tree                                */
/*               data - data to be inserted                                   */
/* Return value: returns 0 for success, 1 for failure                         */
/******************************************************************************/
int AVLInsert(avl_t *avl, void *data);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  removes the specified element from the AVL tree              */
/* Arguments:    avl - pointer to the AVL tree                                */
/*               data - data to be removed                                    */
/* Return value: does not return anything                                     */
/******************************************************************************/
void AVLRemove(avl_t *avl, void *data);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  finds an element in the AVL tree matching the given data     */
/* Arguments:    avl - pointer to the AVL tree                                */
/*               data - data to search for                                    */
/* Return value: returns pointer to the found data, or NULL if not found      */
/******************************************************************************/
void *AVLFind(const avl_t *avl, const void *data);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  returns the number of elements in the AVL tree               */
/* Arguments:    avl - pointer to the AVL tree                                */
/* Return value: returns the number of elements                               */
/******************************************************************************/
size_t AVLSize(const avl_t *avl);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the AVL tree is empty                              */
/* Arguments:    avl - pointer to the AVL tree                                */
/* Return value: returns 1 if empty, 0 otherwise                              */
/******************************************************************************/
int AVLIsEmpty(const avl_t *avl);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  executes a given action function on all elements             */
/* Arguments:    avl - pointer to the AVL tree                                */
/*               action_func - function to be executed on each element        */
/*               params - parameters for the action function                  */
/*               order - traversal order (PRE_ORDER, IN_ORDER, POST_ORDER)    */
/* Return value: returns 0 if successful, non-zero if an action function      */
/*               returns an error.                                            */
/******************************************************************************/
int AVLForEach(avl_t *avl, action_func_t action_func, void *params, traversal_order_t order);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the height of the AVL tree                           */
/* Arguments:    avl - pointer to the AVL tree                                */
/* Return value: returns the height of the tree                               */
/******************************************************************************/
size_t AVLHeight(const avl_t *avl);

#endif /* OL_155_6_AVL */
