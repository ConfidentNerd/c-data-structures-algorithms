/*
Owner: Uri Naor
Date: Mar 12, 2024
*/

#include <assert.h>
#include <stdlib.h>

#include "bst.h" /* bst_iter_t */

/******************** ENUMS ********************/
enum status 
{
    SUCCESS = 0,
    FAIL = 1
};

enum 
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_CHILDREN = 2
};

/******************** STRUCTS ********************/
typedef struct node bst_node_t;

struct node
{
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
    void *data;
    
};

struct tree
{
    bst_node_t root;
    cmp_func_t cmp_func;
};

#define ACTUAL_ROOT ((bst->root.children[LEFT]))
#define DUMMY ((bst_node_t *)&(bst->root))

/******************** FORWARD DECLARATIONS ********************/
static bst_iter_t NodeToIter(const bst_node_t *node);
static bst_node_t *IterToNode(bst_iter_t iter);
static int AddOne(void *data , void *count);
static int NodeLeftOrRight(bst_node_t *node);
static int NodeChildLeftOrRight(bst_node_t *node);
static bst_node_t *GoMostSide(bst_node_t *runner, int side);
static bst_iter_t InOrderTraversal(bst_iter_t iter, int side);
static void InitNode(bst_node_t *node, bst_node_t *parent, bst_node_t *left_son,
                     bst_node_t *right_son, void *data);
static void DestroyPostOrder(bst_node_t *node);

/******************** FUNCTIONS ********************/
bst_t *BSTCreate(cmp_func_t cmp_func)
{
	bst_t *tree = NULL;
	
	assert(cmp_func);

	tree = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == tree)
	{
		return (NULL);
	}

	tree->cmp_func = cmp_func;

	InitNode(&tree->root, NULL, NULL, NULL, NULL);
	
	return (tree);
}

void BSTDestroy(bst_t *bst)
{
	assert(bst);

	DestroyPostOrder(ACTUAL_ROOT);

	free(bst);
}

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_node_t *runner = NULL;

	assert(bst);

	runner = (bst_node_t *)&bst->root;
	
	runner = GoMostSide(runner, LEFT);
	
	return (NodeToIter(runner));
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	assert(bst);

	return (NodeToIter(((bst_node_t *)&bst->root)));
}

bst_iter_t BSTNext(bst_iter_t iter)
{
	assert(IterToNode(iter));

	return (InOrderTraversal(iter, RIGHT));
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	assert(IterToNode(iter));

	return (InOrderTraversal(iter, LEFT));
}

bst_iter_t BSTFind(const bst_t *bst, void *params)
{
	bst_node_t *curr = NULL;
	int cmp_status = 1;

	assert(bst);

	curr = ACTUAL_ROOT;

	while ((0 != cmp_status) && (NULL != curr))
	{
		cmp_status = bst->cmp_func(params, curr->data);

		if (0 > cmp_status)
		{
			curr = curr->children[LEFT];
		}
		
		if (0 < cmp_status)
		{
			curr = curr->children[RIGHT];
		}
	}
	
	return (NULL == curr ? NodeToIter(DUMMY) : NodeToIter(curr) );
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_node_t *curr = NULL;
	bst_node_t *prev = NULL;
	bst_node_t *new_node = NULL;
	int cmp_status = 1;
	int which_child_is_curr = 2;

	assert(bst);

	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return NodeToIter(DUMMY);
	}

	InitNode(new_node, NULL, NULL, NULL, data);

	if (BSTIsEmpty(bst))
	{
		bst->root.children[LEFT] = new_node;
		new_node->parent = &(bst->root);
		return (NodeToIter(new_node));
	}

	curr = ACTUAL_ROOT;

	while ((0 != cmp_status) && NULL != curr)
	{
		cmp_status = bst->cmp_func(data, curr->data);

		if (0 > cmp_status)
		{
			prev = curr;
			curr = curr->children[LEFT];
			which_child_is_curr = LEFT;
		}
		
		if (0 < cmp_status)
		{
			prev = curr;
			curr = curr->children[RIGHT];
			which_child_is_curr = RIGHT;
		}
	}

	assert(0 != cmp_status);
	assert(2 != which_child_is_curr);

	prev->children[which_child_is_curr] = new_node;
	new_node->parent = prev;

	return (NodeToIter(new_node));
}

