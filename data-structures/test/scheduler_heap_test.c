/*
Owner: Uri Naor
Date: Mar 6, 2024
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scheduler_heap.h"

#define GOOD "\033[1;30m\033[102m"
#define BAD "\033[1;37m\033[41m"
#define REG "\033[1;0m""\n"
#define HEAD "\033[1;30m\033[47m"
#define SUB_HEAD "\033[1;30m\033[43m"

#define UNUSED(x) (void)(x)

int was_errors = 0;

char string[100] = {0};

scheduler_t *SchedCreateTEST(void);

ilrd_uid_t SchedAddTaskTEST(scheduler_t *sched, 
                        size_t interval, 
                        action_func_t action, 
                        void *action_param, 
                        cleanup_func_t cleanup_func, 
                        void *cleanup_param);

size_t SchedClearTEST(void);

size_t SchedRemoveTaskTEST(void);

size_t ParamCleanupTEST(void);

/***********************************************************/

void PsuedoClear(void *action_param)
{
	UNUSED(action_param);
}

int PrintS(void *params)
{
	UNUSED(params);
	
	printf("S\n");
	strcat((char *) params, "S");
	
	return SUCCESS;
}

int PrintU(void *params)

{
	UNUSED(params);
	
	printf("U\n");
    strcat((char *) params, "U");
	
	return SUCCESS;
}

int PrintC(void *params)
{
	UNUSED(params);
	
	printf("C\n");
    strcat((char *) params, "C");
	
	return SUCCESS;
}

int PrintE(void *params)
{
	UNUSED(params);
	
	printf("E\n");
    strcat((char *) params, "E");
	
	return SUCCESS;
}

int RepFunc(void *params)
{
	UNUSED(params);
	
	printf("[Repeat]\n");
    strcat((char *) params, "[Repeat]");

	return REPEAT;
}

int StopFunc(void *scheduler)
{
    SchedStop((scheduler_t *) scheduler);
	return STOP;
}

int GhostFunc(void *params)
{
	UNUSED(params);
	
	printf(BAD"you shouldn't see me. removal error."REG);
	strcat((char *) params, "*");
	
	was_errors = 1;
	
	return SUCCESS;
}

int SilentFunc(void *params)
{
	UNUSED(params);
	return SUCCESS;
}

int SilentStopFunc(void *scheduler)
{
	SchedStop((scheduler_t *) scheduler);
	return STOP;
}

int SilentRepFunc(void *params)
{
	UNUSED(params);
	return REPEAT;
}

int GoodJob_1(void *params)
{
	UNUSED(params);
	printf("░██████╗░░█████╗░░█████╗░██████╗░  ░░░░░██╗░█████╗░██████╗░██╗\n");
	return SUCCESS;
}

int GoodJob_2(void *params)
{
	UNUSED(params);
	printf("██╔════╝░██╔══██╗██╔══██╗██╔══██╗  ░░░░░██║██╔══██╗██╔══██╗██║\n");
	return SUCCESS;
}

int GoodJob_3(void *params)
{
	UNUSED(params);
	printf("██║░░██╗░██║░░██║██║░░██║██║░░██║  ░░░░░██║██║░░██║██████╦╝██║\n");
	return SUCCESS;
}

int GoodJob_4(void *params)
{
	UNUSED(params);
	printf("██║░░╚██╗██║░░██║██║░░██║██║░░██║  ██╗░░██║██║░░██║██╔══██╗╚═╝\n");
	return SUCCESS;
}


int GoodJob_5(void *params)
{
	UNUSED(params);
	printf("╚██████╔╝╚█████╔╝╚█████╔╝██████╔╝  ╚█████╔╝╚█████╔╝██████╦╝██╗\n");
	return SUCCESS;
}

int GoodJob_6(void *params)
{
	UNUSED(params);
	printf("░╚═════╝░░╚════╝░░╚════╝░╚═════╝░  ░╚════╝░░╚════╝░╚═════╝░╚═╝\n\n");
	return SUCCESS;
}

