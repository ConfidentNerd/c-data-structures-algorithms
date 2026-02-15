/*
Owner: Uri Naor
Date: Mar 3, 2024

Task

Description:
This library provides a task structure used by the scheduler. A task 
represents an action to be executed at a specific time or interval, 
with associated cleanup functionality.
*/

#ifndef TASK_H
#define TASK_H

#include <stddef.h> /* size_t */
#include <time.h>   /* time_t */

#include "uid.h" /* ilrd_uid_t */

typedef struct task task_t;
typedef int (*task_action_func_t)(void* param);
typedef void (*task_clean_func_t)(void* param);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  creates a new task                                           */
/* Arguments:    interval - the interval at which the task should be executed */
/*               action - function to be executed                             */
/*               action_params - parameters for the action function           */
/*               cleanup - function to be executed upon task destruction      */
/*               cleanup_params - parameters for the cleanup function         */
/* Return value: returns a pointer to the newly created task                  */
/******************************************************************************/
task_t *TaskCreate(size_t interval, task_action_func_t action, void* action_params,
				task_clean_func_t cleanup, void *cleanup_params);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  destroys a task and calls its cleanup function               */
/* Arguments:    task - pointer to the task                                   */
/* Return value: does not return anything                                     */
/******************************************************************************/
void TaskDestroy(task_t *task);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the unique identifier of the task                    */
/* Arguments:    task - pointer to the task                                   */
/* Return value: returns the UID of the task                                  */
/******************************************************************************/
ilrd_uid_t TaskGetUID(const task_t *task);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  executes the task's action function                          */
/* Arguments:    task - pointer to the task                                   */
/* Return value: returns the status code from the action function             */
/******************************************************************************/
int TaskRun(task_t *task);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  checks if two tasks are the same based on their UID          */
/* Arguments:    task1/task2 - pointers to the tasks to compare               */
/* Return value: returns 1 if tasks are the same, 0 otherwise                 */
/******************************************************************************/
int TaskIsSame(const task_t *task1, const task_t *task2);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  returns the scheduled execution time for the task            */
/* Arguments:    task - pointer to the task                                   */
/* Return value: returns the execution time as time_t                         */
/******************************************************************************/
time_t TaskGetTimeToRun(const task_t *task);

/* Complexity: O(1)                                                          */
/******************************************************************************/
/* Description:  updates the task's execution time based on its interval      */
/* Arguments:    task - pointer to the task                                   */
/* Return value: does not return anything                                     */
/******************************************************************************/
void TaskUpdateTimeToRun(task_t *task);

#endif /*TASK_H*/
