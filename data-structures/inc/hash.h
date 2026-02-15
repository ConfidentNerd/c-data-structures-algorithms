/*
Owner: Uri Naor
Date: Mar 26, 2024

Hash Table

Description:
A hash table is a data structure that implements an associative array abstract 
data type, a structure that can map keys to values. It uses a hash function 
to compute an index into an array of buckets or slots, from which the desired 
value can be found.
*/

#ifndef HASH_H
#define HASH_H

#include <stddef.h> /* size_t */

typedef struct hash hash_t;

typedef enum status
{
    SUCCESS = 0,
    FAIL
} status_t;

/******************************************************************************/
/* Description:  hash_cmp_func_t function is used to compare                  */
/* two values in the hash table.                                */
/* Arguments:    value - A pointer to the value to be compared.               */
/* params - A pointer to parameters to be compared against.     */
/* Return value: An integer value indicating the result of the comparison:    */
/* - A negative value if value is less than params.             */
/* - Zero if value is equal to params.                          */
/* - A positive value if value is greater than params.          */
/******************************************************************************/
typedef int(*hash_cmp_func_t)(const void *value, const void *params);

/******************************************************************************/
/* Description:  hash_action_func_t function is used to apply an action to    */
/* elements within the hash table.                              */
/* Arguments:    value - A pointer to the current value in the hash table.    */
/* params - A pointer to any additional parameters required by  */
/* the action function.                                */
/* Return value: An integer value indicating the result of the action:        */
/* - A non-zero value to indicate an error.                     */
/* - Zero if the action function was applied successfully.      */
/******************************************************************************/
typedef int(*hash_action_func_t)(void *value, void *params);

/******************************************************************************/
/* Description:  The hash_func_t is the hash function used to create          */
/* an index/key from the passed value.                          */
/* Arguments:    value - A pointer to the value to be hashed.                 */
/* Return value: The hash value of the given value as a size_t type.          */
/******************************************************************************/
typedef size_t (*hash_func_t)(const void *value);


/* Complexity: O(table_size)                                                  */
/******************************************************************************/
/* Description:  Creates a new hash table.                                    */
/* Arguments:    hash_func - pointer to the hash function to be used.         */
/* cmp_func - pointer to the comparison function to be used.    */
/* table_size - The initial size of the hash table array.       */
/* Return value: A pointer to the created hash table, or NULL on failure.     */
/******************************************************************************/
hash_t *HashCreate(hash_func_t hash_func, hash_cmp_func_t cmp_func, size_t table_size);

/* Complexity: O(n + table_size)                                              */
/******************************************************************************/
/* Description:  Destroys the given hash table and frees all associated memory*/
/* Arguments:    hash - A pointer to the hash table to be destroyed.          */
/* Return value: None.                                                        */
/******************************************************************************/
void HashDestroy(hash_t *hash);

/* Complexity: O(1) average, O(n) worst                                       */
/******************************************************************************/
/* Description:  Inserts a new value into the hash table.                     */
/* Arguments:    hash - A pointer to the hash table.                          */
/* value - A pointer to the value to be inserted.               */
/* Return value: SUCCESS (0) or FAIL (1) indicating the result.               */
/******************************************************************************/
status_t HashInsert(hash_t *hash, const void *value);

/* Complexity: O(1) average, O(n) worst                                       */
/******************************************************************************/
/* Description:  Removes a value from the hash table.                         */
/* Arguments:    hash - A pointer to the hash table.                          */
/* value - A pointer to the value to be removed.                */
/* Return value: None.                                                        */
/******************************************************************************/
void HashRemove(hash_t *hash, const void *value);

/* Complexity: O(1) average, O(n) worst                                       */
/******************************************************************************/
/* Description:  Finds a value in the hash table.                             */
/* Arguments:    hash - A pointer to the hash table.                          */
/* value - A pointer to the value to be found.                  */
/* Return value: A pointer to the found value, or NULL if not present.        */
/******************************************************************************/
void *HashFind(const hash_t *hash, const void *value);

/* Complexity: O(1)                                                           */
/******************************************************************************/
/* Description:  Checks if the hash table contains any elements.              */
/* Arguments:    hash - A pointer to the hash table.                          */
/* Return value: 1 if the hash table is empty, 0 otherwise.                   */
/******************************************************************************/
int HashIsEmpty(const hash_t *hash);

/* Complexity: O(1) or O(table_size) depending on implementation              */
/******************************************************************************/
/* Description:  Returns the number of elements stored in the hash table.     */
/* Arguments:    hash - A pointer to the hash table.                          */
/* Return value: The number of elements in the hash table as size_t.          */
/******************************************************************************/
size_t HashSize(const hash_t *hash);

/* Complexity: O(n + table_size)                                              */
/******************************************************************************/
/* Description:  Applies a function to each element in the hash table.        */
/* Arguments:    hash - A pointer to the hash table.                          */
/* action - A function pointer to the action to be applied.     */
/* params - pointer to additional parameters for the action.    */
/* Return value: 0 if applied successfully to all elements, non-zero otherwise*/
/******************************************************************************/
int HashForEach(hash_t *hash, hash_action_func_t action, void *params);

/* Complexity: O(1)                                                           */
/******************************************************************************/
/* Description:  Computes the load factor of the hash table (elements/buckets)*/
/* Arguments:    hash - A pointer to the hash table.                          */
/* Return value: The load factor as a double.                                 */
/******************************************************************************/
double HashLoadFactor(const hash_t *hash);

#endif /* HASH_H */