int main()
{
	int some_var = 1;
	
	ilrd_uid_t uid1 = {0};
	ilrd_uid_t uid2 = {0};
	ilrd_uid_t uid3 = {0};
	ilrd_uid_t uid4 = {0};
	ilrd_uid_t uid5 = {0};
	ilrd_uid_t uid6 = {0};
	ilrd_uid_t uid7 = {0};
	ilrd_uid_t uid8 = {0};
	ilrd_uid_t uid9 = {0};
	ilrd_uid_t uid10 = {0};
	ilrd_uid_t uid11 = {0};
	ilrd_uid_t uid12 = {0};
		
	scheduler_t *scheduler = NULL;


	UNUSED(uid1);UNUSED(uid2);UNUSED(uid3);UNUSED(uid4);UNUSED(uid5);UNUSED(uid6);
	UNUSED(uid7);UNUSED(uid8);UNUSED(uid9);UNUSED(uid10);UNUSED(uid11);UNUSED(uid12);
	
	printf("\n"HEAD"     Flow Test (utilizes most of the functions)      "REG);
	printf    (HEAD"    (without repeating and stop-signaling tasks)     "REG);

	printf(SUB_HEAD"                 creating a new list                 "REG);
	scheduler = SchedCreateTEST();
	
	printf(SUB_HEAD"                     adding tasks                    "REG);
	
	uid2 = SchedAddTaskTEST(scheduler, 9, PrintC, string, PsuedoClear, NULL);
	
	uid4 = SchedAddTaskTEST(scheduler, 5, PrintS, string, PsuedoClear, NULL);
	
	uid5 = SchedAddTaskTEST(scheduler, 6, PrintU, string, PsuedoClear, NULL);
	
	uid6 = SchedAddTaskTEST(scheduler, 7, PrintC, string, PsuedoClear, NULL);
	
	uid7 = SchedAddTaskTEST(scheduler, 2, GhostFunc, string, PsuedoClear, NULL);
	
	uid11 = SchedAddTaskTEST(scheduler, 14, PrintS, string, PsuedoClear, NULL);

	uid8 = SchedAddTaskTEST(scheduler, 16, GhostFunc, string, PsuedoClear, NULL);
	
	uid9 = SchedAddTaskTEST(scheduler, 11, PrintE, string, PsuedoClear, NULL);
	
	uid10 = SchedAddTaskTEST(scheduler, 12, PrintS, string, PsuedoClear, NULL);

	printf(SUB_HEAD"      removing tasks (if failed - you'll know)       "REG"\n");
	if (ERROR == SchedRemoveTask(scheduler, uid7))
	{
		printf(BAD"FAILURE"REG);
	}

	if (ERROR == SchedRemoveTask(scheduler, uid8))
	{
		printf(BAD"FAILURE"REG);
	}
	
	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (0 == SchedIsEmpty(scheduler) && 7 == SchedSize(scheduler))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		printf("%lu\n", SchedSize(scheduler));
		was_errors = 1;
	}
	
	printf(SUB_HEAD"                  running scheduler                  "REG);
	printf(SUB_HEAD"          should print \"SUCCESS\" vertically          "REG);
	SchedRun(scheduler);
	
	printf(SUB_HEAD"                veryfing print output                "REG);
	if (0 == strcmp("SUCCESS", string))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	
	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (1 == SchedIsEmpty(scheduler) && 0 == SchedSize(scheduler))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	

	
	printf("\n"HEAD"      Flow Test (utilizes most of the functions)     "REG);
	printf    (HEAD"  (with a repeating task and a stop-signaling task)  "REG);
	
	printf(SUB_HEAD"                    adding tasks                     "REG);
	
	uid1 = SchedAddTaskTEST(scheduler, 20, StopFunc, scheduler, PsuedoClear, NULL);
	
	uid2 = SchedAddTaskTEST(scheduler, 9, PrintC, string, PsuedoClear, NULL);
	
	uid3 = SchedAddTaskTEST(scheduler, 6, RepFunc, string, PsuedoClear, NULL);
	
	uid4 = SchedAddTaskTEST(scheduler, 5, PrintS, string, PsuedoClear, NULL);
	
	uid11 = SchedAddTaskTEST(scheduler, 13, PrintS, string, PsuedoClear, NULL);
	
	uid5 = SchedAddTaskTEST(scheduler, 6, PrintU, string, PsuedoClear, NULL);
	
	uid6 = SchedAddTaskTEST(scheduler, 7, PrintC, string, PsuedoClear, NULL);
	
	uid10 = SchedAddTaskTEST(scheduler, 10, PrintE, string, PsuedoClear, NULL);
	
	uid7 = SchedAddTaskTEST(scheduler, 2, GhostFunc, string, PsuedoClear, NULL);

	uid8 = SchedAddTaskTEST(scheduler, 15, GhostFunc, string, PsuedoClear, NULL);
	
	uid12 = SchedAddTaskTEST(scheduler, 11, PrintS, string, PsuedoClear, NULL);

	printf(SUB_HEAD"       removing tasks (if failed - you'll know)      "REG"\n");
	SchedRemoveTask(scheduler, uid7);
	SchedRemoveTask(scheduler, uid8);
	
	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (0 == SchedIsEmpty(scheduler) && 9 == SchedSize(scheduler))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	
	printf(SUB_HEAD"                  running scheduler                  "REG);
	printf(SUB_HEAD"    should print the following string vertically:    "REG);
	printf(SUB_HEAD"           S[Repeat]UCCES[Repeat]S[Repeat]           "REG);
	
	SchedRun(scheduler);

	printf(SUB_HEAD"                veryfing print output                "REG);
	if (0 == strcmp("SUCCESSS[Repeat]UCCES[Repeat]S[Repeat]", string))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}

	printf(SUB_HEAD"                    veryfing size                    "REG);
	if (0 == SchedIsEmpty(scheduler) && 1 == SchedSize(scheduler))
	{
		printf(GOOD"SUCCESS"REG);
	}
	else
	{
		printf(BAD"FAILURE"REG);
		was_errors = 1;
	}
	
	
	was_errors += SchedRemoveTaskTEST();
	
	was_errors += SchedClearTEST();

    was_errors += ParamCleanupTEST();
	
	if (0 == was_errors)
	{
		SchedClear(scheduler);
		
		SchedAddTask(scheduler, 1, GoodJob_1, &some_var, PsuedoClear, NULL);
		SchedAddTask(scheduler, 2, GoodJob_2, &some_var, PsuedoClear, NULL);
		SchedAddTask(scheduler, 3, GoodJob_3, &some_var, PsuedoClear, NULL);
		SchedAddTask(scheduler, 4, GoodJob_4, &some_var, PsuedoClear, NULL);
		SchedAddTask(scheduler, 5, GoodJob_5, &some_var, PsuedoClear, NULL);
		SchedAddTask(scheduler, 6, GoodJob_6, &some_var, PsuedoClear, NULL);

		SchedRun(scheduler);
	}
	
	SchedDestroy(scheduler);
	
	return 0;
}

