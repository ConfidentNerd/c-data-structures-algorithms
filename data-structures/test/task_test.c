/*
Owner: Uri Naor
Date: Mar 3, 2024
*/

#include "task.h" /* task_t */

#include <stdio.h> /* printf */
#include <time.h> /* sleep */

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

enum STATUS
{
	FAILED = -1,
	SUCCEEDED = 0
};

static int TestFlow1();
static int TestFlow2();

static int ActionFunc(void *param);
static void CleanFunc(void *param);

int main()
{
	printf("\n");
	if (SUCCEEDED != TestFlow1())
	{
		printf("Test Flow 1 Task:%s\n",FAIL);
		return 0;
	}
	if (SUCCEEDED != TestFlow2())
	{
		printf("Test Flow 2 Task:%s\n",FAIL);
		return 0;
	}
    printf("You Passed All Test: %s\n",PASS);
	printf("\n");
	
    return 0;
}

static int TestFlow1()
{
    task_t *tasks_arr[3];
    size_t tasks_interval[3] = {1,5,7};
    char *action_params[3] = {"first", "seconds", "third"};
    size_t i = 0, size = sizeof(tasks_arr) / sizeof(tasks_arr[0]); 

    for (i = 0; i < size; i++)
    {
        tasks_arr[i] = TaskCreate(tasks_interval[i], ActionFunc, 
                                  action_params[i], NULL, NULL);
        if (NULL == tasks_arr[i])
        {
            printf("%s to create a task\n", FAIL);
            return FAILED;
        }
        TaskRun(tasks_arr[i]);
    }

    if (1 != TaskIsSame(tasks_arr[0], tasks_arr[0]))
	{
		printf("TaskIsSame, Same task:%s\n",FAIL);
		return FAILED;
	}

    if (0 != TaskIsSame(tasks_arr[2],tasks_arr[1]))
	{
		printf("TaskIsSame, Different task:%s\n",FAIL);
		return FAILED;
	}

    if (time(NULL) + 7 != (long int)TaskGetTimeToRun(tasks_arr[2]))
	{
		printf("TaskGetTimeToRun:%s\n",FAIL);
		return FAILED;
	}
    sleep(3);
    TaskUpdateTimeToRun(tasks_arr[1]);
    if (time(NULL) + 5 != (long int)TaskGetTimeToRun(tasks_arr[1]))
	{
		printf("TaskUpdateTimeToRun:%s\n",FAIL);
		return FAILED;
	}

    for (i = 0; i < size; i++)
    {
        TaskDestroy(tasks_arr[i]);
    }

    return SUCCEEDED;
}

static int TestFlow2()
{
    return SUCCEEDED;
}

static int ActionFunc(void *param)
{
    printf("%s\n", (char *)param);

    return 0;    
}

