/*
Owner: Uri Naor
Date: Feb 10, 2024

Bit Array

Description:
A Bit Array (also known as a bitset, bit map, or bit vector) is a space-efficient 
data structure that stores a collection of bits. This implementation uses 
a size_t (64 bits on 64-bit systems) to represent the array.
*/

#ifndef BITARR_H
#define BITARR_H

#include <stddef.h> /* size_t */

typedef size_t bitarr_t;

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Sets all bits in the bit array to 1                          */
/* Arguments:    arr - the bit array                                          */
/* Return value: returns the modified bit array                               */
/******************************************************************************/
bitarr_t BitArrSetAll(bitarr_t arr);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Resets all bits in the bit array to 0                        */
/* Arguments:    arr - the bit array                                          */
/* Return value: returns the modified bit array                               */
/******************************************************************************/
bitarr_t BitArrResetAll(bitarr_t arr);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Sets the bit at the given index to 1                         */
/* Arguments:    arr - the bit array                                          */
/*               idx - the index of the bit to set (0 to 63)                  */
/* Return value: returns the modified bit array                               */
/******************************************************************************/
bitarr_t BitArrSetOn(bitarr_t arr, size_t idx);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Sets the bit at the given index to 0                         */
/* Arguments:    arr - the bit array                                          */
/*               idx - the index of the bit to set (0 to 63)                  */
/* Return value: returns the modified bit array                               */
/******************************************************************************/
bitarr_t BitArrSetOff(bitarr_t arr, size_t idx);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Sets the bit at the given index to the specified value       */
/* Arguments:    arr - the bit array                                          */
/*               idx - the index of the bit to set (0 to 63)                  */
/*               value - 1 to set on, 0 to set off                            */
/* Return value: returns the modified bit array                               */
/******************************************************************************/
bitarr_t BitArrSetBit(bitarr_t arr, size_t idx, int value);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Returns the value of the bit at the given index              */
/* Arguments:    arr - the bit array                                          */
/*               idx - the index of the bit to get (0 to 63)                  */
/* Return value: returns 1 if bit is on, 0 if off                             */
/******************************************************************************/
int BitArrGetBit(bitarr_t arr, size_t idx);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Flips the value of the bit at the given index                */
/* Arguments:    arr - the bit array                                          */
/*               idx - the index of the bit to flip (0 to 63)                 */
/* Return value: returns the modified bit array                               */
/******************************************************************************/
bitarr_t BitArrFlipBit(bitarr_t arr, size_t idx);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  Reverses the order of the bits in the bit array              */
/* Arguments:    arr - the bit array                                          */
/* Return value: returns the mirrored bit array                               */
/******************************************************************************/
bitarr_t BitArrMirror(bitarr_t arr);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Rotates the bit array to the right by n positions            */
/* Arguments:    arr - the bit array                                          */
/*               n - the number of positions to rotate                        */
/* Return value: returns the rotated bit array                                */
/******************************************************************************/
bitarr_t BitArrRotateRight(bitarr_t arr, size_t n);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  Rotates the bit array to the left by n positions             */
/* Arguments:    arr - the bit array                                          */
/*               n - the number of positions to rotate                        */
/* Return value: returns the rotated bit array                                */
/******************************************************************************/
bitarr_t BitArrRotateLeft(bitarr_t arr, size_t n);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  Counts the number of bits that are set to 1                  */
/* Arguments:    arr - the bit array                                          */
/* Return value: returns the number of bits set to 1                          */
/******************************************************************************/
size_t BitArrCountOn(bitarr_t arr);

/* Complexity: O(log n)                                                      */
/******************************************************************************/
/* Description:  Counts the number of bits that are set to 0                  */
/* Arguments:    arr - the bit array                                          */
/* Return value: returns the number of bits set to 0                          */
/******************************************************************************/
size_t BitArrCountOff(bitarr_t arr);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  Converts the bit array to a string representation            */
/* Arguments:    arr - the bit array                                          */
/*               buffer - pointer to a buffer to store the string             */
/*               (must be at least 65 bytes)                                  */
/* Return value: returns a pointer to the buffer                              */
/******************************************************************************/
char *BitArrToString(bitarr_t arr, char *buffer);

/* Complexity: O(1) (with LUT)                                               */
/******************************************************************************/
/* Description:  Reverses the order of bits in the bit array using a LUT      */
/* Arguments:    arr - the bit array                                          */
/* Return value: returns the mirrored bit array                               */
/******************************************************************************/
bitarr_t BitArrMirrorLut(bitarr_t arr);

/* Complexity: O(1) (with LUT)                                               */
/******************************************************************************/
/* Description:  Counts set bits in the bit array using a LUT                 */
/* Arguments:    arr - the bit array                                          */
/* Return value: returns the number of bits set to 1                          */
/******************************************************************************/
size_t BitArrCountOnLut(bitarr_t arr);

#endif /* BITARR_H */
