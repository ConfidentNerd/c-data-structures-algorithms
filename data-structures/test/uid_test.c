/*
Owner: Uri Naor
Date: Feb 29, 2024
*/

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

#include <stdio.h> /* printf */

#include "uid.h"

/******************** TESTS ********************/
int TestFlow()
{
	ilrd_uid_t uid1 = UIDGenerate();
	ilrd_uid_t uid2 = UIDGenerate();
	
	if(UIDIsEqual(uid1 , uid2))
	{
		printf("2 Different UIDs Test: Should be false, but result is true.\n");
		return 1;
	}
	
	if(0 == UIDIsEqual(uid1 , uid1))
	{
		printf("2 Different UIDs Test: Should be true, but result is false.\n");
		return 2;
	}
	
	return 0;
}

/******************** MAIN ********************/
int main()
{
	int test_status = TestFlow();
	
	if(test_status == 0)
	{
		printf("UID| ALL TESTS: %s\n", PASS);
	}
	else
	{
		printf("UID| %s AT %d \n", FAIL, test_status);
	}

	return 0;
}

