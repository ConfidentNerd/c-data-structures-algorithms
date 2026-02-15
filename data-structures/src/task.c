/*
Owner: Uri Naor
Date: Mar 3, 2024
*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <time.h>   /* time */

#include "task.h" /* task_t */

/******************** STRUCTS ********************/
struct task
{
	ilrd_uid_t id;
	task_action_func_t action;
	task_clean_func_t clean_func;
	void *action_params;
	void *cleanup_params;
	size_t interval;
	time_t exec_time;
};

/******************** FUNCTIONS ********************/
task_t *TaskCreate(size_t interval, task_action_func_t action, 
void* action_params, task_clean_func_t cleanup , void *cleanup_params)
{
    task_t *task;

    assert(action);

    task = (task_t *)malloc(sizeof(task_t));
    if (NULL == task)
    {
        return (NULL);
    }

    task->id = UIDGenerate();
    if(UIDIsEqual(task->id, bad_uid))
    {
        free(task);
        return (NULL);
    }

    task->exec_time = time(NULL) + (time_t)interval;
    task->interval = interval;
    task->action = action;
    task->action_params = action_params;
    task->clean_func = cleanup;
    task->cleanup_params = cleanup_params;
    
    return (task);
}

void TaskDestroy(task_t *task)
{
    assert(task);

    if(NULL != task->clean_func)
    {
        task->clean_func(task->cleanup_params);
    }

    free(task);
}

ilrd_uid_t TaskGetUID(const task_t *task)
{
    assert(task);


    return (task->id);
}

int TaskRun(task_t *task)
{
    int status = 0;
	
    assert(task);

    status = task->action(task->action_params);

    if (0 > status && NULL != task->clean_func)
    {
        task->clean_func(task->cleanup_params);
    }

    return status;
}

int TaskIsSame(const task_t *task1, const task_t *task2)
{
    assert(task1);
    assert(task2);

    return (UIDIsEqual(task1->id, task2->id));
}

time_t TaskGetTimeToRun(const task_t *task)
{
    assert(task);

    return (task->exec_time);
}

void TaskUpdateTimeToRun(task_t *task)
{
    assert(task);

    task->exec_time = time(NULL) + (time_t)task->interval;
}
