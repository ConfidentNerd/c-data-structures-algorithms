/*
Owner: Uri Naor
Date: Feb 22, 2024
*/

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include "srtlist.h" /*srtlist_iter_t*/

#ifndef NDEBUG
    #define DEBUG_ONLY(x) {x;}
#else
    #define DEBUG_ONLY(x)
#endif

/******************** STRUCTS ********************/
struct srtlist
{
	dlist_t *dlist;
	cmp_func_t cmp_func;
};

/******************** FUNCTIONS ********************/
srtlist_t *SrtListCreate(cmp_func_t cmp_func)
{
	srtlist_t *new_srtlist = NULL;
	dlist_t *new_dlist = DListCreate();
	
	assert(cmp_func);
	
	if(NULL == new_dlist)
	{
		return (NULL);
	}
	
	new_srtlist = malloc(sizeof(srtlist_t));
	if (NULL == new_srtlist)
	{
		DListDestroy(new_dlist);
		
		return (NULL);
	}
	
	new_srtlist->dlist = new_dlist;
	new_srtlist->cmp_func = cmp_func;
	
	return (new_srtlist);
}

void SrtListDestroy(srtlist_t *list)
{
	assert(list);

	DListDestroy(list->dlist);
	
	free(list);
}

srtlist_iter_t SrtListBegin(const srtlist_t *list)
{
	srtlist_iter_t iter;
	
	assert(list);
	
	iter.iter = DListBegin(list->dlist);
	DEBUG_ONLY(iter.list = (srtlist_t *)list);
	
	return (iter);
}

srtlist_iter_t SrtListEnd(const srtlist_t *list)
{
	srtlist_iter_t iter;
	
	assert(list);
	
	iter.iter = DListEnd(list->dlist);
	DEBUG_ONLY(iter.list = (srtlist_t *)list);
	
	return (iter);
}

srtlist_iter_t SrtListNext(srtlist_iter_t iter)
{
	iter.iter = DListNext(iter.iter);
	
	return (iter);
}

srtlist_iter_t SrtListPrev(srtlist_iter_t iter)
{
	iter.iter = DListPrev(iter.iter);
	
	return (iter);
}

int SrtListIsIterSame(srtlist_iter_t iter1, srtlist_iter_t iter2)
{
	return (DListIsIterSame(iter1.iter, iter2.iter));
}

srtlist_iter_t SrtListInsert(srtlist_t *list, void* data)
{
	srtlist_iter_t runner = SrtListBegin(list);

	assert(list);
	
	while((!SrtListIsIterSame(runner, SrtListEnd(list))) && 
		 (0 >= list->cmp_func(SrtListGetData(runner), data)))
	{
		runner = SrtListNext(runner);
	}
	
	runner.iter = DListInsert(runner.iter, data);
	DEBUG_ONLY(runner.list = list);
	
	return (runner);
}

srtlist_iter_t SrtListRemove(srtlist_iter_t to_remove)
{
	to_remove.iter = DListRemove(to_remove.iter);
	
	return (to_remove);
}

void *SrtListGetData(srtlist_iter_t iter)
{
	return (DListGetData(iter.iter));
}

size_t SrtListCount(const srtlist_t *list)
{
	assert(list);

	return (DListCount(list->dlist));
}

int SrtListIsEmpty(const srtlist_t *list)
{
	assert(list);

	return (DListIsEmpty((list->dlist)));
}

srtlist_iter_t SrtListFind(srtlist_t *list, srtlist_iter_t from,
						   srtlist_iter_t to, void *data)
{
	int res = -1;

	assert(list);
	assert(from.list == to.list);
	
	while((!SrtListIsIterSame(from, to)) && 
		 (0 > res))
	{
		res = list->cmp_func(SrtListGetData(from), data);
		from = SrtListNext(from);
	}
	
	return (res == 0 ? SrtListPrev(from) : to);
}

srtlist_iter_t SrtListFindIf(srtlist_iter_t from, srtlist_iter_t to,
							 match_func_t is_match, void *param)
{
	assert(from.list == to.list);
	assert(is_match);

	from.iter = DListFind(from.iter, to.iter, is_match, param);

	return (from);
}

int SrtListForEach(srtlist_iter_t from, srtlist_iter_t to, 
				   action_func_t action, void *param)
{
	assert(action);
	assert(from.list == to.list);

	return ((DListForEach(from.iter, to.iter, action, param)));
}

void *SrtListPopBack(srtlist_t *list)
{
	assert(list);

	return (DListPopBack(list->dlist));
}

void *SrtListPopFront(srtlist_t *list)
{
	assert(list);

	return (DListPopFront(list->dlist));
}

void SrtListMerge(srtlist_t *dest, srtlist_t *src)
{
	srtlist_iter_t from = SrtListBegin(src);
	srtlist_iter_t to = SrtListNext(from);
	srtlist_iter_t where = SrtListBegin(dest);
	
	assert(dest);
	assert(src);
	assert(where.list != from.list);
	assert(src->cmp_func == dest->cmp_func);
	
	while (!SrtListIsEmpty(src))
	{
		from = SrtListBegin(src);
		to = SrtListNext(from);
		
		while(!SrtListIsIterSame(where, SrtListEnd(dest)) &&
		dest->cmp_func(SrtListGetData(from), SrtListGetData(where)) >= 0)
		{
			where = SrtListNext(where);
		}
		
		if (SrtListIsIterSame(where, SrtListEnd(dest)))
		{
			to = SrtListEnd(src);
		} 
		else
		{
			while(!SrtListIsIterSame(to, SrtListEnd(src)) &&
			dest->cmp_func(SrtListGetData(where), SrtListGetData(to)) >= 0)
			{
				to = SrtListNext(to);
			}
		}
		
		DListSplice(from.iter, to.iter, where.iter); 
	}
}

