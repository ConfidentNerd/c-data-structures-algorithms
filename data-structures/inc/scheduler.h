/*
Owner: Uri Naor
Date: Mar 6, 2024

Scheduler (Priority Queue Implementation)

Description:
This library provides functionality for scheduling tasks to be executed 
at specified intervals. It uses a priority queue (implemented with a sorted 
linked list) to manage and execute tasks based on their scheduled time.
*/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stddef.h> /* size_t */

#include "uid.h" /* ilrd_uid_t */

typedef struct scheduler scheduler_t;

typedef int (*action_func_t)(void* param);
typedef void (*cleanup_func_t)(void* param);

enum
{
    ERROR = -1,
    SUCCESS,
    STOP,
    REPEAT
};

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates a new scheduler                                      */
/* Arguments:    none                                                         */
/* Return value: returns a pointer to the newly created scheduler, or NULL    */
/******************************************************************************/
scheduler_t *SchedCreate(void);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  destroys a scheduler and frees all associated memory        */
/* Arguments:    sched - pointer to the scheduler                             */
/* Return value: does not return anything                                     */
/******************************************************************************/
void SchedDestroy(scheduler_t *sched);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  adds a new task to the scheduler                             */
/* Arguments:    sched - pointer to the scheduler                             */
/*               interval - interval for execution in seconds                 */
/*               action - action function to execute                          */
/*               action_param - parameters for the action function            */
/*               cleanup_func - cleanup function after task removal           */
/*               cleanup_param - parameters for the cleanup function          */
/* Return value: returns UID of the added task, or bad_uid on failure         */
/******************************************************************************/
ilrd_uid_t SchedAddTask(scheduler_t *sched, size_t interval, 
                        action_func_t action, void *action_param, 
                        cleanup_func_t cleanup_func, void *cleanup_param);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  removes a task from the scheduler                            */
/* Arguments:    sched - pointer to the scheduler                             */
/*               task_id - unique identifier of the task                      */
/* Return value: returns SUCCESS (0) if successful, ERROR otherwise            */
/******************************************************************************/
int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t task_id);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  runs the scheduler, executing tasks at their scheduled time  */
/* Arguments:    sched - pointer to the scheduler                             */
/* Return value: returns SUCCESS (0) if stopped normally, or ERROR/STOP codes */
/******************************************************************************/
int SchedRun(scheduler_t *sched);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  stops the scheduler after the current task finishes          */
/* Arguments:    sched - pointer to the scheduler                             */
/* Return value: returns SUCCESS (0)                                          */
/******************************************************************************/
int SchedStop(scheduler_t *sched);

/* Complexity: O(n)                                                          */
/******************************************************************************/
/* Description:  clears all tasks from the scheduler                          */
/* Arguments:    sched - pointer to the scheduler                             */
/* Return value: does not return anything                                     */
/******************************************************************************/
void SchedClear(scheduler_t *sched);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the number of tasks currently in the scheduler       */
/* Arguments:    sched - pointer to the scheduler                             */
/* Return value: returns the number of tasks                                  */
/******************************************************************************/
size_t SchedSize(const scheduler_t *sched);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if the scheduler is empty                              */
/* Arguments:    sched - pointer to the scheduler                             */
/* Return value: returns 1 if empty, 0 otherwise                              */
/******************************************************************************/
int SchedIsEmpty(const scheduler_t *sched);  

#endif /*SCHEDULER_H*/
