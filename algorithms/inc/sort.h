/*
Owner: Uri Naor
Date: Mar 31, 2024

Sorting and Searching Algorithms

Description:
This library provides implementations of classic comparison-based sorting 
algorithms (such as Bubble Sort, Insertion Sort, and Quick Sort), specialized 
non-comparison sorts (Counting Sort and Radix Sort), as well as iterative 
and recursive binary search algorithms.
*/

#ifndef SORT_HEADER
#define SORT_HEADER

#include <stddef.h>

/* Complexity: Time: O(n^2) worst/average/best | Space: O(1) | Stability: Unstable */
/******************************************************************************/
/* Description:  Sorts an array of integers in ascending order using the      */
/* Selection Sort algorithm. It repeatedly finds the minimum    */
/* element from the unsorted part and puts it at the beginning. */
/* Arguments:    arr - pointer to the array of integers to be sorted          */
/* size - the number of elements in the array                   */
/* Return value: None                                                         */
/* Note:         Passing a size of 0 is safe and will return immediately.     */
/******************************************************************************/
void SelectionSort(int arr[], size_t size);

/* Complexity: Time: O(n^2) worst/average, O(n) best | Space: O(1) | Stability: Stable */
/******************************************************************************/
/* Description:  Sorts an array of integers in ascending order using the      */
/* Bubble Sort algorithm. Adjacent elements are swapped if they */
/* are in the wrong order. Optimized to stop if already sorted. */
/* Arguments:    arr - pointer to the array of integers to be sorted          */
/* size - the number of elements in the array                   */
/* Return value: None                                                         */
/* Note:         Passing a size of 0 is safe and will return immediately.     */
/******************************************************************************/
void BubbleSort(int arr[], size_t size);

/* Complexity: Time: O(n^2) worst/average, O(n) best | Space: O(1) | Stability: Stable */
/******************************************************************************/
/* Description:  Sorts an array of integers in ascending order using the      */
/* Insertion Sort algorithm. Builds the sorted array one        */
/* element at a time by shifting larger elements to the right.  */
/* Arguments:    arr - pointer to the array of integers to be sorted          */
/* size - the number of elements in the array                   */
/* Return value: None                                                         */
/* Note:         Passing a size of 0 is safe and will return immediately.     */
/******************************************************************************/
void InsertionSort(int arr[], size_t size);

/* Complexity: Time: O(n + k) worst/avg/best | Space: O(n + k) | Stability: Stable */
/******************************************************************************/
/* Description:  Sorts an array of integers using the Counting Sort algorithm.*/
/* It counts the occurrences of each unique element to determine*/
/* their positions. (Where 'k' is the maximum value in the array)*/
/* Arguments:    arr - pointer to the array of integers to be sorted          */
/* size - the number of elements in the array                   */
/* Return value: None                                                         */
/* Note:         Passing a size of 0 is safe and will return immediately.     */
/******************************************************************************/
void CountingSort(int arr[], size_t size);

/* Complexity: Time: O(d * (n + 10)) worst/avg/best | Space: O(n) | Stability: Stable */
/******************************************************************************/
/* Description:  Sorts an array of integers using the Radix Sort algorithm.   */
/* It processes the elements digit by digit, from least to most */
/* significant, using a stable Counting Sort subroutine.        */
/* Arguments:    arr - pointer to the array of integers to be sorted          */
/* size - the number of elements in the array                   */
/* Return value: None                                                         */
/* Note:         Passing a size of 0 is safe and will return immediately.     */
/******************************************************************************/
void RadixSort(int arr[], size_t size);

/* Complexity: Time: O(log n) worst/average, O(1) best | Space: O(1) */
/******************************************************************************/
/* Description:  Searches for a target value within a sorted array using      */
/* the iterative Binary Search algorithm.                       */
/* Arguments:    sorted_arr - pointer to a sorted array of integers           */
/* size - the number of elements in the array                   */
/* target - the integer value to search for                     */
/* Return value: The index of the target if found, or -1 if not found.        */
/******************************************************************************/
int BinarySearch(int sorted_arr[], size_t size, int target);

/* Complexity: Time: O(log n) worst/average, O(1) best | Space: O(log n) */
/******************************************************************************/
/* Description:  Searches for a target value within a sorted array using      */
/* the recursive Binary Search algorithm.                       */
/* Arguments:    sorted_arr - pointer to a sorted array of integers           */
/* size - the number of elements in the array                   */
/* target - the integer value to search for                     */
/* Return value: The index of the target if found, or -1 if not found.        */
/* Note:         Space complexity is O(log n) due to the recursive call stack.*/
/******************************************************************************/
int BinarySearchRecursive(int sorted_arr[], size_t size, int target);

/* Complexity: Time: O(n log n) worst/avg/best | Space: O(n) | Stability: Stable */
/******************************************************************************/
/* Description:  Sorts an array using the recursive Merge Sort algorithm.     */
/* It divides the array into halves, sorts them, and merges     */
/* the sorted halves back together.                             */
/* Arguments:    arr_to_sort - pointer to the array of integers to be sorted  */
/* num_elements - the number of elements in the array           */
/* Return value: Returns 0 on success, or 1 if a memory allocation fails.     */
/******************************************************************************/
int MergeSort(int *arr_to_sort, size_t num_elements);

/* Complexity: Time: O(n^2) worst, O(n log n) avg/best | Space: O(log n) avg | Stability: Unstable */
/******************************************************************************/
/* Description:  Sorts an array of any data type using the Quick Sort         */
/* algorithm. A random pivot is selected to partition the array.*/
/* Arguments:    base - pointer to the first element of the array             */
/* nmemb - number of elements in the array                      */
/* size - size in bytes of each element                         */
/* compar - function pointer to compare two elements            */
/* Return value: None                                                         */
/******************************************************************************/
void Qsort(
    void *base, 
    size_t nmemb, 
    size_t size,
    int (*compar)(const void *,  const void *));

#endif /* SORT_HEADER */