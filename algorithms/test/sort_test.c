/*
Owner: Uri Naor
Date: Mar 31, 2024
*/

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

#define SLOW_LOOPS 100  /* loop count for slow loops - O(N^2) */
#define FAST_LOOPS 1000 /* loop count for faster loops - O(N log N) and O(N) */

#include <stdio.h> /* printf */
#include <time.h> /* clock() */
#include <stdlib.h> /* rand */

#include "sort.h" /* SelectionSort */

/******************** FORWARD DECLARATIONS ********************/
static void InitArray(int *arr, size_t size);
static int IsArraySorted(int *arr, size_t size);
static int Cmp(const void * a, const void * b);
static void CopyArray(int *dest, int *src, size_t size);

/******************** TESTS ********************/
int TestFlowSimpleSorts()
{
    int baseline[5000] = {0};
    int arr1[5000] = {0};
    int arr2[5000] = {0};
    int arr3[5000] = {0};
    int arr4[5000] = {0};
    int arr5[5000] = {0};
    int arr6[5000] = {0};
    int loop_idx = 0;

    clock_t start_selection, end_selection;
    clock_t start_bubble, end_bubble;
    clock_t start_insertion, end_insertion;
    clock_t start_qsort, end_qsort;
    clock_t start_counting, end_counting;
    clock_t start_radix, end_radix;
    double time_taken_selection = 0;
    double time_taken_bubble = 0;
    double time_taken_insertion = 0;
    double time_taken_qsort = 0;
    double time_taken_counting = 0;
    double time_taken_radix = 0;
    int temp;

    /* init a single permanent unsorted baseline */
    InitArray(baseline, 5000);

    /* testing selection sort */
    CopyArray(baseline, arr1, 5000);
    temp = IsArraySorted(arr1, 5000);
    if(0 != temp)
    {
        printf("Testing Selection\n");
        printf("unsorted arr case: Should be unsorted but result is sorted.\n");
        return 1;
    }

    time_taken_selection = 0;
    for (loop_idx = 0; loop_idx < SLOW_LOOPS; loop_idx++)
    {
        CopyArray(baseline, arr1, 5000);
        start_selection = clock();
        SelectionSort(arr1, 5000);
        end_selection = clock();
        time_taken_selection += (double)(end_selection - start_selection) / (double)(CLOCKS_PER_SEC);
    }
    /* get average time per run */
    time_taken_selection /= SLOW_LOOPS;
    
    temp = IsArraySorted(arr1, 5000);
    if(1 != temp)
    {
        printf("Testing Selection\n");
        printf("sorted arr case: Should be sorted but result is unsorted.\n");
        return 2;
    }

    
    /* testing bubble sort */
    CopyArray(baseline, arr2, 5000);
    temp = IsArraySorted(arr2, 5000);
    if(0 != temp)
    {
        printf("Testing Bubble\n");
        printf("unsorted arr case: Should be unsorted but result is sorted.\n");
        return 3;
    }

    time_taken_bubble = 0;
    for (loop_idx = 0; loop_idx < SLOW_LOOPS; loop_idx++)
    {
        CopyArray(baseline, arr2, 5000);
        start_bubble = clock();
        BubbleSort(arr2, 5000);
        end_bubble = clock();
        time_taken_bubble += (double)(end_bubble - start_bubble) / (double)(CLOCKS_PER_SEC);
    }
    time_taken_bubble /= SLOW_LOOPS;

    temp = IsArraySorted(arr2, 5000);
    if(1 != temp)
    {
        printf("Testing Bubble\n");
        printf("sorted arr case: Should be sorted but result is unsorted.\n");
        return 4;
    }


    /* testing insertion sort */
    CopyArray(baseline, arr3, 5000);
    temp = IsArraySorted(arr3, 5000);
    if(0 != temp)
    {
        printf("Testing Insertion\n");
        printf("unsorted arr case: Should be unsorted but result is sorted.\n");
        return 5;
    }

    time_taken_insertion = 0;
    for (loop_idx = 0; loop_idx < SLOW_LOOPS; loop_idx++)
    {
        CopyArray(baseline, arr3, 5000);
        start_insertion = clock();
        InsertionSort(arr3, 5000);
        end_insertion = clock();
        time_taken_insertion += (double)(end_insertion - start_insertion) / (double)(CLOCKS_PER_SEC);
    }
    time_taken_insertion /= SLOW_LOOPS;

    temp = IsArraySorted(arr3, 5000);
    if(1 != temp)
    {
        printf("Testing Insertion\n");
        printf("sorted arr case: Should be sorted but result is unsorted.\n");
        return 6;
    }


    /* testing quick sort */
    CopyArray(baseline, arr4, 5000);
    temp = IsArraySorted(arr4, 5000);
    if(0 != temp)
    {
        printf("Testing Quick Sort\n");
        printf("unsorted arr case: Should be unsorted but result is sorted.\n");
        return 7;
    }

    time_taken_qsort = 0;
    for (loop_idx = 0; loop_idx < FAST_LOOPS; loop_idx++)
    {
        CopyArray(baseline, arr4, 5000);
        start_qsort = clock();
        qsort(arr4, 5000, sizeof(int), Cmp);
        end_qsort = clock();
        time_taken_qsort += (double)(end_qsort - start_qsort) / (double)(CLOCKS_PER_SEC);
    }
    time_taken_qsort /= FAST_LOOPS;

    temp = IsArraySorted(arr4, 5000);
    if(1 != temp)
    {
        printf("Testing Quick Sort\n");
        printf("sorted arr case: Should be sorted but result is unsorted.\n");
        return 8;
    }


    /* testing counting sort */
    CopyArray(baseline, arr5, 5000);
    temp = IsArraySorted(arr5, 5000);
    if(0 != temp)
    {
        printf("Testing Counting Sort\n");
        printf("unsorted arr case: Should be unsorted but result is sorted.\n");
        return 9;
    }

    time_taken_counting = 0;
    for (loop_idx = 0; loop_idx < FAST_LOOPS; loop_idx++)
    {
        CopyArray(baseline, arr5, 5000);
        start_counting = clock();
        CountingSort(arr5, 5000);
        end_counting = clock();
        time_taken_counting += (double)(end_counting - start_counting) / (double)(CLOCKS_PER_SEC);
    }
    time_taken_counting /= FAST_LOOPS;

    temp = IsArraySorted(arr5, 5000);
    if(1 != temp)
    {
        printf("Testing Counting Sort\n");
        printf("sorted arr case: Should be sorted but result is unsorted.\n");
        return 10;
    }


    /* testing radix sort */
    CopyArray(baseline, arr6, 5000);
    temp = IsArraySorted(arr6, 5000);
    if(0 != temp)
    {
        printf("Testing Radix Sort\n");
        printf("unsorted arr case: Should be unsorted but result is sorted.\n");
        return 11;
    }

    time_taken_radix = 0;
    for (loop_idx = 0; loop_idx < FAST_LOOPS; loop_idx++)
    {
        CopyArray(baseline, arr6, 5000);
        start_radix = clock();
        RadixSort(arr6, 5000);
        end_radix = clock();
        time_taken_radix += (double)(end_radix - start_radix) / (double)(CLOCKS_PER_SEC);
    }
    time_taken_radix /= FAST_LOOPS;

    
    /* calculating time differences from Qsort using average time per run */
    printf("time diff of Selection from QSort (avg): %.8f\n", 
            time_taken_selection - time_taken_qsort);
    printf("time diff of Bubble from QSort (avg): %.8f\n", 
            time_taken_bubble - time_taken_qsort);
    printf("time diff of Insertion from QSort (avg): %.8f\n", 
            time_taken_insertion - time_taken_qsort);
    printf("time diff of Counting from QSort (avg): %.8f\n", 
            time_taken_counting - time_taken_qsort);
    printf("time diff of Radix from QSort (avg): %.8f\n", 
            time_taken_radix - time_taken_qsort);
    
    return 0;
}

