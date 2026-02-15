/*
Owner: Uri Naor
Date: Feb 29, 2024

Unique Identifier (UID)

Description:
This library provides a globally unique identifier structure, consisting of 
a counter, a process ID (PID), and a timestamp. It ensures uniqueness across 
multiple processes and over time.
*/

#ifndef ILRD_UID_H
#define ILRD_UID_H

#include <stddef.h> /* size_t */
#include <sys/types.h> /* pid_t */
#include <time.h> /* time_t */

typedef struct ilrd_uid
{
    size_t counter;
    pid_t pid;
    time_t time;
} ilrd_uid_t;

extern const ilrd_uid_t bad_uid;

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  generates a new unique identifier                            */
/* Arguments:    none                                                         */
/* Return value: returns a new ilrd_uid_t structure                           */
/* Note:         if timestamp generation fails, returns bad_uid               */
/******************************************************************************/
ilrd_uid_t UIDGenerate(void);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  compares two UIDs for equality                               */
/* Arguments:    one/other - UIDs to be compared                              */
/* Return value: returns 1 if UIDs are equal, 0 otherwise                     */
/******************************************************************************/
int UIDIsEqual(ilrd_uid_t one, ilrd_uid_t other);

#endif /*ILRD_UID_H*/
