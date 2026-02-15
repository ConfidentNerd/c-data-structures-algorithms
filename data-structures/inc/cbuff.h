/*
Owner: Uri Naor
Date: Feb 19, 2024

Circular Buffer

Description:
A circular buffer (also known as a ring buffer or cyclic buffer) is a data 
structure that uses a single, fixed-size buffer as if it were connected 
end-to-end. This implementation is byte-oriented and efficient for buffering 
data streams.
*/

#ifndef CBUFF_H
#define CBUFF_H

#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */

typedef struct cbuff cbuff_t;

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates an empty circular buffer                             */
/* Arguments:    capacity - maximum number of bytes the buffer can hold       */
/* Return value: returns a pointer to the newly created circular buffer       */
/******************************************************************************/
cbuff_t *CBuffCreate(size_t capacity);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  removes the circular buffer from memory                      */
/* Arguments:    buffer - pointer to the circular buffer                      */
/* Return value: does not return anything                                     */
/******************************************************************************/
void CBuffDestroy(cbuff_t *buffer);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  reads up to 'count' bytes from the buffer into 'dest'        */
/* Arguments:    buffer - pointer to the circular buffer                      */
/*               dest - pointer to the destination memory                     */
/*               count - maximum number of bytes to read                      */
/* Return value: returns the number of bytes read, or -1 if the buffer is empty */
/******************************************************************************/
ssize_t CBuffRead(cbuff_t *buffer, void *dest, size_t count);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  writes up to 'count' bytes from 'src' into the buffer        */
/* Arguments:    buffer - pointer to the circular buffer                      */
/*               src - pointer to the source memory                           */
/*               count - maximum number of bytes to write                     */
/* Return value: returns the number of bytes written, or -1 if the buffer is full */
/******************************************************************************/
ssize_t CBuffWrite(cbuff_t *buffer, const void *src, size_t count);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the buffer is empty                                */
/* Arguments:    buffer - pointer to the circular buffer                      */
/* Return value: returns 1 if empty, 0 otherwise                              */
/******************************************************************************/
int CBuffIsEmpty(const cbuff_t *buffer);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the number of bytes currently in the buffer          */
/* Arguments:    buffer - pointer to the circular buffer                      */
/* Return value: returns the number of bytes                                  */
/******************************************************************************/
size_t CBuffSize(const cbuff_t *buffer);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the number of free bytes remaining in the buffer     */
/* Arguments:    buffer - pointer to the circular buffer                      */
/* Return value: returns the number of free bytes                             */
/******************************************************************************/
size_t CBuffFreeSpace(const cbuff_t *buffer);

#endif /* CBUFF_H */
