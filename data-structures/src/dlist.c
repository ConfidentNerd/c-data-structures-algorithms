/*
Owner: Uri Naor
Date: Feb 19, 2024
*/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "dlist.h" /* dlist_t */

enum status 
{
SUCCESS = 0,
FAIL = 1,
NOT_FOUND = 2
};

/******************** STRUCTS ********************/
typedef struct dlist_node node_t;

struct dlist_node
{
    void *data;
    node_t *next;
    node_t *prev;
};

struct dlist
{
    node_t head;
    node_t tail;
};

/******************** FORWARD DECLARATIONS ********************/
static node_t *CreateNode(void *data, void *next, void *prev);
static dlist_iter_t NodeToIter(const node_t *node);
static node_t *IterToNode(dlist_iter_t iter);
static node_t *GoToEnd(node_t *node);
static int AddOne(void *data , void *count);
static int IsWhereBetween(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where);

/******************** FUNCTIONS ********************/
dlist_t *DListCreate()
{
	dlist_t *list = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == list)
	{
		return (NULL);
	}
	
	list->head.prev = NULL;
	list->head.data = list;
	list->head.next = &list->tail;
	
	list->tail.prev = &list->head;
	list->tail.data = list;
	list->tail.next = NULL;
	
	return (list);
}

void DListDestroy(dlist_t *list)
{
	dlist_iter_t curr;
	dlist_iter_t next;
	
	assert(list);
	
	curr = DListBegin(list);
	next = DListNext(curr);
	
	while (!DListIsIterSame(curr, DListEnd(list)))
	{
		next = DListNext(curr);
		DListRemove(curr);
		curr = next;
	}

	free(list);
}

dlist_iter_t DListBegin(const dlist_t *list)
{
	assert(list);

	return (DListNext(NodeToIter(&list->head)));
}

dlist_iter_t DListEnd(const dlist_t *list)
{
	assert(list);

	return (NodeToIter(&list->tail));
}

dlist_iter_t DListNext(dlist_iter_t iter)
{
	node_t *iter_node = IterToNode(iter);
	
	assert(iter);
	
	return (NodeToIter(iter_node->next));
}

dlist_iter_t DListPrev(dlist_iter_t iter)
{
	node_t *iter_node = IterToNode(iter);
	
	assert(iter);
	
	return (NodeToIter(iter_node->prev));
}

int DListIsIterSame(dlist_iter_t iter1, dlist_iter_t iter2)
{
	node_t *iter1_node = IterToNode(iter1);
	node_t *iter2_node = IterToNode(iter2);

	assert(iter1);
	assert(iter2);

	return (iter1_node == iter2_node);
}

dlist_iter_t DListInsert(dlist_iter_t where, void* data)
{
	node_t *where_node = IterToNode(where);
	node_t *new_node = CreateNode(data, where_node, where_node->prev);
	
	assert(where);
	
	if (NULL == new_node)
	{
		
		return (NodeToIter(GoToEnd(where_node)));
	}
	
	new_node->prev->next = new_node;
	new_node->next->prev = new_node;
	
	return (NodeToIter(new_node));
}

dlist_iter_t DListRemove(dlist_iter_t to_remove)
{
	node_t *remove_node = NULL;
	node_t *to_return = NULL;
	
	assert(IterToNode(to_remove));
	
	remove_node = IterToNode(to_remove);
	to_return = remove_node->next;
	
	(to_remove->next)->prev = to_remove->prev;
	to_remove->prev->next = to_remove->next;
	
	free(remove_node);
	
	return (to_return);
}

void *DListGetData(dlist_iter_t iter)
{
	node_t *iter_node = IterToNode(iter);
	
	assert(iter);

	return (NodeToIter(iter_node->data));
}

void DListSetData(dlist_iter_t iter, void *data)
{
	node_t *iter_node = IterToNode(iter);
	
	assert(iter);
	
	iter_node->data = data;
}

size_t DListCount(const dlist_t *list)
{
	size_t count = 0;
	
	assert(list);

    DListForEach(DListBegin(list), DListEnd(list), AddOne, &count);
		
	return (count);
}

int DListIsEmpty(const dlist_t *list)
{
	assert(list);
	
	return (DListIsIterSame(DListBegin(list), DListEnd(list)));
}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, 
					   match_func_t is_match, void *param)
{
	assert(from);
    assert(to);
    assert(is_match);

	while (!(DListIsIterSame(from, to)) && 
	!(is_match(DListGetData(from), param)))
	{
		from = DListNext(from);
	}
	
	return (from);   
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action, 
				 void *param)
{
    int status = SUCCESS;
    
    assert(IterToNode(from));
    assert(IterToNode(to));
    
    while (!DListIsIterSame(from ,to) && status == SUCCESS)
    {
        status = action(DListGetData(from), param);
       
		from = DListNext(from);
    }
    
    return (status);
}

void DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	node_t *from_prev = IterToNode(from)->prev;
	node_t *to_prev = IterToNode(to)->prev;
	node_t *where_prev = IterToNode(where)->prev;
	
	assert(!IsWhereBetween(from, to, where));
	
	where->prev->next = from;
	to->prev->next = where;
	from->prev->next = to;
	where->prev = to_prev;
	from->prev = where_prev;
	to->prev = from_prev;
}

int DListMultiFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match,
				   void *param, dlist_t *found_elements)
{
	int status = NOT_FOUND;
	dlist_iter_t iter = NULL;
	assert(from);
    assert(to);
    assert(is_match);
    assert(found_elements);    

	while (!(DListIsIterSame(from, to)))
	{
		if (is_match(DListGetData(from), param))
		{
			iter = DListPushBack(found_elements, DListGetData(from));
			
			if (DListIsIterSame(iter, DListEnd(found_elements)))
			{
				return (FAIL);
			}
			
			status = SUCCESS;
		}
	
		from = DListNext(from);
	}
	
	return (status);   
}

dlist_iter_t DListPushBack(dlist_t *list, void *data)
{
	assert(list);

	return (DListInsert(DListEnd(list), data));
}

void *DListPopBack(dlist_t *list)
{
	void *data = DListGetData(DListPrev(DListEnd(list)));
	
	assert(list);
	
	DListRemove(DListPrev(DListEnd(list)));
	
	return (data);
}

dlist_iter_t DListPushFront(dlist_t *list, void *data)
{
	return (DListInsert(DListBegin(list), data));
}

void *DListPopFront(dlist_t *list)
{
	void *data = DListGetData(DListBegin(list));
	
	assert(list);
	
	DListRemove(DListBegin(list));
	
	return (data);
}

/******************** HELPER FUNCTIONS ********************/
static node_t *CreateNode(void *data, void *next, void *prev)
{
	node_t *new_node = (node_t *)(malloc)(sizeof(node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}	
	
	new_node->data = data;
	new_node->next = next;
	new_node->prev = prev;
	
	return (new_node);
}

static dlist_iter_t NodeToIter(const node_t *node)
{
	return ((dlist_iter_t)node);
}

static node_t *IterToNode(dlist_iter_t iter)
{
	return ((node_t *)iter);
}

static node_t *GoToEnd(node_t *node)
{
	while (node->next != NULL)
	{
		node = node->next;
	}
	
	return (node);
}

static int AddOne(void *data , void *count)
{	
	(void)data;
	
	*(size_t *)count = *(size_t *)count + 1;
	
	return (SUCCESS);
}

static int IsWhereBetween(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	while (!DListIsIterSame(from, to))
	{
		if(DListIsIterSame(from, where))
		{
			return (1);
		}
		
		from = DListNext(from);
	}
	
	return (0);
}
