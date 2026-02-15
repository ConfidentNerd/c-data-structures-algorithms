/*
Owner: Uri Naor
Date: Feb 7, 2024

Stack

Description:
A stack is a linear data structure that follows the Last In, First Out (LIFO) 
principle. This implementation provides a fixed-capacity stack that stores 
elements of a uniform size.
*/

#ifndef STACK_H
#define STACK_H

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates a new fixed-capacity stack                           */
/* Arguments:    capacity - maximum number of elements the stack can hold     */
/*               element_size - size of each element in bytes                 */
/* Return value: returns a pointer to the newly created stack                 */
/******************************************************************************/
stack_t *StackCreate(size_t capacity, size_t element_size);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes the stack from memory                                */
/* Arguments:    stack - pointer to the stack to be removed                   */
/* Return value: does not return anything                                     */
/******************************************************************************/
void StackDestroy(stack_t *stack);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  adds a new element to the top of the stack                   */
/* Arguments:    stack - pointer to the stack                                 */
/*               element - pointer to the data to be added                    */
/* Return value: does not return anything                                     */
/* Note:         pushing to a full stack will result in an error message      */
/*               and the operation will be ignored.                           */
/******************************************************************************/
void StackPush(stack_t *stack, void *element);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes the top element from the stack                       */
/* Arguments:    stack - pointer to the stack                                 */
/* Return value: does not return anything                                     */
/* Note:         popping from an empty stack is ignored.                      */
/******************************************************************************/
void StackPop(stack_t *stack);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns a pointer to the top element without removing it     */
/* Arguments:    stack - pointer to the stack                                 */
/* Return value: returns a void pointer to the top element, or NULL if empty  */
/******************************************************************************/
void *StackPeek(const stack_t *stack);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the stack is empty                                 */
/* Arguments:    stack - pointer to the stack                                 */
/* Return value: returns 1 if empty, 0 otherwise                              */
/******************************************************************************/
int StackIsEmpty(const stack_t *stack);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the maximum capacity of the stack                    */
/* Arguments:    stack - pointer to the stack                                 */
/* Return value: returns the capacity                                         */
/******************************************************************************/
size_t StackCapacity(const stack_t *stack);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the number of elements currently in the stack        */
/* Arguments:    stack - pointer to the stack                                 */
/* Return value: returns the current size                                     */
/******************************************************************************/
size_t StackSize(const stack_t *stack);

#endif /* STACK_H */
