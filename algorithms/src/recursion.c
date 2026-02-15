/*
Owner: Uri Naor
Date: Mar 20, 2024
*/

#include <stddef.h>
#include <string.h>

#include "recursion.h"

/******************** FORWARD DECLARATIONS ********************/
static void SortedInsert (stack_t *stack, int saved);

/******************** FUNCTIONS ********************/

int Fibonacci(int element_index)
{
    if (element_index == 1 || element_index == 2)
    {
        return 1;
    }
    if (element_index == 0)
    {
        return 0;
    }

    return (Fibonacci(element_index - 1) + Fibonacci(element_index - 2));
}

node_t * Flip(node_t * node)
{
    node_t *rest = NULL;

    if (node == NULL || node->next == NULL)
    {
        return node;
    }

    rest = Flip(node->next);

    node->next->next = node;
    node->next = NULL;

    return rest;
}

void SortStack(stack_t *stack)
{
    int saved = 0;

    if (!(StackIsEmpty(stack)))
    {
        saved = *(int *)StackPeek(stack);
        StackPop(stack);

        SortStack(stack);

        SortedInsert(stack, saved);
    }
}

size_t Strlen(const char *str)
{
    if (*str == '\0')
    {
        return (0);
    }

    return (Strlen(str + 1) + 1);
}

int Strcmp(const char *str1, const char *str2)
{
    if (*str1 != *str2 || *str1 == '\0' || *str2 == '\0')
    {
        return (*str1 - *str2);
    }

    return (Strcmp(str1+1, str2+1));
}

char *Strcpy(char *dest, const char *src)
{
    *dest = *src;
    if (*src != '\0')
    {
        Strcpy(dest + 1, src + 1);
    }

    return dest;
}

char *Strcat(char *dest, const char *src)
{
    Strcpy(dest + Strlen(dest), src);

    return dest;
}

char *Strstr(const char *haystack, const char *needle)
{
    size_t needle_length = 0;
    
    if (*needle == '\0')
    {
        return ((char *)haystack);
    }

    if (*haystack == '\0')
    {
        return NULL;
    }

    needle_length = Strlen(needle);

    if(strncmp(haystack, needle, needle_length) == 0)
    {
        return ((char *)haystack);
    }

    return Strstr(haystack+1, needle);
}

/******************** HELPER FUNCTIONS ********************/
static void SortedInsert (stack_t *stack, int saved)
{
    int temp = 0;

    if ((StackIsEmpty(stack)) || (saved > *(int *)StackPeek(stack)))
    {
        StackPush(stack, &saved);
    }
    else
    {
        temp = *(int *)StackPeek(stack);
        StackPop(stack);

        SortedInsert(stack, saved);

        StackPush(stack, &temp);
    }

}