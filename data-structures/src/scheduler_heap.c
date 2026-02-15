/*
Owner: Uri Naor
Date: Mar 6, 2024
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <unistd.h> /* sleep */
#include <time.h>   /* time */

#include "pqueue_heap.h" /* pq_t */
#include "scheduler_heap.h" /* scheduler_t */
#include "task.h" /* task_t */

/******************** FORWARD DECLARATIONS ********************/
static int PriorityRule(const void *data, const void *dest_data);
static int FindToRemove(const void *task, void *id);

/******************** STRUCTS ********************/
typedef struct scheduler
{
    pq_t *priority_queue;
    task_t *active;
    int stop;
} sc_t;

/******************** FUNCTIONS ********************/
scheduler_t *SchedCreate(void)
{
    scheduler_t *scheduler;
    pq_t *new_pqueue;

    scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
    if (NULL == scheduler)
    {
        return (NULL);
    }

    new_pqueue = PQCreate(PriorityRule);
    if (NULL == new_pqueue)
    {
        free(scheduler);

        return (NULL);
    }

    scheduler->priority_queue = new_pqueue;
    scheduler->stop = 1;
    scheduler->active = NULL;

    return (scheduler);
}

void SchedDestroy(scheduler_t *sched)
{
    assert(sched);

    SchedClear(sched);
    PQDestroy(sched->priority_queue);

    free(sched);
}

ilrd_uid_t SchedAddTask(scheduler_t *sched, size_t interval, 
action_func_t action, void *action_param, 
cleanup_func_t cleanup_func, void *cleanup_param)
{
    int status = 0;
    task_t *task_to_add = NULL;

    assert(sched);
    assert(action);

    task_to_add = TaskCreate(interval, action, action_param, cleanup_func, 
                            cleanup_param);
    if (NULL == task_to_add)
    {
        return (bad_uid);
    }

    status = PQEnqueue(sched->priority_queue, task_to_add);
    if (SUCCESS != status)
    {
        return (bad_uid);
    }

    return (TaskGetUID(task_to_add));
}

int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t task_id)
{
    task_t *task_to_remove = NULL;

    assert(sched);

    task_to_remove = PQErase(sched->priority_queue, FindToRemove, &task_id);
    if (NULL == task_to_remove)
    {
        return (ERROR);
    }

    TaskDestroy(task_to_remove);

    return (SUCCESS);
}

int SchedRun(scheduler_t *sched)
{
    int status = 0;

    assert(sched);

    sched->stop = 0;

    while (!SchedIsEmpty(sched) && (sched->stop) == 0)
    {
        while (time(NULL) < TaskGetTimeToRun(PQPeek(sched->priority_queue)))
        {
            sleep(1);
        }

        sched->active = (task_t *)PQDequeue(sched->priority_queue);

        status = TaskRun(sched->active);

        if (REPEAT == status)
        {
            TaskUpdateTimeToRun(sched->active);
        
            if (SUCCESS != PQEnqueue(sched->priority_queue, sched->active))
            {
                TaskDestroy(sched->active);
                return (ERROR);
            }
        }
        else
        {
            TaskDestroy(sched->active);
        }

        if (STOP == status || ERROR == status)
        {
            SchedStop(sched);            
            return (status);
        }
    }

    return (SUCCESS);
}

int SchedStop(scheduler_t *sched)
{
    assert(sched);

    sched->stop = 1;

    return (SUCCESS);
}

void SchedClear(scheduler_t *sched)
{
    task_t *task_to_free;

    assert(sched);

    while (!SchedIsEmpty(sched))
    {
        task_to_free = (task_t *)PQDequeue(sched->priority_queue);
        TaskDestroy(task_to_free);
    }
}

size_t SchedSize(const scheduler_t *sched)
{
    assert(sched);

    return (PQCount(sched->priority_queue));
}

int SchedIsEmpty(const scheduler_t *sched)
{
    assert(sched);
    
    return (PQIsEmpty(sched->priority_queue));
}

/******************** HELPER FUNCTIONS ********************/
static int PriorityRule(const void *data, const void *param)
{
    return (TaskGetTimeToRun(data) - TaskGetTimeToRun(param));
}

static int FindToRemove(const void *task, void *id)
{
    return (UIDIsEqual((TaskGetUID((task_t *)task)), *(ilrd_uid_t *)id));
}
