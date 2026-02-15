/*
Owner: Uri Naor
Date: Mar 20, 2024

Recursion Library

Description:
This library provides recursive implementations of common algorithmic problems
and standard string manipulation functions. It demonstrates the use of the 
call stack for state management, backtracking, and mathematical calculations.
*/

#ifndef RECURSION_HEAD
#define RECURSION_HEAD

#include "stack.h"

/******************** STRUCTS ********************/
typedef struct node
{
    void *data;
    struct node *next;
} node_t;

/******************** FORWARD DECLARATIONS ********************/

/* Complexity: Time: O(2^n) | Space: O(n) */
/******************************************************************************/
/* Description:  Calculates the nth element of the Fibonacci sequence using   */
/* naive recursion.                                             */
/* Arguments:    element_index - the 0-based index in the sequence            */
/* Return value: The integer value at the specified index.                    */
/* Note:         Space complexity is O(n) due to the depth of the call stack. */
/******************************************************************************/
int Fibonacci(int element_index);

/* Complexity: Time: O(n) | Space: O(n) */
/******************************************************************************/
/* Description:  Recursively reverses the direction of a singly linked list.  */
/* Arguments:    node - pointer to the head of the list to be flipped         */
/* Return value: A pointer to the new head of the flipped list.               */
/******************************************************************************/
node_t *Flip(node_t *node);

/* Complexity: Time: O(n^2) worst case | Space: O(n) */
/******************************************************************************/
/* Description:  Recursively sorts a stack data structure in ascending order. */
/* Uses a recursive helper to insert items in sorted order.     */
/* Arguments:    stack - pointer to the stack to be sorted                    */
/* Return value: None                                                         */
/******************************************************************************/
void SortStack(stack_t *stack);

/* Complexity: Time: O(n) | Space: O(n) */
/******************************************************************************/
/* Description:  Recursively calculates the length of a null-terminated       */
/* string, excluding the null byte itself.                      */
/* Arguments:    str - pointer to the string                                  */
/* Return value: The number of characters in the string.                      */
/******************************************************************************/
size_t Strlen(const char *str);

/* Complexity: Time: O(min(n, m)) | Space: O(min(n, m)) */
/******************************************************************************/
/* Description:  Recursively compares two strings character by character.     */
/* Arguments:    str1 - pointer to the first string                           */
/* str2 - pointer to the second string                          */
/* Return value: An integer less than, equal to, or greater than zero if      */
/* str1 is found, respectively, to be less than, to match,      */
/* or be greater than str2.                                     */
/******************************************************************************/
int Strcmp(const char *str1, const char *str2);

/* Complexity: Time: O(n) | Space: O(n) */
/******************************************************************************/
/* Description:  Recursively copies the string pointed to by src, including   */
/* the terminating null byte, to the buffer pointed to by dest. */
/* Arguments:    dest - pointer to the destination buffer                     */
/* src - pointer to the source string                           */
/* Return value: A pointer to the destination string dest.                    */
/******************************************************************************/
char *Strcpy(char *dest, const char *src);

/* Complexity: Time: O(n + m) | Space: O(m) stack space */
/******************************************************************************/
/* Description:  Recursively appends the src string to the dest string,       */
/* overwriting the terminating null byte at the end of dest,    */
/* and then adds a terminating null byte.                       */
/* Arguments:    dest - pointer to the destination string                     */
/* src - pointer to the source string                           */
/* Return value: A pointer to the resulting string dest.                      */
/******************************************************************************/
char *Strcat(char *dest, const char *src);

/* Complexity: Time: O(n * m) worst case | Space: O(n) */
/******************************************************************************/
/* Description:  Recursively finds the first occurrence of the substring      */
/* needle in the string haystack.                               */
/* Arguments:    haystack - pointer to the string to be searched              */
/* needle - pointer to the substring to search for              */
/* Return value: A pointer to the beginning of the located substring, or      */
/* NULL if the substring is not found.                          */
/******************************************************************************/
char *Strstr(const char *haystack, const char *needle);

#endif /** END RECURSION_HEAD */