scheduler_t *SchedCreateTEST(void)
{
	size_t error_count = 0;
	
	scheduler_t *scheduler = SchedCreate();
	
	if (NULL == scheduler)
	{
		printf(BAD"allocation failed"REG);
		++error_count;
	}

	
	if (0 == SchedIsEmpty(scheduler))
	{
		printf(BAD"new scheduler isn't empty"REG);
		++error_count;
	}
	
	if (0 != SchedSize(scheduler))
	{
		printf(BAD"new scheduler size isn't 0"REG);
		++error_count;
	}
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}

	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	return scheduler;
}


ilrd_uid_t SchedAddTaskTEST(scheduler_t *sched, 
                        size_t interval, 
                        action_func_t action, 
                        void *action_param, 
                        cleanup_func_t cleanup_func, 
                        void *cleanup_param)
{
	size_t error_count = 0;
	
	size_t old_scheduler_size = SchedSize(sched);
	
	ilrd_uid_t uid = {0};	

	uid = SchedAddTask(sched, interval, action, action_param, 
					   cleanup_func, cleanup_param);
	
	if (1 == UIDIsEqual(uid, bad_uid))
	{
		printf(BAD"uid == bad_uid\n");
		return uid;
	}
	
	if (1 == SchedIsEmpty(sched))
	{
		printf(BAD"scheduler is empty after adding test"REG);
		++error_count;
	}
	
	if (old_scheduler_size + 1 != SchedSize(sched))
	{
		printf(BAD"scheduler size is incorrect"REG);
		++error_count;
	}
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}
	
	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	return uid;
}


