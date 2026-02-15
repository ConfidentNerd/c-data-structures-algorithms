/*
Owner: Uri Naor
Date: Mar 24, 2024
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "avl.h"

#define GOOD "\033[1;30m\033[102m"
#define BAD "\033[1;37m\033[41m"
#define REG "\033[1;0m""\n"
#define HEAD "\033[1;30m\033[47m"
#define SUB_HEAD "\033[1;30m\033[43m"

#define HEADER_LEN 58

#define PRINT_HEADER(x) printf(HEAD"%s"REG, MP(x))
#define PRINT_SUB_HEADER(x) printf(SUB_HEAD"%s"REG, MP(x))
#define PRINT_REG(x) printf("%s"REG, MP(x))

#define PRINT_SUCCESS printf(GOOD"%s"REG, MP("SUCCESS"))
#define PRINT_FAILURE printf(BAD"%s"REG, MP("FAILURE"))

/* Fixed missing parameter evaluation in macro so we print strings properly */
#define PRINT_BAD(x) printf(BAD"%s"REG, MP(x))

#define JUNK -123

static char *MP(char *str)
{
	char *spaces = "                                    ";
	size_t num_of_spaces = (HEADER_LEN - strlen(str)) / 2;
	
	static char pretty_str[HEADER_LEN] = {0};
	
	assert(HEADER_LEN > strlen(str));
	
	*pretty_str = '\0';
	
	strncat(pretty_str, spaces, num_of_spaces);
	strncat(pretty_str, str, strlen(str));
	strncat(pretty_str, spaces, num_of_spaces);
	
	if (strlen(pretty_str) < HEADER_LEN)
	{
		strcat(pretty_str, " ");
	}
	
	return pretty_str;
}


int CmpInts(const void *lhs, const void *rhs)
{
	assert(NULL != lhs);
	assert(NULL != rhs);
	
	return *(int *)lhs - *(int *)rhs;
}


avl_t *AVLCreateTEST(void)
{
	size_t error_count = 0;
	
	avl_t *tree = AVLCreate(CmpInts);
	
	/* trying to destroy a brand new tree */
	avl_t *tree_to_remove = AVLCreate(CmpInts);
	
	if (NULL == tree)
	{
		PRINT_FAILURE;
		PRINT_BAD("AVLCreate returned pointer was NULL");
		++error_count;
	}
	if (0 != AVLSize(tree))
	{
		PRINT_FAILURE;
		PRINT_BAD("AVLSize: Size of newly created tree wasn't 0");
		++error_count;
	}
	if (1 != AVLIsEmpty(tree))
	{
		PRINT_FAILURE;
		PRINT_BAD("AVLIsEmpty: Newly created tree wasn't empty");
		++error_count;
	}
	
	if (0 == error_count)
	{
		PRINT_SUCCESS;
	}

	AVLDestroy(tree_to_remove);
	
	return tree;
}


void VerifySize(avl_t *tree, size_t expected_size)
{
	size_t size = AVLSize(tree);
	
	PRINT_SUB_HEADER("Verifyng size:");
	
	if (size == expected_size)
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected size = %lu | Actual size = %lu"REG, expected_size, size);
	}
}

void VerifyHeight(avl_t *tree, size_t expected_height)
{
	size_t height = AVLHeight(tree);
	
	PRINT_SUB_HEADER("Verifyng height:");
	
	if (height == expected_height)
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected height = %lu | Actual height = %lu"REG, expected_height, height);
	}
}

void AVLFindTEST(avl_t *tree, void *key, void *expected_data)
{
	void *data = AVLFind(tree, key);
	
	if (data == expected_data)
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected data was different than returned data"REG);
		printf(BAD"Expected data = %d | Actual data = %d"REG,
		 *(int *)expected_data, *(int *)data);
	}
}

void AVLRemoveTEST(avl_t *tree, void *data)
{
	size_t size_before = AVLSize(tree);
	size_t error_count = 0;

	AVLRemove(tree, data);

	if (size_before != AVLSize(tree) + 1)
	{
		++error_count;
		PRINT_FAILURE;
		printf(BAD"size wasn't updated after removal"REG);
	}
	
	if (0 == error_count)
	{
		PRINT_SUCCESS;
	}
}

