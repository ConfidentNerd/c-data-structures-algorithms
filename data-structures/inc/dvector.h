/*
Owner: Uri Naor
Date: Feb 13, 2024

Dynamic Vector

Description:
A dynamic vector (also known as a dynamic array) is a random access, 
variable-size list data structure that allows elements to be added or removed. 
It automatically grows or shrinks its capacity based on the number of elements 
it contains to optimize memory usage and performance.
*/

#ifndef DVECTOR_H
#define DVECTOR_H

#include <stddef.h> /* size_t */

typedef struct dvector dvector_t;

/* Growth/Shrink policy:                                                     */
/* - If size >= 75% of capacity: Grow (capacity * 2)                         */
/* - If size <= 25% of capacity: Shrink (capacity / 2)                       */

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates an empty Dynamic Vector                              */
/* Arguments:    capacity - initial number of elements the vector can hold    */
/*               element_size - size of each element in bytes                 */
/* Return value: returns a pointer to the newly created vector                */
/******************************************************************************/
dvector_t *DVectorCreate(size_t capacity , size_t element_size);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes the vector from memory                               */
/* Arguments:    dvector - pointer to the vector to be removed                */
/* Return value: does not return anything                                     */
/******************************************************************************/
void DvectorDestroy(dvector_t *dvector);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns a pointer to the element at the specified index      */
/* Arguments:    dvector - pointer to the vector                              */
/*               idx - index of the element                                   */
/* Return value: returns a void pointer to the element                        */
/* Note:         providing an index out of bounds will lead to undefined      */
/*               behavior.                                                    */
/******************************************************************************/
void *DvectorGetAccessToElement(const dvector_t *dvector, size_t idx);

/* Complexity: Amortized O(1)                                                */
/******************************************************************************/
/* Description:  adds a new element to the end of the vector                  */
/* Arguments:    dvector - pointer to the vector                              */
/*               data - pointer to the data to be added                       */
/* Return value: returns 0 on success, or -1 on failure                       */
/******************************************************************************/
int DvectorPushBack(dvector_t *dvector, const void *data);

/* Complexity: Amortized O(1)                                                */
/******************************************************************************/
/* Description:  removes the last element from the vector                     */
/* Arguments:    dvector - pointer to the vector                              */
/* Return value: does not return anything                                     */
/* Note:         popping from an empty vector will result in undefined        */
/*               behavior.                                                    */
/******************************************************************************/
void DvectorPopBack(dvector_t *dvector);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the number of elements currently in the vector       */
/* Arguments:    dvector - pointer to the vector                              */
/* Return value: returns the number of elements                               */
/******************************************************************************/
size_t DvectorSize(const dvector_t *dvector); 

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the current capacity of the vector                   */
/* Arguments:    dvector - pointer to the vector                              */
/* Return value: returns the maximum number of elements before next resize    */
/******************************************************************************/
size_t DvectorCapacity(const dvector_t *dvector);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  manually changes the capacity of the vector                  */
/* Arguments:    dvector - pointer to the vector                              */
/*               capacity - the new desired capacity                          */
/* Return value: returns 0 on success, or -1 on failure                       */
/******************************************************************************/
int DvectorReserve(dvector_t *dvector, size_t capacity);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  manually shrinks the capacity to half its current size       */
/* Arguments:    dvector - pointer to the vector                              */
/* Return value: returns 0 on success, or -1 on failure                       */
/* Note:         will fail if size is larger than 25% of current capacity     */
/******************************************************************************/
int DvectorShrink(dvector_t *dvector);

#endif /*DVECTOR_H*/
