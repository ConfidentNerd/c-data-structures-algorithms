/*
Owner: Uri Naor
Date: Mar 20, 2024
*/

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

#include "recursion.h"

/******************** HELPER FUNCTIONS ********************/
static void PrintListInt(node_t *head)
{
	while(head != NULL)
	{
		printf("data: %d\n", *(int *)head->data);
		head = head->next;
	}

}

/******************** TESTS ********************/
int TestFlow1()
{
    int temp = 0;
	
    temp = Fibonacci(7);
	if(13 != temp)
	{
		printf("Testing Fibonacci.\n");
		printf("expected 13, but result is %d\n", temp);
		return 1;
	}

    temp = Fibonacci(0);
	if(0 != temp)
	{
		printf("Testing Fibonacci.\n");
		printf("expected 0, but result is %d\n", temp);
		return 2;
	}

    temp = Fibonacci(1);
	if(1 != temp)
	{
		printf("Testing Fibonacci.\n");
		printf("expected 1, but result is %d\n", temp);
		return 3;
	}

    temp = Fibonacci(2);
	if(1 != temp)
	{
		printf("Testing Fibonacci.\n");
		printf("expected 1, but result is %d\n", temp);
		return 4;
	}

    temp = Fibonacci(5);
	if(5 != temp)
	{
		printf("Testing Fibonacci.\n");
		printf("expected 5, but result is %d\n", temp);
		return 5;
	}

    temp = Fibonacci(23);
	if(28657 != temp)
	{
		printf("Testing Fibonacci.\n");
		printf("expected 28657, but result is %d\n", temp);
		return 6;
	}

    return 0;
}

int TestFlow2()
{
    node_t one;
    node_t two;
    node_t three;
    node_t four;
    node_t five;
    
    node_t one_list_2;
    node_t two_list_2;
    node_t three_list_2;

    one.data = malloc(sizeof(int));
    two.data = malloc(sizeof(int));
    three.data = malloc(sizeof(int));
    four.data = malloc(sizeof(int));
    five.data = malloc(sizeof(int));
    
    one_list_2.data = malloc(sizeof(int));
    two_list_2.data = malloc(sizeof(int));
    three_list_2.data = malloc(sizeof(int));
    
    if (one.data == NULL || two.data == NULL || three.data == NULL || 
    four.data == NULL || five.data == NULL || one_list_2.data == NULL ||
     two_list_2.data == NULL || three_list_2.data == NULL)
    {
        return 1;
    }

    *(int *)one.data = 1;
    *(int *)two.data = 2;
    *(int *)three.data = 3;
    *(int *)four.data = 4;
    *(int *)five.data = 5;

    one.next = &two;
    two.next = &three;
    three.next = &four;
    four.next = &five;
    five.next = NULL;

	printf("list by order: \n");
    PrintListInt(&one);
    
    printf("now list should be flipped: \n");
    PrintListInt(Flip(&one));
    
    printf("flipped back: \n");
    Flip(&five);
    PrintListInt(&one);
    
    free(one.data);
    free(two.data);
    free(three.data);
    free(four.data);
    free(five.data);
    free(one_list_2.data);
    free(two_list_2.data);
    free(three_list_2.data);

    return 0;
}

int TestFlow3()
{
    stack_t *stack = StackCreate(10, sizeof(int));
    int i = 0;

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;

    StackPush(stack, &d);
    StackPush(stack, &a);
    StackPush(stack, &e);
    StackPush(stack, &c);
    StackPush(stack, &b);

    printf("TESTING SORT STACK FUNC\n");
    printf("Unsorted stack is: \n");

    for (i = 0; i < 5; i++)
    {
        printf("elem num %d is: %d\n", i, *(int *)StackPeek(stack));
        StackPop(stack);
    }

    StackPush(stack, &d);
    StackPush(stack, &a);
    StackPush(stack, &e);
    StackPush(stack, &c);
    StackPush(stack, &b);

    SortStack(stack);

    printf("RAN SORTED STACK FUNC\n");
    printf("stack should be sorted: \n");

    for (i = 0; i < 5; i++)
    {
        printf("elem num %d is: %d\n", i, *(int *)StackPeek(stack));
        StackPop(stack);
    }

    return 0;
}

void TestStrCmp()
{
	char str1[] = "hello";
	char str2[] = "hello";
	
	char str3[] = "aello";
	char str4[] = "cello";
	
	char str5[] = "cello";
	char str6[] = "aello";
	
	char str7[] = "hello";
	char str8[] = "hell";
	
	char str9[] = "hell";
	char str10[] = "hello";
	
	printf("\nTesting StrCmp:\n");
	printf("should be 0: %d\n", Strcmp(str1, str2));
	printf("should be -2: %d\n", Strcmp(str3, str4));
	printf("should be 2: %d\n", Strcmp(str5, str6));
	printf("should be 111: %d\n", Strcmp(str7, str8));
	printf("should be -111: %d\n", Strcmp(str9, str10));
}

void TestStrCpy()
{
	char str1[] = "hello";
	char str2[] = "yello";
	char str3[] = "hola";
	char str4[] = "amigo-muchacho";
	
	printf("\nTesting StrCpy:\nTest1\nBefore: src = %s, dest = %s\n", str1, str2);
	Strcpy(str2, str1);
	printf("After: src = %s, dest= %s\n", str1, str2);

    printf("Test2\nBefore: src = %s, dest = %s\n", str3, str4);
	Strcpy(str4, str3);
	printf("After: src = %s, dest = %s\n", str3, str4);
}

void TestStrCat()
{
	char str1[100] = "This is ", str2[] = "Infinity Labs";
	
	printf("\nTesting StrCat:\n");
	printf("should be: This is Infinity Labs | %s\n", Strcat(str1, str2));
}

void TestStrStr()
{
	
	char *hay = "heymanyocowhahahellomydudehelloooo";
	char *needle = "hello";
	
	printf("\nTesting Strstr:\n");
	printf("should return hellomydudehelloooo: %s\n", Strstr(hay, needle));
}

/******************** MAIN ********************/
int main()
{
	int test_status = TestFlow1();
	
	if(test_status == 0)
	{
		printf("Fibonacci| ALL TESTS: %s\n", PASS);
	}
	else
	{
		printf("Fibonacci| %s AT %d \n", FAIL, test_status);
	}

    TestFlow2();

    TestFlow3();

    TestStrCmp();

    TestStrCpy();

    TestStrCat();

    TestStrStr();

	return 0;
}