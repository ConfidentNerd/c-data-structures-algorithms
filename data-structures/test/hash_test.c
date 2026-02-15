/*
Owner: Uri Naor
Date: Mar 26, 2024
*/

#define _GNU_SOURCE /* strdup */
#include <stdio.h> /* printf */
#include <string.h> /* strcmp */
#include <stdlib.h> /* free */

#include "hash.h" /* hash_t */

#define PASS "\033[1;32mPASS\033[0m" /* green bold PASS string */
#define FAIL "\033[1;31mFAIL\033[0m" /* red bold FAIL string */

static void SpellCheck(const char *dictionaryPath);

size_t HashFunc(const void* value);
int CompFunc(const void *a, const void *b);
int CleanupFunc(void *data, void *param);

int main(int argc, char *argv[])
{
    /* use user passed path if available, else default to the standard linux dict */
    const char *dict_path = (argc > 1) ? argv[1] : "/usr/share/dict/words";
    
    SpellCheck(dict_path);

    return 0;
}

static void SpellCheck(const char *dictionaryPath) 
{
    FILE *dictFile = fopen(dictionaryPath, "r");
    hash_t *dictHash = NULL;
    char word[50] = {0};
    size_t tableSize = 140000;

    if (dictFile == NULL) 
    {
        fprintf(stderr, "FAIL to open dictionary file at: %s\n", dictionaryPath);
        exit(EXIT_FAILURE);
    }

    dictHash = HashCreate(HashFunc, CompFunc, tableSize);
    if (dictHash == NULL) 
    {
        fprintf(stderr, "FAIL to create hash table\n");
        fclose(dictFile);
        exit(EXIT_FAILURE);
    }

    while (fgets(word, sizeof(word), dictFile)) 
    {
        word[strcspn(word, "\n")] = 0;   
        HashInsert(dictHash, strdup(word));
    }

    fclose(dictFile);

    printf("Dictionary loaded. Enter words to check or 'q' to quit.\n");
    while (1) 
    {
        printf("Word: ");

        if (fgets(word, sizeof(word), stdin) == NULL) 
        {
            break; 
        }
        word[strcspn(word, "\n")] = 0; 
        
        if (strcmp(word, "q") == 0)
        {
            break;
        }

        if (HashFind(dictHash, word)) 
        {
            printf("%s is in the dictionary.\n", word);
        } 

        else 
        {
            printf("%s is NOT in the dictionary.\n", word);
        }
    }

    HashForEach(dictHash, CleanupFunc, NULL);

    HashDestroy(dictHash); 
    printf("Exiting program.\n");
}

size_t HashFunc(const void* value) 
{
    char *str = (char *)value;
    size_t hash = 5381;
    while (*str)
    {
        hash = 33 * hash ^ *str++;
    }

    return (hash);
}


int CompFunc(const void *a, const void *b) 
{
    return strcmp((const char *)a, (const char *)b);
}

int CleanupFunc(void *data, void *param)
{
    (void)param; 
    free(data);
    return SUCCESS; 
}
