/*
Owner: Uri Naor
Date: Apr 2, 2024
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /*abs*/
#include "knight_tour.h"

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */


static int TestFlow();
static int RunTest(unsigned char *path);
static void PrintPath(unsigned char *path);

int main()
{
    if (TestFlow() == 0)
    {
        printf("all tests %s \n",PASS);
        return 0;
    }

    return (0);
}

static int TestFlow()
{
    unsigned char path[64] = {0};
    int status = 0;

    KnightTour(0 , path,900,0);
    status = RunTest(path);
	
    KnightTour(20 , path,900,1);
    status = RunTest(path);

    KnightTour(50 , path,900,1);
    status = RunTest(path);

    KnightTour(63 , path,900,1);
    status = RunTest(path);

    KnightTour(0 , path,900,1);
    status = RunTest(path);
    
    return status;
}

static int RunTest(unsigned char *path)
{
    int is_visited[64] = {0}; 
    size_t i = 0 ;
    int x = 0;
    int y = 0;
    int x2 = 0;
    int y2 = 0;
    int dy = 0 , dx = 0;
    
    for (i = 0; i < 64; ++i)
    {
        if (is_visited[(int)path[i]] || path[i] > 64)
        {
            printf("%s your knight tour visited the same place twice \n", FAIL);
            printf("or there is invalid path in your knight tour \n");
            return 1;
        }
        else
        {
            is_visited[(int)path[i]] = 1;
        }
    }

    for (i = 1; i < 64 ; ++i)
    {
        x = path[i - 1] / 8 ;
        y = path[i - 1] % 8;
        x2 = path[i] / 8;
        y2 = path[i] % 8;
        dx = abs(x2 - x);
        dy = abs(y2 - y);

        if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1)))
        {
            printf("%s your knight moves are not right \n" ,FAIL);
            printf("Invalid move from (%d, %d) to (%d, %d)\n", x, y, x2, y2);
            return 1;
        }
    }

    PrintPath(path);

    return 0;
}

static void PrintPath(unsigned char *path)
{
    int i = 0, j = 0, k = 0;
    int arr[8][8] = {0};

    for (k = 0; k < 64; ++k)
    {
        i = path[k] / 8;
        j = path[k] % 8;
        
        arr[i][j] = k;
    }

    printf("\n\n");
    
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            printf ("%02d   ", arr[i][j]);
        }

        printf("\n\n");
    }
}
