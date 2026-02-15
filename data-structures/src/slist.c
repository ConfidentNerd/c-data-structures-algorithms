/*
Owner: Uri Naor
Date: Feb 16, 2024
*/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "slist.h" /* slist_t */

enum status 
{
SUCCESS = 0,
FAIL = 1
}; 


/******************** STRUCTS ********************/
typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

struct slist
{
    node_t *head;
    node_t *tail;
};

/******************** FORWARD DECLARATIONS ********************/
static slist_iter_t NodeToIter(node_t *node);
static node_t *IterToNode(slist_iter_t iter);
static int AddOne(void *data , void *count);
static node_t *CreateNode(void *data, void* next);
static node_t *GoToEnd(node_t *node);

/******************** FUNCTIONS ********************/
slist_t *SListCreate()
{
	node_t *dummy;	
	
	slist_t *new_list = (slist_t *)malloc(sizeof(slist_t));
	if (NULL == new_list)
	{
		return NULL;
	}
	
	dummy = CreateNode(new_list, NULL);
	if (NULL == dummy)
	{
		free(new_list);
		return NULL;
	}
	
	new_list->head = dummy;
	new_list->tail = dummy;
	
	return new_list;
}

void SListDestroy(slist_t *list)
{
	slist_iter_t curr = SListBegin(list);
	slist_iter_t next = NULL;
	
	assert(list);
	
	while (!SListIsIterSame(curr, SListEnd(list)))
	{
		next = curr->next;
		free(curr);
		curr = next;
	}

	free(curr);
	free(list);
}

slist_iter_t SListBegin(const slist_t *list)
{
	assert(list);

	return (NodeToIter(list->head));
}

slist_iter_t SListEnd(const slist_t *list)
{
	assert(list);

	return (NodeToIter(list->tail));
}

slist_iter_t SListNext(slist_iter_t where)
{
	node_t *where_node = IterToNode(where);
	
	assert(where);
	
	return (NodeToIter(where_node->next));
}

int SListIsIterSame(slist_iter_t where1, slist_iter_t where2)
{
	node_t *where1_node = IterToNode(where1);
	node_t *where2_node = IterToNode(where2);

	assert(where1);
	assert(where2);

	return where1_node == where2_node;
}

slist_iter_t SListInsert(slist_iter_t where, void* data)
{
	node_t *where_node = IterToNode(where);
	node_t *new_node = CreateNode(where_node->data, where_node->next);
	if (NULL == new_node)
	{
		return NodeToIter(GoToEnd(where_node));
	}
	
	where_node->next = new_node;
	where_node->data = data;

	
	if (NULL == new_node->next)
	{
		((slist_t *)new_node->data)->tail = new_node;
	}
	
	return NodeToIter(where_node);
}

slist_iter_t SListRemove(slist_iter_t to_remove)
{
	node_t *temp_node = NULL;
	node_t *to_remove_node = IterToNode(to_remove);
	
	assert(to_remove);
	assert(to_remove_node->next != NULL);
	
	temp_node = to_remove_node->next;
	to_remove_node->data = to_remove_node->next->data;
	to_remove_node->next = to_remove_node->next->next;
	
	free(temp_node);
	
	if (to_remove_node->next == NULL)
	{
		((slist_t *)to_remove_node->data)->tail = to_remove_node;
	}
	
	return (NodeToIter(to_remove_node));
}

void *SListGetData(slist_iter_t iter)
{
	node_t *iter_node = IterToNode(iter);
	
	assert(iter);

	return (iter_node->data);
}

void SListSetData(slist_iter_t iter, void *data)
{
	node_t *iter_node = IterToNode(iter);
	
	assert(iter);
	assert(data);
	
	iter_node->data = data;
}

size_t SListCount(const slist_t *list)
{
	size_t count = 0;
	node_t *head = list->head;
	node_t *tail = list->tail;
	
	assert(list);

	SListForEach(head, tail, AddOne, &count);
		
	return (count);
}

int SListIsEmpty(const slist_t *list)
{
	assert(list);
	
	return (SListIsIterSame(NodeToIter(list->head), NodeToIter(list->tail)));
}

slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t is_match, void *param)
{
	assert(from);
    assert(to);
    assert(is_match);

	while (!(SListIsIterSame(from, to)) && !(is_match(SListGetData(from), param)))
	{
		from = SListNext(from);
	}
	
	return (from);
}

int SListForEach(slist_iter_t from, slist_iter_t to, action_func_t action, void *param)
{
	node_t *from_node = IterToNode(from);
	node_t *to_node = IterToNode(to);
    int status = SUCCESS;
    
    assert(from);
    assert(to);
    
    while (from_node != to_node && status == SUCCESS)
    {
        status = action(from_node->data, param);
       
		from_node = from_node->next;
    }
    
    return (status);
}

void SListAppend(slist_t *dest, slist_t *src)
{	
	slist_t *src_dummy_data = src->tail->data;
	
	assert(dest != src);
	assert(dest);
	assert(src);
	
	/* prevent breaking dest when src is empty */
	if (SListIsEmpty(src)) 
	{
		return;
	}
	
	src->tail->data = dest->tail->data;
	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;
	dest->tail = src->tail;
	src->head->data = src_dummy_data;
    src->tail = src->head;
    src->tail->next = NULL;
}

/******************** FUNCTIONS HELPERS ********************/
static slist_iter_t NodeToIter(node_t *node)
{
	return ((slist_iter_t)node);
}

static node_t *IterToNode(slist_iter_t iter)
{
	return ((node_t *)iter);
}

static int AddOne(void *data , void *count)
{	
	(void)data;
	
	*(size_t *)count = *(size_t *)count + 1;
	
	return SUCCESS;
}

static node_t *CreateNode(void *data, void *next)
{
	node_t *new_node = (node_t *)(malloc)(sizeof(node_t));
	if (NULL == new_node)
	{
		return NULL;
	}	
	
	new_node->data = data;
	new_node->next = next;
	
	return new_node;
}

static node_t *GoToEnd(node_t *node)
{
	while(node->next != NULL)
	{
		node = node->next;
	}
	
	return node;
}
