/*
Owner: Uri Naor
Date: Feb 19, 2024
*/

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */

#include "cbuff.h" /*  CBuffCreate */

int main()
{
	cbuff_t *new_buff = CBuffCreate(20);
	char *src = "abcdefghijklmnopqrstuv";
	char dest[] = "hello-amigo";
	char dest2[] = "hello-amigo-shalom";
	char dest3[] = "hello-amigo-shalom-bonjour";
	ssize_t written = 0;
	ssize_t read = 0;
	
	printf("Testing Create & Empty List Case:\n");
	printf("Testing IsEmpty - empty list case, should be 1: %s\n" , CBuffIsEmpty(new_buff) == 1 ? PASS : FAIL);
	printf("Testing Size - 0 element list case, should be 0: %s\n" , CBuffSize(new_buff) == 0 ? PASS : FAIL);
	printf("Testing FreeSpace - 0 element list case, should be 20: %s\n" , CBuffFreeSpace(new_buff) == 20 ? PASS : FAIL);
	
	printf("\nTesting Write & List Size of 3 Elements:\n");
	written = CBuffWrite(new_buff, src, 3);
	printf("Testing Written, - 3 element case, should be 3: %s\n" , written == 3 ? PASS : FAIL);
	printf("Testing IsEmpty - 3 element list case, should be 0: %s\n" , CBuffIsEmpty(new_buff) == 0 ? PASS : FAIL);
	printf("Testing Size - 3 element list case, should be 3: %s\n" , CBuffSize(new_buff) == 3 ? PASS : FAIL);
	printf("Testing FreeSpace - 3 element list case, should be 17: %s\n" , CBuffFreeSpace(new_buff) == 17 ? PASS : FAIL);
	
	printf("\nTesting Read & List Size of 3 Elements:\n");
	read = CBuffRead(new_buff, dest, 3);
	printf("Testing Read, - 3 element case, should be 3: %s\n" , read == 3 ? PASS : FAIL);
	printf("Read from start case, dest was: hello-amigo, should be: abclo-amigo %s\n" , strcmp(dest, "abclo-amigo") == 0 ? PASS : FAIL);
	printf("Testing IsEmpty - after reading case, should be 1: %s\n" , CBuffIsEmpty(new_buff) == 1 ? PASS : FAIL);
	printf("Testing Size - after reading case, should be 0: %s\n" , CBuffSize(new_buff) == 0 ? PASS : FAIL);
	printf("Testing FreeSpace - after reading case, should be 20: %s\n" , CBuffFreeSpace(new_buff) == 20 ? PASS : FAIL);
	
	printf("\nTesting Write of 25 & List Size of 20 Elements:\n");
	written = CBuffWrite(new_buff, src, 25);
	printf("Testing Written, - 20 element case, should be 20: %s\n" , written == 20 ? PASS : FAIL);
	printf("Testing IsEmpty - 20 element list case, should be 0: %s\n" , CBuffIsEmpty(new_buff) == 0 ? PASS : FAIL);
	printf("Testing Size - 20 element list case, should be 20: %s\n" , CBuffSize(new_buff) == 20 ? PASS : FAIL);
	printf("Testing FreeSpace - 20 element list case, should be 0: %s\n" , CBuffFreeSpace(new_buff) == 0 ? PASS : FAIL);
	
	printf("\nTesting Read & List Size of 10 Elements:\n");
	read = CBuffRead(new_buff, dest2, 10);
	printf("Testing Read, - 10 element case, should be 10: %s\n" , read == 10 ? PASS : FAIL);
	printf("Read from 3rd position case, dest was: hello-amigo-shalom, should be: abcdefghijo-shalom %s\n" ,
	 strcmp(dest2, "abcdefghijo-shalom") == 0 ? PASS : FAIL);
	printf("dest2: %s\n", dest2);
	printf("Testing IsEmpty - after reading case, should be 0: %s\n" , CBuffIsEmpty(new_buff) == 0 ? PASS : FAIL);
	printf("Testing Size - after reading case, should be 10: %s\n" , CBuffSize(new_buff) == 10 ? PASS : FAIL);
	printf("Testing FreeSpace - after reading case, should be 10: %s\n" , CBuffFreeSpace(new_buff) == 10 ? PASS : FAIL);
	
	printf("\nTesting Write of 12 from mid of llist, when 10 free space\n");
	written = CBuffWrite(new_buff, src, 10);
	printf("Testing Written, - 12 element case, should be 10: %s\n" , written == 10 ? PASS : FAIL);
	printf("Testing IsEmpty - 20 element list case, should be 0: %s\n" , CBuffIsEmpty(new_buff) == 0 ? PASS : FAIL);
	printf("Testing Size - 20 element list case, should be 20: %s\n" , CBuffSize(new_buff) == 20 ? PASS : FAIL);
	printf("Testing FreeSpace - 20 element list case, should be 0: %s\n" , CBuffFreeSpace(new_buff) == 0 ? PASS : FAIL);
	
	printf("\nTesting Write of 2 to full List\n");
	written = CBuffWrite(new_buff, src, 2);
	printf("Testing Written, - 2 element case, should be Error -1: %s\n" , written == -1 ? PASS : FAIL);
	printf("Testing IsEmpty - 20 element list case, should be 0: %s\n" , CBuffIsEmpty(new_buff) == 0 ? PASS : FAIL);
	printf("Testing Size - 20 element list case, should be 20: %s\n" , CBuffSize(new_buff) == 20 ? PASS : FAIL);
	printf("Testing FreeSpace - 20 element list case, should be 0: %s\n" , CBuffFreeSpace(new_buff) == 0 ? PASS : FAIL);
	
	printf("\nTesting Read of 25 in list of 20\n");
	read = CBuffRead(new_buff, dest3, 20);
	printf("Testing Read, - when list full should be 20: %s\n" , read == 20 ? PASS : FAIL);
	printf("Read full list case, dest was: hello-amigo-shalom-bonjour, should be: klmnopqrstabcdefghijonjour %s\n" , strcmp(dest3, "klmnopqrstabcdefghijonjour") == 0 ? PASS : FAIL);
	printf("Testing IsEmpty - after reading case, should be 1: %s\n" , CBuffIsEmpty(new_buff) == 1 ? PASS : FAIL);
	printf("Testing Size - after reading case, should be 0: %s\n" , CBuffSize(new_buff) == 0 ? PASS : FAIL);
	printf("Testing FreeSpace - after reading case, should be 20: %s\n" , CBuffFreeSpace(new_buff) == 20 ? PASS : FAIL);
	
	printf("\nTesting Read of 1 in an empty list\n");
	read = CBuffRead(new_buff, dest3, 1);
	printf("Testing Read, - when list empty should be Error -1: %s\n" , read == -1 ? PASS : FAIL);
	printf("Testing IsEmpty - after reading empty list case, should be 1: %s\n" , CBuffIsEmpty(new_buff) == 1 ? PASS : FAIL);
	printf("Testing Size - after reading case, should be 0: %s\n" , CBuffSize(new_buff) == 0 ? PASS : FAIL);
	printf("Testing FreeSpace - after reading case, should be 20: %s\n" , CBuffFreeSpace(new_buff) == 20 ? PASS : FAIL);
	
	CBuffDestroy(new_buff);

	return 0;
}