size_t SchedClearTEST(void)
{
	size_t error_count = 0;
	
	scheduler_t *scheduler = SchedCreate();
	
	int some_var = 1;
	
	ilrd_uid_t first_uid = {0};
	ilrd_uid_t mid_uid = {0};
	ilrd_uid_t last_uid = {0};
	
	printf("\n"HEAD"           Edge cases for 'SchedClear'           "REG);

	/* trying to clear a brand new scheduler */
	SchedClear(scheduler);
	
	SchedAddTask(scheduler, 16, StopFunc, scheduler, PsuedoClear, NULL);
	SchedAddTask(scheduler, 9, PrintE, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 6, RepFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 5, PrintS, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 7, PrintU, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 7, PrintC, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 2, GhostFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 12, GhostFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 11, PrintE, &some_var, PsuedoClear, NULL);


	if (9 != SchedSize(scheduler))
	{
		printf(BAD"error inserting tasks"REG);
		++error_count;
	}
	
	SchedClear(scheduler);


	if (0 == SchedIsEmpty(scheduler))
	{
		printf(BAD"scheduler isn't empty after Clear"REG);
		++error_count;
	}
	
	if (0 != SchedSize(scheduler))
	{
		printf(BAD"scheduler size isn't 0 after Clear"REG);
		++error_count;
	}

	if (0 == error_count)
	{	
		/* trying to clear an empty scheduler */
		SchedClear(scheduler);
	}
	
	if (0 == SchedIsEmpty(scheduler))
	{
		printf(BAD"scheduler isn't empty after Clear"REG);
		++error_count;
	}
	
	if (0 != SchedSize(scheduler))
	{
		printf(BAD"scheduler size isn't 0 Clear"REG);
		++error_count;
	}
	
	SchedAddTask(scheduler, 4, SilentStopFunc, scheduler, PsuedoClear, NULL);
	SchedAddTask(scheduler, 3, SilentFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 1, SilentRepFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 5, SilentFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 2, SilentFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 1, SilentFunc, &some_var, PsuedoClear, NULL);
	
	first_uid = SchedAddTask(scheduler, 0, GhostFunc, &some_var, PsuedoClear, NULL);
	mid_uid = SchedAddTask(scheduler, 3, GhostFunc, &some_var, PsuedoClear, NULL);
	last_uid = SchedAddTask(scheduler, 6, GhostFunc, &some_var, PsuedoClear, NULL);
	
	SchedAddTask(scheduler, 5, SilentFunc, &some_var, PsuedoClear, NULL);

	SchedRemoveTask(scheduler, first_uid);
	SchedRemoveTask(scheduler, mid_uid);
	SchedRemoveTask(scheduler, last_uid);
	
	if (7 != SchedSize(scheduler))
	{
		printf(BAD"error inserting tasks"REG);
		++error_count;
	}
	
	SchedRun(scheduler);
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG"\n");
	}
	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	SchedDestroy(scheduler);

    return error_count;
}