int TestFlowAdvancedSorts()
{
    int temp;
    int arr[] = {-420,-120,-60,-5,-1,0,1,2,3,4,25,37,40,69,420,760};
    /*index        0    1   2   3  4 5 6 7 8 9 10,11,12,13, 14, 15 */
    size_t size = 16;
    int baseline[5000] = {0};
    int arr1[5000] = {0};
    int arr2[5000] = {0};
    int arr3[5000] = {0};
    int loop_idx = 0;
    clock_t start_merge, end_merge;
    clock_t start_my_qsort, end_my_qsort;
    clock_t start_default_qsort, end_default_qsort;
    double time_taken_merge = 0;
    double time_taken_my_qsort = 0;
    double time_taken_default_qsort = 0;

    InitArray(baseline, 5000);

    /******************** testing binary search ********************/
    temp = BinarySearch(arr, size, 69);
    if(13 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for 69, Should be at 13 but result is %d.\n", temp);
        return 1;
    }

    temp = BinarySearch(arr, size, -420);
    if(0 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for -420, Should be at 0 but result is %d.\n", temp);
        return 2;
    }

    temp = BinarySearch(arr, size, 760);
    if(15 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for 760, Should be at 15 but result is %d.\n", temp);
        return 3;
    }

    temp = BinarySearch(arr, size, -60);
    if(2 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for -60, Should be at 2 but result is %d.\n", temp);
        return 4;
    }

    temp = BinarySearch(arr, size, 2);
    if(7 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for 2, Should be at 7 but result is %d.\n", temp);
        return 5;
    }

    /******************** testing RECURSIVE binary search ********************/
    temp = BinarySearchRecursive(arr, size, 69);
    if(13 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for 69, Should be at 13 but result is %d.\n", temp);
        return 6;
    }

    temp = BinarySearchRecursive(arr, size, -420);
    if(0 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for -420, Should be at 0 but result is %d.\n", temp);
        return 7;
    }

    temp = BinarySearchRecursive(arr, size, 760);
    if(15 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for 760, Should be at 15 but result is %d.\n", temp);
        return 8;
    }

    temp = BinarySearchRecursive(arr, size, -60);
    if(2 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for -60, Should be at 2 but result is %d.\n", temp);
        return 9;
    }

    temp = BinarySearchRecursive(arr, size, 2);
    if(7 != temp)
    {
        printf("Testing Binary Search\n");
        printf("Searching for 2, Should be at 7 but result is %d.\n", temp);
        return 10;
    }

    /******************** testing merge sort ********************/
    CopyArray(baseline, arr1, 5000);
    temp = IsArraySorted(arr1, 5000);
    if(0 != temp)
    {
        printf("Testing Merge\n");
        printf("unsorted arr case: Should be unsorted but result is sorted.\n");
        return 11;
    }

    time_taken_merge = 0;
    for (loop_idx = 0; loop_idx < FAST_LOOPS; loop_idx++)
    {
        CopyArray(baseline, arr1, 5000);
        start_merge = clock();
        MergeSort(arr1, 5000);
        end_merge = clock();
        time_taken_merge += (double)(end_merge - start_merge) / (double)(CLOCKS_PER_SEC);
    }
    time_taken_merge /= FAST_LOOPS;

    temp = IsArraySorted(arr1, 5000);
    if(1 != temp)
    {
        printf("Testing Merge\n");
        printf("sorted arr case: Should be sorted but result is unsorted.\n");
        return 12;
    }

    /******************** testing MY quick sort ********************/
    CopyArray(baseline, arr2, 5000);
    temp = IsArraySorted(arr2, 5000);
    if(0 != temp)
    {
        printf("Testing My Qsort\n");
        printf("unsorted arr case: Should be unsorted but result is sorted.\n");
        return 13;
    }

    time_taken_my_qsort = 0;
    for (loop_idx = 0; loop_idx < FAST_LOOPS; loop_idx++)
    {
        CopyArray(baseline, arr2, 5000);
        start_my_qsort = clock();
        Qsort(arr2, 5000, sizeof(int), Cmp);
        end_my_qsort = clock();
        time_taken_my_qsort += (double)(end_my_qsort - start_my_qsort) / (double)(CLOCKS_PER_SEC);
    }
    time_taken_my_qsort /= FAST_LOOPS;

    temp = IsArraySorted(arr2, 5000);
    if(1 != temp)
    {
        printf("Testing My Qsort\n");
        printf("sorted arr case: Should be sorted but result is unsorted.\n");
        return 14;
    }


    /******************** testing DEFAULT quick sort ********************/
    CopyArray(baseline, arr3, 5000);
    temp = IsArraySorted(arr3, 5000);
    if(0 != temp)
    {
        printf("Testing Default Qsort\n");
        printf("unsorted arr case: Should be unsorted but result is sorted.\n");
        return 15;
    }

    time_taken_default_qsort = 0;
    for (loop_idx = 0; loop_idx < FAST_LOOPS; loop_idx++)
    {
        CopyArray(baseline, arr3, 5000);
        start_default_qsort = clock();
        qsort(arr3, 5000, sizeof(int), Cmp);
        end_default_qsort = clock();
        time_taken_default_qsort += (double)(end_default_qsort - start_default_qsort) / (double)(CLOCKS_PER_SEC);
    }
    time_taken_default_qsort /= FAST_LOOPS;

    temp = IsArraySorted(arr3, 5000);
    if(1 != temp)
    {
        printf("Testing Default Qsort\n");
        printf("sorted arr case: Should be sorted but result is unsorted.\n");
        return 16;
    }


    /* printing how long each advanced sort took */
    printf("how long Merge Sort took (avg): %.8f\n", 
            time_taken_merge);
    printf("how long My Quick Sort took (avg): %.8f\n", 
            time_taken_my_qsort);
    printf("how long Default Quick Sort took (avg): %.8f\n", 
            time_taken_default_qsort);

    return 0;
}


/******************** MAIN ********************/
int main()
{
    int test_status = TestFlowSimpleSorts();
    
    if(test_status == 0)
    {
        printf("Simple Sorts| ALL TESTS: %s\n", PASS);
    }
    else
    {
        printf("Simple Sorts| %s AT %d \n", FAIL, test_status);
    }

    test_status = TestFlowAdvancedSorts();
    
    if(test_status == 0)
    {
        printf("Binary Search & Advanced Sorts| ALL TESTS: %s\n", PASS);
    }
    else
    {
        printf("Binary Search & Advanced Sorts| %s AT %d \n", FAIL, test_status);
    }

    return 0;
}
/******************** HELPER FUNCS ********************/
static void InitArray(int *arr, size_t size)
{
    size_t i = 0;
    srand(time(NULL));

    for (i = 0; i < size; i++)
    {
        arr[i] = (rand() % 100) + 1; 
    }
}

static int IsArraySorted(int *arr, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size-1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return (0);
        }
    }

    return (1);
}

static int Cmp(const void * a, const void * b) 
{
   return (*(int*)a - *(int*)b);
}

static void CopyArray(int *arr1, int *arr2, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; i++)
    {
        arr2[i] = arr1[i];
    }
}