void AVLFakeRemoveTEST(avl_t *tree, void *data)
{
	size_t size_before = AVLSize(tree);
	size_t error_count = 0;

	AVLRemove(tree, data);

	if (size_before != AVLSize(tree))
	{
		++error_count;
		PRINT_FAILURE;
		printf(BAD"size was updated after fake removal"REG);
	}
	
	if (0 == error_count)
	{
		PRINT_SUCCESS;
	}
}

int AVLInsertTEST(avl_t *tree, void *data)
{
	size_t error_count = 0;
	size_t size_before = AVLSize(tree);

	AVLInsert(tree, data);
	
	if (size_before + 1 != AVLSize(tree))
	{
		++error_count;
		PRINT_FAILURE;
		printf(BAD"size wasn't updated after insert"REG);
		printf("\nexpected: %lu\nrecieved: %lu\n", size_before + 1, AVLSize(tree));
	}
	
	if (0 == error_count)
	{
		PRINT_SUCCESS;
	}
	
	return error_count;
}

static void PrintArr(int *arr, size_t size)
{
	int *arr_runner = arr;
	int *end_address = arr + size;

	printf("[ ");
	while (arr_runner < end_address)
	{
		printf("%i ", *arr_runner);
		++arr_runner;
	}
	printf("]"REG);
}

int AddDataToArr(void *data, void *arr)
{
	int *arr_runner = (int *)arr;
	
	while (JUNK != *arr_runner)
	{
		++arr_runner;
	}
	
	*arr_runner = *(int *)data;
	
	return 0;
}

void SetArrJunk(int *arr, size_t size)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		arr[i] = JUNK;
	}
}
	
