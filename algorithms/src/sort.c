/*
Owner: Uri Naor
Date: Mar 31, 2024
*/

#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf for helper function */
#include <assert.h> /* assert */
#include <time.h> /* srand */

/******************** FORWARD DECLARATIONS ********************/
static void CopyArray(int *dest, int *src, size_t size);
static void CountingSortForDigits(int arr[], size_t size, size_t digit);
static int GetMaxDigits(int num);
static int BinarySearchRecursiveHelper(
    int sorted_arr[],
    size_t left,
    size_t right,
    int target
);
static int Merge(
    int *left_arr, 
    int *right_arr, 
    size_t left_size, 
    size_t right_size
);
static void GenericSwap(void *a, void *b, size_t elem_size);
static size_t Partition(void *base, 
size_t low, 
size_t high, 
size_t size, 
int (*compar)(const void *, const void *)
);
static void QsortRecursion(
    void *base, 
    size_t low, 
    size_t high, 
    size_t size, 
    int (*compar)(const void *, const void *)
);


/******************** FUNCTIONS ********************/
void SelectionSort(int arr[], size_t size)
{
    size_t i = 0;
    size_t j = 0;
    size_t min_idx = 0;
    int temp = 0;

    for (i = 0; i < size; i++)
    {
        min_idx = i;

        for (j = i; j < size; j++)
        {
            if (arr[min_idx] > arr[j])
            {
                min_idx = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void BubbleSort(int arr[], size_t size)
{
    size_t j = 0;
    int temp = 0;
    int swapped = 1;

    if (0 == size) return; 

    while (swapped)
    {
        swapped = 0;

        for (j = 0; j < size-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swapped = 1;
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }

        size -= 1;
    }
}

void InsertionSort(int arr[], size_t size)
{
    size_t i = 0;
    size_t j = 0;
    int curr_elem = 0;

    for (i = 1; i < size; i++)
    {
        curr_elem = arr[i];
        j = i;

        while (j > 0 && arr[j-1] > curr_elem)
        {
            arr[j] = arr[j-1];
            --j;
        }
        arr[j] = curr_elem;
    }
}

void CountingSort(int arr[], size_t size)
{
    int *range_arr = NULL;
    int *new_arr = NULL;
    size_t i = 0;
    size_t range = 0;

    if (0 == size) return; 

    range = arr[0];

    for (i = 0; i < size; i++)
    {
        if (arr[i] > (int)range)
        {
            range = arr[i];
        }
    }

    range_arr = (int *)calloc(range + 1, sizeof(int));
    if (NULL == range_arr)
    {
        return;
    }

    new_arr = (int *)malloc(size * sizeof(int));
    if (NULL == new_arr)
    {
        free(range_arr);
        return;
    }

    for (i = 0; i < size; i++)
    {
        range_arr[arr[i]]++;
    }

    for (i = 0; i < (range); i++)
    {
        range_arr[i + 1] += range_arr[i];
    }

    for (i = size; i > 0; i--) 
    {
        range_arr[arr[i - 1]]--;
        new_arr[range_arr[arr[i - 1]]] = arr[i - 1];
    }

    CopyArray(arr, new_arr, size);

    free(new_arr);
    free(range_arr);
}


void RadixSort(int arr[], size_t size)
{
    int max = 0;
    size_t i = 0;
    size_t digit = 1;
    size_t max_digits = 1; 

    if (0 == size) return; 
    
    max = arr[0];

    for (i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    max_digits = GetMaxDigits(max);

    for (i = 0; i < max_digits; i++)
    {
        CountingSortForDigits(arr, size, digit);
        digit *= 10;
    }
}

int BinarySearch(int sorted_arr[], size_t size, int target)
{
    size_t left = 0;
    size_t right = 0;
    size_t mid_idx = 0;
    int mid_value = 0;

    assert(sorted_arr);

    if (0 == size) return (-1); 

    right = size-1;

    while(left <= right)
    {
        mid_idx = (left + right) / 2;
        mid_value = sorted_arr[mid_idx];

        if (mid_value == target)
        {
            return ((int)mid_idx);
        }

        if (mid_value < target)
        {
            left = mid_idx + 1;
        }

        if (mid_value > target)
        {
            right = mid_idx - 1;
        }
    }

    return (-1);
}

int BinarySearchRecursive(int sorted_arr[], size_t size, int target)
{
    size_t left = 0;
    size_t right = 0;

    assert(sorted_arr);

    if (0 == size) return (-1);

    right = size-1;

    return (BinarySearchRecursiveHelper(sorted_arr, left, right, target));   
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
    size_t left_size = 0;
    size_t right_size = 0;
    int *left_arr = NULL;
    int *right_arr = NULL;

    assert(arr_to_sort);

    if (num_elements < 2)
    {
        return (0);
    }

    left_size = num_elements / 2;
    right_size = num_elements - left_size;

    left_arr = arr_to_sort;
    right_arr = arr_to_sort + left_size;

    MergeSort(left_arr, left_size);
    MergeSort(right_arr, right_size);

    return (Merge(left_arr, right_arr, left_size, right_size));
}

void Qsort(
    void *base, 
    size_t nmemb, 
    size_t size, 
    int (*compar)(const void *, const void *))
{
    assert(base);
    assert(nmemb);
    assert(size);
    assert(compar);

    if (2 > nmemb)
    {
        return;
    }

    /* srand is used to choose a random pivot each run */
    srand(time(NULL));
    QsortRecursion(base, 0, nmemb - 1, size, compar);
}


/******************** HELPER FUNCS ********************/
static void QsortRecursion(
    void *base, 
    size_t low, 
    size_t high, 
    size_t size, 
    int (*compar)(const void *, const void *))
{
    if (low < high)
    {
        size_t pivot_index = Partition(base, low, high, size, compar);
        
        if (pivot_index > 0)
        {
            QsortRecursion(base, low, pivot_index - 1, size, compar);
        }
        
        QsortRecursion(base, pivot_index + 1, high, size, compar);
    }
}

static size_t Partition(void *base, size_t low, size_t high, size_t size, int (*compar)(const void *, const void *))
{
    size_t pivot_index = 0;
    size_t i = 0;
    size_t j = 0;
    void *pivot_value = NULL;

    /* choose a random pivot between low and high inclusive*/
    pivot_index = low + (rand() % (high - low));

    /* if pivot index isn't the last element, swap with last elem. */
    if (pivot_index != high)
    {
        GenericSwap(((char *)base + (pivot_index * size)), 
                    ((char *)base + (high * size)), size);
    }
    
    pivot_value = (char *)base + (high * size);
    i = low;

    /* go over array and sort it compared to pivot value */
    for (j = low; j < high; j++)
    {
        if (compar((char *)base + (j * size), pivot_value) <= 0)
        {
            GenericSwap(((char *)base + (i * size)), ((char *)base + (j * size)), size);
            i++;
        }
    }

    /* place pivot value in correct spot and return it's index */
    GenericSwap(((char *)base + (i * size)), ((char *)base + (high * size)), size);
    return i;
}

static void GenericSwap(void *a, void *b, size_t elem_size)
{
    char temp = '\0';
    size_t i = 0;

    assert(a);
    assert(b);
    assert(elem_size);

    for (i = 0; i < elem_size; i++)
    {
        temp = *((char *)a + i);
        *((char *)a + i) = *((char *)b + i);
        *((char *)b + i) = temp;
    }
}

static int Merge(
    int *left_arr, 
    int *right_arr, 
    size_t left_size, 
    size_t right_size) 
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    int *merged_arr = (int *)malloc((left_size + right_size) * sizeof(int));
    if (NULL == merged_arr)
    {
        return (1);
    }

    while (i < left_size && j < right_size) 
    {
        if (left_arr[i] <= right_arr[j]) 
        {
            merged_arr[k] = left_arr[i];
            i++;
        } else {
            merged_arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < left_size) 
    {
        merged_arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < right_size) 
    {
        merged_arr[k] = right_arr[j];
        j++;
        k++;
    }

    for (i = 0; i < left_size; i++)
        left_arr[i] = merged_arr[i];

    for (j = 0; j < right_size; j++)
        left_arr[left_size + j] = merged_arr[left_size + j];

    free(merged_arr);

    return (0);
}


static int BinarySearchRecursiveHelper(
    int sorted_arr[],
    size_t left,
    size_t right,
    int target)
{
    int mid_value = 0;
    size_t mid = 0;

    if (left > right)
    {
        return (-1);
    }

    mid = (left + right) / 2;
    mid_value = sorted_arr[mid];

    if (mid_value == target)
    {
        return ((int)mid);
    }

    if (mid_value < target)
    {
        return (BinarySearchRecursiveHelper(sorted_arr, mid+1, right, target));
    }

    if (mid_value > target)
    {
        return (BinarySearchRecursiveHelper(sorted_arr, left, mid-1, target));
    }

    return 0;
}

static void CopyArray(int *dest, int *src, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

static void CountingSortForDigits(int arr[], size_t size, size_t digit)
{
    int range_arr[10] = {0};
    int *new_arr = NULL;
    size_t i = 0;

    new_arr = (int *)malloc(size * sizeof(int));
    if (NULL == new_arr)
    {
        return;
    }
	
    for (i = 0; i < size; i++)
    {
        (range_arr[(arr[i] / digit) % 10])++;
    }

    for (i = 1; i < 10; i++)
    {
        range_arr[i] += range_arr[i - 1];
    }

    for (i = size; i > 0; i--) 
    {
        new_arr[range_arr[(arr[i - 1] / digit) % 10] - 1] = arr[i - 1];
        --range_arr[(arr[i - 1] / digit) % 10];
    }

    CopyArray(arr, new_arr, size);

    free(new_arr);
}

static int GetMaxDigits(int num)
{
    int count = 0;

    while (num)
    {
        count++;
        num /= 10;
    }

    return count;
}