size_t SchedRemoveTaskTEST(void)
{
	size_t error_count = 0;
	
	
	size_t old_scheduler_size = 0;
	
	scheduler_t *scheduler = SchedCreate();
	
	ilrd_uid_t first_uid = {0};
	ilrd_uid_t mid_uid = {0};
	ilrd_uid_t last_uid = {0};

	ilrd_uid_t dummy_uid = UIDGenerate();
	ilrd_uid_t blank_uid = {0};
	
	int some_var = 1;
	
	printf("\n"HEAD"        Edge cases for 'SchedRemoveTask'         "REG);


	SchedAddTask(scheduler, 4, SilentStopFunc, scheduler, PsuedoClear, NULL);
	SchedAddTask(scheduler, 3, SilentFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 1, SilentRepFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 5, SilentFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 2, SilentFunc, &some_var, PsuedoClear, NULL);
	SchedAddTask(scheduler, 1, SilentFunc, &some_var, PsuedoClear, NULL);
	
	first_uid = SchedAddTask(scheduler, 0, GhostFunc, &some_var, PsuedoClear, NULL);
	mid_uid = SchedAddTask(scheduler, 3, GhostFunc, &some_var, PsuedoClear, NULL);
	last_uid = SchedAddTask(scheduler, 6, GhostFunc, &some_var, PsuedoClear, NULL);
	
	SchedAddTask(scheduler, 5, SilentFunc, &some_var, PsuedoClear, NULL);
	

	if (10 != SchedSize(scheduler))
	{
		printf(BAD"error inserting tasks"REG);
		++error_count;
	}
	
	old_scheduler_size = SchedSize(scheduler);
	SchedRemoveTask(scheduler, mid_uid);

	if (old_scheduler_size != SchedSize(scheduler) + 1)
	{
		printf(BAD"error removing tasks from the middle"REG);
		++error_count;
	}
	
	old_scheduler_size = SchedSize(scheduler);
	SchedRemoveTask(scheduler, last_uid);
	
	if (old_scheduler_size != SchedSize(scheduler) + 1)
	{
		printf(BAD"error removing the last task"REG);
		++error_count;
	}
	
	old_scheduler_size = SchedSize(scheduler);
	SchedRemoveTask(scheduler, first_uid);
	
	if (old_scheduler_size != SchedSize(scheduler) + 1)
	{
		printf(BAD"error removing the first task"REG);
		++error_count;
	}
	
	old_scheduler_size = SchedSize(scheduler);
	
	/* attempting to remove nonexisting tasks */
	SchedRemoveTask(scheduler, first_uid);
	SchedRemoveTask(scheduler, mid_uid);
	SchedRemoveTask(scheduler, last_uid);
	SchedRemoveTask(scheduler, dummy_uid);
	SchedRemoveTask(scheduler, bad_uid);
	SchedRemoveTask(scheduler, blank_uid);
	
	
	if (old_scheduler_size != SchedSize(scheduler))
	{
		printf(BAD"the size changed after attempting to remove nonexisting tasks"REG);
		++error_count;
	}
	
	/* trying to run the scheduler after several removals and removal-attempts */
	SchedRun(scheduler);
	
	if (0 == error_count)
	{
		printf(GOOD"SUCCESS"REG);
	}
	else 
	{
		printf(BAD"FAILURE. %lu errors was found"REG, error_count);
		was_errors = 1;
	}
	
	SchedDestroy(scheduler);

    return error_count;
}

typedef struct to_clean
{
    int x;
    int y;
}to_clean_t;

void CleanChangeParam(void *params)
{
    ((to_clean_t *)params)->x = 0;
}

size_t ParamCleanupTEST(void)
{
    size_t error_count = 0;
    scheduler_t *scheduler = SchedCreate();
    
    to_clean_t first_struct = {5, 5};
    to_clean_t mid_struct = {2, 2};
    to_clean_t last_struct = {1, 1};

    ilrd_uid_t first_uid = {0};
    ilrd_uid_t mid_uid = {0};
    ilrd_uid_t last_uid = {0};

    UNUSED(mid_uid);
    UNUSED(last_uid);

    
    printf("\n"HEAD"              Clean Func Functionality              "REG);

    first_uid = SchedAddTask(scheduler, 0, GhostFunc, &first_struct, CleanChangeParam, &first_struct);
    mid_uid = SchedAddTask(scheduler, 3, SilentStopFunc, scheduler, CleanChangeParam, &mid_struct);
    last_uid = SchedAddTask(scheduler, 6, GhostFunc, &last_struct, CleanChangeParam, &last_struct);

    SchedRemoveTask(scheduler, first_uid);
    SchedRun(scheduler);
    SchedClear(scheduler);

    if (first_struct.x)
    {
        printf(BAD"clean_func at remove didn't use action params or acted at all"REG);
        ++error_count;
    }

    if (!first_struct.y)
    {
        printf(BAD"clean_func at remove didn't use clean params or acted at all"REG);
        ++error_count;
    }

    if (mid_struct.x)
    {
        printf(BAD"clean_func at run didn't use action params or acted at all"REG);
        ++error_count;
    }

    if (!mid_struct.y)
    {
        printf(BAD"clean_func at run didn't use clean params or acted at all"REG);
        ++error_count;
    }

    if (last_struct.x)
    {
        printf(BAD"clean_func at clear didn't use action params or acted at all"REG);
        ++error_count;
    }

    if (!last_struct.y)
    {
        printf(BAD"clean_func at clear didn't use clean params or acted at all"REG);
        ++error_count;
    }




    if (0 == error_count)
    {
        printf(GOOD"SUCCESS\n"REG);
    }
    else 
    {
        printf(BAD"FAILURE. %lu errors were found\n"REG, error_count);
        was_errors = 1;
    }

    SchedDestroy(scheduler);

    return error_count;
}