void AVLNoBalanceFlowTEST(void)
{
	avl_t *tree = NULL;
	
	   /* INDEXES:  0  1   2   3  4 5 6 7 8  9   */
	int list[10] = {23,10,-15,134,4,2,1,9,43,0};
	
	int sorted_list[10] = {0};
	int pre_order_list[10] = {23,10,-15,4,2,1,0,9,134,43};
	int post_order_list[10] = {0, 1, 2, 9, 4, -15, 10, 43, 134, 23};
	int pre_order_list_after_remove[10] = {43,10,4,2,1,9,134};
	
	int for_each_arr_data[10] = {JUNK,JUNK,JUNK,JUNK,JUNK,JUNK,JUNK,JUNK,JUNK,JUNK};
	
	int ghost_ints[5] = {11,-44,23,0,93};
	
	memcpy(&sorted_list, list, sizeof(int) * 10);
	qsort(sorted_list, 10, 4, CmpInts);
	
	PRINT_HEADER("Flow Test:");
	
	PRINT_SUB_HEADER("AVLCreateTEST: Creating a new tree");
	tree = AVLCreateTEST();
	
	VerifyHeight(tree, 0);

	PRINT_SUB_HEADER("AVLInsertTEST: Inserting 10 elements");
	AVLInsertTEST(tree, &list[0]);	/* 23  */
	AVLInsertTEST(tree, &list[1]); /* 10  */
	AVLInsertTEST(tree, &list[2]); /* -15  */
	AVLInsertTEST(tree, &list[3]);	/* 134 */
	AVLInsertTEST(tree, &list[4]); /* 4   */
	AVLInsertTEST(tree, &list[5]); /* 2   */
	AVLInsertTEST(tree, &list[6]); /* 1   */
	AVLInsertTEST(tree, &list[7]); /* 9   */
	AVLInsertTEST(tree, &list[8]); /* 43  */
	AVLInsertTEST(tree, &list[9]); /* 0   */
	VerifyHeight(tree, 6);

	PRINT_SUB_HEADER("AVLFind: Searching for all 10 datas");
	AVLFindTEST(tree, &list[0], &list[0]);
	AVLFindTEST(tree, &list[1], &list[1]);
	AVLFindTEST(tree, &list[2], &list[2]);
	AVLFindTEST(tree, &list[3], &list[3]);
	AVLFindTEST(tree, &list[4], &list[4]);
	AVLFindTEST(tree, &list[5], &list[5]);
	AVLFindTEST(tree, &list[6], &list[6]);
	AVLFindTEST(tree, &list[7], &list[7]);
	AVLFindTEST(tree, &list[8], &list[8]);
	AVLFindTEST(tree, &list[9], &list[9]);
	
	
	PRINT_SUB_HEADER("AVLForEach: checking in order");
	AVLForEach(tree, AddDataToArr, &for_each_arr_data, IN_ORDER);
	
	if (0 == memcmp(&sorted_list, &for_each_arr_data, sizeof(int) * 10))
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(sorted_list, 10);
		printf(BAD"Actual array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(for_each_arr_data, 10);
	}

	SetArrJunk(for_each_arr_data, 10);
	PRINT_SUB_HEADER("AVLForEach: checking pre order");
	AVLForEach(tree, AddDataToArr, &for_each_arr_data, PRE_ORDER);
	
	if (0 == memcmp(&pre_order_list, &for_each_arr_data, sizeof(int) * 10))
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(pre_order_list, 10);
		printf(BAD"Actual array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(for_each_arr_data, 10);
	}

	SetArrJunk(for_each_arr_data, 10);
	PRINT_SUB_HEADER("AVLForEach: checking post order");
	AVLForEach(tree, AddDataToArr, &for_each_arr_data, POST_ORDER);
	
	if (0 == memcmp(&post_order_list, &for_each_arr_data, sizeof(int) * 10))
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(post_order_list, 10);
		printf(BAD"Actual array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(for_each_arr_data, 10);
	}

	VerifySize(tree, 10);

	PRINT_SUB_HEADER("AVLRemove: checking leaf removal (val 0) - 0 childs");
	AVLRemoveTEST(tree, &list[9]);
	
	VerifyHeight(tree, 5);

	PRINT_SUB_HEADER("AVLRemove: checking leaf removal (val -15) - 1 childs");
	AVLRemoveTEST(tree, &list[2]);

	PRINT_SUB_HEADER("AVLForEach: checking in order after remove");
	SetArrJunk(for_each_arr_data, 10);
	AVLForEach(tree, AddDataToArr, &for_each_arr_data, IN_ORDER);
	
	if (0 == memcmp(((int *)(&sorted_list)) + 2, &for_each_arr_data, sizeof(int) * 8))
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(sorted_list + 2, 8);
		printf(BAD"Actual array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(for_each_arr_data, 8);
	}

	PRINT_SUB_HEADER("AVLRemove: checking leaf removal (val 23) - 2 childs");
	AVLRemoveTEST(tree, &list[0]);

	PRINT_SUB_HEADER("AVLForEach: checking pre order after remove");
	SetArrJunk(for_each_arr_data, 10);
	AVLForEach(tree, AddDataToArr, &for_each_arr_data, PRE_ORDER);
	
	if (0 == memcmp(&pre_order_list_after_remove, &for_each_arr_data, sizeof(int) * 7))
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(pre_order_list_after_remove, 7);
		printf(BAD"Actual array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(for_each_arr_data, 7);
	}

	PRINT_SUB_HEADER("AVLFind: look for deleted/non-existing values");
	AVLFindTEST(tree, &ghost_ints[0], NULL);
	AVLFindTEST(tree, &ghost_ints[1], NULL);
	AVLFindTEST(tree, &ghost_ints[2], NULL);
	AVLFindTEST(tree, &ghost_ints[3], NULL);
	AVLFindTEST(tree, &ghost_ints[4], NULL);

	PRINT_SUB_HEADER("AVLRemove: Removing all nodes but one:");
	AVLRemoveTEST(tree, &list[1]);
	AVLRemoveTEST(tree, &list[4]);
	AVLRemoveTEST(tree, &list[3]);
	AVLRemoveTEST(tree, &list[5]);
	AVLRemoveTEST(tree, &list[6]);
	AVLRemoveTEST(tree, &list[7]);

	VerifyHeight(tree, 0);

	PRINT_SUB_HEADER("AVLRemove: Removing last node");
	AVLRemoveTEST(tree, &list[8]);

	VerifySize(tree, 0);

	VerifyHeight(tree, 0);

	PRINT_SUB_HEADER("AVLInsertTEST: Inserting 10 elements to the emptied tree");
	AVLInsertTEST(tree, &list[0]);
	AVLInsertTEST(tree, &list[1]);
	AVLInsertTEST(tree, &list[2]);
	AVLInsertTEST(tree, &list[3]);
	AVLInsertTEST(tree, &list[4]);
	AVLInsertTEST(tree, &list[5]);
	AVLInsertTEST(tree, &list[6]);
	AVLInsertTEST(tree, &list[7]);
	AVLInsertTEST(tree, &list[8]);
	AVLInsertTEST(tree, &list[9]);
	VerifySize(tree, 10);
	
	
	PRINT_SUB_HEADER("AVLDestroyTEST: Destroying the tree");
	AVLDestroy(tree);
	PRINT_REG("*** RUN VALGRING TO VERIFY NO MEMORY LEAKS ***");
	
	printf("\n");
}

