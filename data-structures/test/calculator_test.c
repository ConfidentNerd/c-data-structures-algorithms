/*
Owner: Uri Naor
Date: Mar 20, 2024
*/

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

#include <stdio.h>

#include "calculator.h"

int TestFlow()
{
    double res = 0;
    calc_status_t status = SUCCESS;

    char *expression1 = "5^2^2";  /* Result = 15 status = SUCCESS */
    char *expression2 = "7 + 8";  /* Result = 15 status = SUCCESS */
    char *expression3 = "8+8*3+-2^5"; /* Result =  0 status = SUCCESS */
    char *expression4 = "8+8*3-2^"; /* Result =  0 status = SYNTAX_ERROR */
    char *expression5 = "2/0"; /* Result =  0 status = MATH_ERROR */
    char *expression6 = "8++8*((3-2)*5)"; /* Result = 48 status = SUCCESS */
    char *expression7 = "3-2)*5"; /* Result =  0 status = SYNTAX_ERROR */
    char *expression8 = "(3-2)*5+ 5*(4+4+4"; /* Result =  0 status = SYNTAX_ERROR */
	
    status = Calculator(expression1, &res);
	if(SUCCESS != status || res != 625)
	{
		printf("Testing Calculator: "
		"No Space Case: Expected res=8, status=0 but result is %f and status is %d\n", res, status);
		return 1;
	}

	status = Calculator(expression2, &res);
	if(SUCCESS != status || res != 15)
	{
		printf("Testing Calculator: "
		"Expected res=15, status=0 but result is %f and status is %d\n", res, status);
		return 2;
	}

	status = Calculator(expression3, &res);
	if(SUCCESS != status || res != 0)
	{
		printf("Testing Calculator: "
		"Expected res=0, status=0 but result is %f and status is %d\n", res, status);
		return 3;
	}

	status = Calculator(expression4, &res);
	if(SYNTAX_ERR != status || res != 0)
	{
		printf("Testing Calculator: "
		"Expected res=0, status=1 but result is %f and status is %d\n", res, status);
		return 4;
	}
	
	status = Calculator(expression5, &res);
	if(MATH_ERR != status || res != 0)
	{
		printf("Testing Calculator: "
		"Expected res=0, status=2 but result is %f and status is %d\n", res, status);
		return 5;
	}
	
	status = Calculator(expression6, &res);
	if(SUCCESS != status || res != 48)
	{
		printf("Testing Calculator: "
		"Expected res=48, status=0 but result is %f and status is %d\n", res, status);
		return 6;
	}
	
	status = Calculator(expression7, &res);
	if(SYNTAX_ERR != status || res != 0)
	{
		printf("Testing Calculator: "
		"Expected res=0, status=1 but result is %f and status is %d\n", res, status);
		return 7;
	}
	
	status = Calculator(expression8, &res);
	if(SYNTAX_ERR != status || res != 0)
	{
		printf("Testing Calculator: "
		"Expected res=0, status=1 but result is %f and status is %d\n", res, status);
		return 8;
	}

    return 0;

}

int main()
{
	int test_status = TestFlow();
	
	if(test_status == 0)
	{
		printf("CALC| ALL TESTS: %s\n", PASS);
	}
	else
	{
		printf("CALC| %s AT %d \n", FAIL, test_status);
	}

	return 0;
}
