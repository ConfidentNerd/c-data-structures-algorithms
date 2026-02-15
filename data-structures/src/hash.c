/*
Owner: Uri Naor
Date: Mar 26, 2024
*/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "hash.h" /* Added missing include to verify prototypes against definitions */
#include "dlist.h" /* dlist_t */

/******************** TYPEDEFS, ENUMS & STRUCTS ********************/

struct hash
{
    hash_func_t hash_func;
    hash_cmp_func_t cmp_func;
    size_t table_size;
    dlist_t **table;
};

typedef struct params
{
    hash_cmp_func_t cmp_func;
    void *data;
}param_t;

enum bool
{
    FALSE = 0,
    TRUE
};

/******************** FORWARD DECLARATIONS ********************/
int HashForEach(hash_t *hash, hash_action_func_t action, void *params);
static void DestroyTable(hash_t *hash, size_t table_size);
static int IsMatch(const void *data, void *params);
static int AddOne(void *data , void *count);
static void InitTable(hash_t *hash, size_t table_size, hash_func_t hash_func, 
                                                      hash_cmp_func_t cmp_func);

/******************** FUNCTIONS ********************/
hash_t *HashCreate(hash_func_t hash_func, hash_cmp_func_t cmp_func, size_t table_size)
{
    hash_t *new_hash = NULL;
    size_t i = 0;
    
    assert(hash_func);
    assert(cmp_func);
    assert(table_size);

    new_hash = (hash_t *)malloc(sizeof(hash_t));
    if (NULL == new_hash)
    {
        return (NULL);
    }

    new_hash->table = malloc(sizeof(dlist_t *) * table_size);
    if (NULL == new_hash->table)
    {
        free(new_hash);
        return (NULL);
    }

    for (i = 0; i < table_size; i++)
    {
        new_hash->table[i] = DListCreate();
        if (NULL == new_hash->table[i])
        {
            DestroyTable(new_hash, i);
            free(new_hash);
            return (NULL);
        }
    }

    InitTable(new_hash, table_size, hash_func, cmp_func);

    return (new_hash);
}

void HashDestroy(hash_t *hash)
{
    assert(hash);

    DestroyTable(hash, hash->table_size);

    free(hash);
}

status_t HashInsert(hash_t *hash, const void *value)
{
    size_t idx = 0;
    dlist_iter_t iter = {0};

    assert(hash);
    assert(value);

    idx = hash->hash_func(value) % hash->table_size;

    iter = DListPushFront(hash->table[idx], (void *)value);
    if (DListIsIterSame(iter, DListEnd(hash->table[idx])))
    {
        return (FAIL);
    }

    return (SUCCESS);
}

void HashRemove(hash_t *hash, const void *value)
{
    size_t idx = 0;
    dlist_iter_t iter = {0};
    param_t params;

    assert(hash);
    assert(value);

    params.data = (void *)value;
    params.cmp_func = hash->cmp_func;

    idx = hash->hash_func(value) % hash->table_size;

    iter = DListFind(DListBegin(hash->table[idx]), DListEnd(hash->table[idx]), IsMatch, &params);

    if (!DListIsIterSame(iter, DListEnd(hash->table[idx]))) 
    {
        DListRemove(iter);
    }
}

void *HashFind(const hash_t *hash, const void *value)
{
    size_t idx = 0;
    dlist_iter_t iter = {0};
    param_t params;

    assert(hash);
    assert(value);

    params.data = (void *)value;
    params.cmp_func = hash->cmp_func;

    idx = hash->hash_func(value) % hash->table_size;

    iter = DListFind(DListBegin(hash->table[idx]), DListEnd(hash->table[idx]), IsMatch, &params);
    if (DListIsIterSame(DListEnd(hash->table[idx]), iter))
    {
        return NULL;
    }

    return (DListGetData(iter));
}

int HashIsEmpty(const hash_t *hash)
{
    size_t i = 0;
    int status = TRUE;

    assert(hash);

    for (i = 0; i < hash->table_size; i++)
    {
        status = DListIsEmpty(hash->table[i]);
        if (FALSE == status)
        {
            return (FALSE);
        }
    }

    return (TRUE);
}

size_t HashSize(const hash_t *hash)
{
    size_t count = 0;

    assert(hash);

    HashForEach((hash_t *)hash, AddOne, &count);

    return (count);
}

int HashForEach(hash_t *hash, hash_action_func_t action, void *params)
{
    size_t i = 0;
    int status = SUCCESS;
    dlist_iter_t begin = {0};
    dlist_iter_t end = {0};

    assert(hash);
    assert(action);

    for (i = 0; i < hash->table_size; i++)
    {
        begin = DListBegin(hash->table[i]);
        end = DListEnd(hash->table[i]);

        status = DListForEach(begin, end, action, params);
        
        if (SUCCESS != status) 
        {
            return (status);
        }
    }

    return (status);
}

double HashLoadFactor(const hash_t *hash)
{
    return ((double)HashSize(hash) / hash->table_size);
}

/******************** HELPER FUNCTIONS ********************/
static void InitTable(hash_t *hash, size_t table_size, hash_func_t hash_func, 
                                                      hash_cmp_func_t cmp_func)
{
    assert(hash);
    assert(hash_func);
    assert(cmp_func);
    assert(table_size);

    hash->table_size = table_size;
    hash->hash_func = hash_func;
    hash->cmp_func = cmp_func;
}

static void DestroyTable(hash_t *hash, size_t table_size)
{
    size_t i = 0;

    assert(hash);
    assert(table_size);

    for (i = 0; i < table_size; i++)
    {
        DListDestroy(hash->table[i]);
    }

    free(hash->table);
}

static int IsMatch(const void *data, void *params)
{
    assert(data);
    assert(params);

    return (!((param_t *)params)->cmp_func(data, ((param_t *)params)->data));
}

static int AddOne(void *data , void *count)
{	
	(void)data;
	
	*(size_t *)count = *(size_t *)count + 1;
	
	return (SUCCESS);
}