void AVLBalanceFlowTEST(void)
{
	avl_t *tree = NULL;
	
	   /* INDEXES:  0  1   2   3  4 5 6 7 8  9  10 */
	int list[11] = {23,10,-15,134,4,2,1,9,43,0,-20};
	
	int a = 10000;

	int sorted_list[11] = {0};
	
	int for_each_arr_data[11] = {JUNK,JUNK,JUNK,JUNK,JUNK,JUNK,JUNK,JUNK,JUNK,JUNK};
	
	int ghost_ints[5] = {11,-44,134,-20,93};
	
	memcpy(&sorted_list, list, sizeof(int) * 11);
	qsort(sorted_list, 11, 4, CmpInts);
	
	PRINT_HEADER("Flow Test:");
	
	PRINT_SUB_HEADER("AVLCreateTEST: Creating a new tree");
	tree = AVLCreateTEST();
	
	VerifyHeight(tree, 0);

	PRINT_SUB_HEADER("AVLInsertTEST: Inserting 10 elements");
	AVLInsertTEST(tree, &list[0]);	/* 23  */
	VerifyHeight(tree, 0);
	AVLInsertTEST(tree, &list[1]); /* 10  */
	VerifyHeight(tree, 1);
	AVLInsertTEST(tree, &list[2]); /* -15  */
	VerifyHeight(tree, 1);
	AVLInsertTEST(tree, &list[3]);	/* 134 */
	VerifyHeight(tree, 2);
	AVLInsertTEST(tree, &list[4]); /* 4   */
	VerifyHeight(tree, 2);
	AVLInsertTEST(tree, &list[5]); /* 2   */
	VerifyHeight(tree, 2);
	AVLInsertTEST(tree, &list[6]); /* 1   */
	VerifyHeight(tree, 3);
	AVLInsertTEST(tree, &list[7]); /* 9   */
	VerifyHeight(tree, 3);
	AVLInsertTEST(tree, &list[8]); /* 43  */
	VerifyHeight(tree, 3);
	AVLInsertTEST(tree, &list[9]); /* 0   */
	VerifyHeight(tree, 3);
	AVLInsertTEST(tree, &list[10]); /* -20 */
	VerifyHeight(tree, 3);

	PRINT_SUB_HEADER("AVLFind: Searching for all 10 datas");
	AVLFindTEST(tree, &list[0], &list[0]);
	AVLFindTEST(tree, &list[1], &list[1]);
	AVLFindTEST(tree, &list[2], &list[2]);
	AVLFindTEST(tree, &list[3], &list[3]);
	AVLFindTEST(tree, &list[4], &list[4]);
	AVLFindTEST(tree, &list[5], &list[5]);
	AVLFindTEST(tree, &list[6], &list[6]);
	AVLFindTEST(tree, &list[7], &list[7]);
	AVLFindTEST(tree, &list[8], &list[8]);
	AVLFindTEST(tree, &list[9], &list[9]);
	AVLFindTEST(tree, &list[10], &list[10]);
	
	SetArrJunk(for_each_arr_data, 11);
	PRINT_SUB_HEADER("AVLForEach: checking in order");
	AVLForEach(tree, AddDataToArr, &for_each_arr_data, IN_ORDER);
	
	if (0 == memcmp(&sorted_list, &for_each_arr_data, sizeof(int) * 11))
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(sorted_list, 11);
		printf(BAD"Actual array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(for_each_arr_data, 11);
	}

	VerifySize(tree, 11);

	PRINT_SUB_HEADER("AVLRemove: checking leaf removal (val -20)");
	AVLRemoveTEST(tree, &list[10]);

	PRINT_SUB_HEADER("AVLRemove: checking leaf removal (val -15)");
	AVLRemoveTEST(tree, &list[2]);

	PRINT_SUB_HEADER("AVLRemove: checking leaf removal (val 134)");
	AVLRemoveTEST(tree, &list[3]);
	
	VerifyHeight(tree, 3);

	PRINT_SUB_HEADER("AVLForEach: checking in order after remove");
	SetArrJunk(for_each_arr_data, 11);
	AVLForEach(tree, AddDataToArr, &for_each_arr_data, IN_ORDER);
	
	if (0 == memcmp(((int *)(&sorted_list)) + 2, &for_each_arr_data, sizeof(int) * 8))
	{
		PRINT_SUCCESS;
	}
	else
	{
		PRINT_FAILURE;
		printf(BAD"Expected array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(sorted_list + 2, 8);
		printf(BAD"Actual array after AVLForEach:"REG);
		printf(BAD"");
		PrintArr(for_each_arr_data, 8);
	}

	PRINT_SUB_HEADER("AVLRemove: checking leaf removal (val 10)");
	AVLRemoveTEST(tree, &list[1]);

	VerifyHeight(tree, 3);

	PRINT_SUB_HEADER("AVLRemove: checking leaf removal (val 1)");
	AVLRemoveTEST(tree, &list[6]);

	VerifyHeight(tree, 2);


	PRINT_SUB_HEADER("AVLFind: look for deleted/non-existing values");
	AVLFindTEST(tree, &ghost_ints[0], NULL);
	AVLFindTEST(tree, &ghost_ints[1], NULL);
	AVLFindTEST(tree, &ghost_ints[2], NULL);
	AVLFindTEST(tree, &ghost_ints[3], NULL);
	AVLFindTEST(tree, &ghost_ints[4], NULL);

	PRINT_SUB_HEADER("AVLRemove: test non-existing remove");
	AVLFakeRemoveTEST(tree, &a);

	PRINT_SUB_HEADER("AVLRemove: Removing all nodes but one:");
	AVLRemoveTEST(tree, &list[8]);
	AVLRemoveTEST(tree, &list[4]);
	AVLRemoveTEST(tree, &list[9]);
	AVLRemoveTEST(tree, &list[5]);
	AVLRemoveTEST(tree, &list[7]);
	AVLRemoveTEST(tree, &list[0]);

	VerifySize(tree, 0);

	VerifyHeight(tree, 0);

	PRINT_SUB_HEADER("AVLInsertTEST: Inserting 10 elements to the emptied tree");
	AVLInsertTEST(tree, &list[0]);
	AVLInsertTEST(tree, &list[1]);
	AVLInsertTEST(tree, &list[2]);
	AVLInsertTEST(tree, &list[3]);
	AVLInsertTEST(tree, &list[4]);
	AVLInsertTEST(tree, &list[5]);
	AVLInsertTEST(tree, &list[6]);
	AVLInsertTEST(tree, &list[7]);
	AVLInsertTEST(tree, &list[8]);
	AVLInsertTEST(tree, &list[9]);
	AVLInsertTEST(tree, &list[10]);
	VerifySize(tree, 11);
	
	
	PRINT_SUB_HEADER("AVLDestroyTEST: Destroying the tree");
	AVLDestroy(tree);
	PRINT_REG("*** RUN VALGRING TO VERIFY NO MEMORY LEAKS ***");
	
	printf("\n");
}

int main()
{
	/* Uncommented so both tests execute */
	AVLNoBalanceFlowTEST(); 
	AVLBalanceFlowTEST();
	
	return 0;
}