void BSTRemove(bst_iter_t iter)
{
	bst_node_t *node = NULL;
	bst_node_t *next_node = NULL;
	int side_of_node = 0;
	int side_of_next = 0;
	int side_of_child = 0;

	assert(IterToNode(iter));

	node = IterToNode(iter);

	/* If node is leaf */
	if (NULL == node->children[LEFT] && NULL == node->children[RIGHT])
	{
		node->parent->children[NodeLeftOrRight(node)] = NULL;
	}
	/* node has one son */
	else if ((NULL == node->children[LEFT]) || (NULL == node->children[RIGHT]))
	{
		side_of_node = NodeLeftOrRight(node);
		side_of_child = NodeChildLeftOrRight(node);

		node->parent->children[side_of_node] = node->children[side_of_child];
		node->children[side_of_child]->parent = node->parent;
	}
	/* node has two sons */
	else
	{
		next_node = BSTNext(node);
		side_of_next = NodeLeftOrRight(next_node);

		next_node->parent->children[side_of_next] = next_node->children[RIGHT];

		if (NULL != next_node->children[RIGHT])
		{
			next_node->children[RIGHT]->parent = next_node->parent;
		}

		side_of_node = NodeLeftOrRight(node);

		node->parent->children[side_of_node] = next_node;
		next_node->parent = node->parent;

		next_node->children[LEFT] = node->children[LEFT];
		node->children[LEFT]->parent = next_node;

		if (NULL == node->children[RIGHT])
		{
			next_node->children[RIGHT] = NULL;
		}
		else
		{
			next_node->children[RIGHT] = node->children[RIGHT];
			node->children[RIGHT]->parent = next_node;
		}
	}

	free(node);
}

size_t BSTSize(const bst_t *bst)
{
	size_t count = 0;

	assert (bst);

	BSTForEach(BSTBegin(bst), BSTEnd(bst), AddOne, &count);

	return count;
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);

	return (NULL == ACTUAL_ROOT);
}

void *BSTGetData(bst_iter_t iter)
{
	bst_node_t *node = NULL;

	assert(IterToNode(iter));

	node = IterToNode(iter);

	return (node->data);
}

int BSTIsIterSame(bst_iter_t iter1, bst_iter_t iter2)
{
	bst_node_t *node1 = NULL;
	bst_node_t *node2 = NULL;
	
	assert(IterToNode(iter1));
	assert(IterToNode(iter2));

	node1 = IterToNode(iter1);
	node2 = IterToNode(iter2);

	return (node1 == node2);
}

int BSTForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func, void *params)
{
	int status = SUCCESS;

	assert(IterToNode(from));
	assert(IterToNode(to));

	while (!BSTIsIterSame(from ,to) && status == SUCCESS)
    {
        status = action_func(BSTGetData(from), params);
       
		from = BSTNext(from);
    }
    
    return (status);
}

/******************** HELPER FUNCTIONS ********************/
static bst_iter_t NodeToIter(const bst_node_t *node)
{
	return ((bst_iter_t)node);
}

static bst_node_t *IterToNode(bst_iter_t iter)
{
	return ((bst_node_t *)iter);
}

static int AddOne(void *data , void *count)
{	
	(void)data;
	
	*(size_t *)count = *(size_t *)count + 1;
	
	return (SUCCESS);
}

static int NodeLeftOrRight(bst_node_t *node)
{
	if (node == node->parent->children[LEFT])
	{
		return LEFT;
	}
	
	return RIGHT;
}

static int NodeChildLeftOrRight(bst_node_t *node)
{
	if (NULL == node->children[LEFT])
	{
		return RIGHT;
	}
	
	return LEFT;
}

static bst_node_t *GoMostSide(bst_node_t *runner, int side)
{
	while (NULL != runner->children[side])
	{
		runner = runner->children[side];
	}

	return runner;
}

static bst_iter_t InOrderTraversal(bst_iter_t iter, int side)
{
	bst_node_t *node = NULL;

	assert(IterToNode(iter));

	node = IterToNode(iter);

	if (NULL != node->children[side])
	{
		node = node->children[side];
		node = GoMostSide(node, !side);

		return (NodeToIter(node));
	}
	else
	{
		while (node == node->parent->children[side])
		{
			node = node->parent;
		}

		return (NodeToIter(node->parent));
	}
}

static void InitNode(bst_node_t *node, bst_node_t *parent, bst_node_t *left_son,
                     bst_node_t *right_son, void *data)
{   
    assert(node);

    node->parent = parent;
    node->children[LEFT] = left_son;
    node->children[RIGHT] = right_son;
    node->data = data;
}

static void DestroyPostOrder(bst_node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	DestroyPostOrder(node->children[LEFT]);
	DestroyPostOrder(node->children[RIGHT]);
	free(node);
}
