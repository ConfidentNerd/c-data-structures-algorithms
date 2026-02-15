/*
Owner: Uri Naor
Date: Mar 24, 2024
*/

#include <stdlib.h> /* malloc, size_t */
#include <assert.h> /* assert */

#include "avl.h"

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

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

enum
{
    LEFT_UNBALANCE = 1,
    RIGHT_UNBALANCE = -1
};

/******************** STRUCTS ********************/
typedef struct avl_node avl_node_t;

struct avl_node
{
    void *data;
    avl_node_t *children[NUM_OF_CHILDREN];
    size_t height;
};

struct tree
{
    avl_node_t *root;
    cmp_func_t cmp_func;
};

/******************** FORWARD DECLARATIONS ********************/
static void *AVLFindHelper(const avl_t *avl, const void *data, avl_node_t *node);
static int AVLForEachPreOrder(avl_t *avl, action_func_t action_func, 
                              void *params, avl_node_t *node);
static int AVLForEachInOrder(avl_t *avl, action_func_t action_func, 
                              void *params, avl_node_t *node);
static int AVLForEachPostOrder(avl_t *avl, action_func_t action_func, 
                              void *params, avl_node_t *node);
static int AddOne(void *data , void *count);
static void AVLDestroyWithNode(avl_t *avl, avl_node_t *node);
static int Height(avl_node_t *node);
static avl_node_t *AVLInsertHelper(avl_t *avl, void *data, avl_node_t *node, avl_node_t *new_node);
static void InitNode(avl_node_t *new_node, avl_node_t *left_child, 
                     avl_node_t *right_child, void* data, size_t height);
static avl_node_t *AVLRemoveHelper(avl_t *avl, void *data, avl_node_t *node);
static void *GetSmallestData(avl_node_t *node);
static void UpdateHeight(avl_node_t *node);
static avl_node_t *Rotate(avl_node_t *node, int side);
static avl_node_t *Balance(avl_node_t *node);
static int GetBalance(avl_node_t* node);

/******************** FUNCTIONS ********************/
avl_t *AVLCreate(cmp_func_t cmp_func)
{
	avl_t *tree = NULL;
	
	assert(cmp_func);

	tree = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == tree)
	{
		return (NULL);
	}

	tree->cmp_func = cmp_func;
    tree->root = NULL;
	
	return (tree);
}

void AVLDestroy(avl_t *avl)
{
    assert(avl);

    AVLDestroyWithNode(avl, avl->root);

    free(avl);
}

int AVLInsert(avl_t *avl, void *data)
{
    avl_node_t *new_node = NULL;

    assert(avl);
    assert(data);

    new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
    if (NULL == new_node)
    {
        return 1;
    }

    InitNode(new_node, NULL, NULL, data, 0);

    avl->root = AVLInsertHelper(avl, data, avl->root, new_node);

    return 0;
}

void AVLRemove(avl_t *avl, void *data)
{
    avl_node_t *new_root = NULL;

    assert(avl);

    new_root = AVLRemoveHelper(avl, data, avl->root);

    avl->root = new_root;
}

void *AVLFind(const avl_t *avl, const void *data)
{
    assert (avl);

    return (AVLFindHelper(avl, data, avl->root));
}

size_t AVLSize(const avl_t *avl)
{
    size_t count = 0;

    assert(avl);

    AVLForEach((avl_t *)avl, AddOne, &count, PRE_ORDER);

    return count;
}

int AVLIsEmpty(const avl_t *avl)
{
    assert(avl);

    return (NULL == avl->root ? 1 : 0 );
}

int AVLForEach(avl_t *avl, action_func_t action_func, void *params, 
               traversal_order_t order)
{
    int status = 0;
    assert(avl);
    assert(action_func);
    
    switch(order)
    {
        case PRE_ORDER: 
            status = (AVLForEachPreOrder(avl, action_func, params, avl->root));
            break;
        case IN_ORDER:
            status = (AVLForEachInOrder(avl, action_func, params, avl->root));
            break;
        case POST_ORDER:
            status = (AVLForEachPostOrder(avl, action_func, params, avl->root));
            break;
    }

    return (status);
}

size_t AVLHeight(const avl_t *avl)
{
    assert (avl);

    if (avl->root == NULL)
    {
        return 0;
    }

    return avl->root->height;
}

/******************** HELPER FUNCTIONS ********************/
static avl_node_t *AVLRemoveHelper(avl_t *avl, void *data, avl_node_t *node)
{
    int cmp_status = 0;
    avl_node_t *temp = NULL;

    if (NULL == node)
    {
        return NULL;
    }

    cmp_status = avl->cmp_func(node->data, data);

    if (0 == cmp_status)
    {
        /* if leaf*/
        if ((NULL == node->children[LEFT]) && (NULL == node->children[RIGHT]))
        {
            free(node);
            return NULL;
        }
         /* if only left child */
        else if (NULL == node->children[RIGHT])
        {
            temp = node->children[LEFT];
            free(node);
            return temp;
        }
        /* if only right child */
        else if (NULL == node->children[LEFT])
        {
            temp = node->children[RIGHT];
            free(node);
            return temp;
        }

        node->data = GetSmallestData(node->children[RIGHT]);
        node->children[RIGHT] = AVLRemoveHelper(avl, node->data, node->children[RIGHT]);
    }
    else
    {
        node->children[cmp_status < 0] = AVLRemoveHelper(avl, data, node->children[cmp_status < 0]);
    }

    UpdateHeight(node);

    return Balance(node);
}

static void *GetSmallestData(avl_node_t *node)
{
    assert(node);

    if (NULL == node->children[LEFT])
    {
        return (node->data);
    }

    node = node->children[LEFT];

    return (GetSmallestData(node));
}


static avl_node_t *AVLInsertHelper(avl_t *avl, void *data, avl_node_t *node, avl_node_t *new_node)
{
    int side = 0;
    int cmp_status = 0;

    if (NULL == node)
    {
        return new_node;
    }

    cmp_status = avl->cmp_func(node->data, data);

    assert(cmp_status != 0);

    if (cmp_status > 0)
    {
        side = LEFT;
    }
    else
    {
        side = RIGHT;
    }

    node->children[side] = AVLInsertHelper(avl, data, node->children[side], new_node);

    UpdateHeight(node);

    return Balance(node);
}

/* function to get the height of a node (handles NULL nodes) */
static int Height(avl_node_t *node)
{
    if (node == NULL)
    {
        return -1;
    }
    
    return ((int)node->height);
}

static void *AVLFindHelper(const avl_t *avl, const void *data, avl_node_t *node)
{
    int cmp_status = 0;

    if (NULL == node)
    {
        return NULL;
    }

    /* Consistently pass node->data (avl_data) then data (user_data) 
       to align with cmp_func signature */
    cmp_status = avl->cmp_func(node->data, data);

    /* if we found match return data */
    if (0 == cmp_status)
    {
        return (node->data);
    }
    /* if node is leaf return NULL */
    if (NULL == node->children[LEFT] && NULL == node->children[RIGHT])
    {
        return NULL;
    }

    if (cmp_status > 0)
    {
        return AVLFindHelper(avl, data, node->children[LEFT]);
    }
    else
    {
        return AVLFindHelper(avl, data, node->children[RIGHT]);
    }
}

static int AVLForEachPreOrder(avl_t *avl, action_func_t action_func, 
                              void *params, avl_node_t *node)
{
    int status = 0;

    if (node == NULL)
    {
        return status;
    }

    status = action_func(node->data, params);
    if (0 != status)
    {
        return status;
    }

    status = AVLForEachPreOrder(avl, action_func, params, node->children[LEFT]);
    if (0 != status)
    {
        return status;
    }

    status = AVLForEachPreOrder(avl, action_func, params, node->children[RIGHT]);
    if (0 != status)
    {
        return status;
    }

    return status;
}

static int AVLForEachInOrder(avl_t *avl, action_func_t action_func, 
                              void *params, avl_node_t *node)
{
    int status = 0;

    if (node == NULL)
    {
        return status;
    }

    status = AVLForEachInOrder(avl, action_func, params, node->children[LEFT]);
    if (0 != status)
    {
        return status;
    }

    status = action_func(node->data, params);
    if (0 != status)
    {
        return status;
    }

    status = AVLForEachInOrder(avl, action_func, params, node->children[RIGHT]);
    if (0 != status)
    {
        return status;
    }

    return status;
}

static int AVLForEachPostOrder(avl_t *avl, action_func_t action_func, 
                              void *params, avl_node_t *node)
{
    int status = 0;

    if (node == NULL)
    {
        return status;
    }

    status = AVLForEachPostOrder(avl, action_func, params, node->children[LEFT]);
    if (0 != status)
    {
        return status;
    }

    status = AVLForEachPostOrder(avl, action_func, params, node->children[RIGHT]);
    if (0 != status)
    {
        return status;
    }

    status = action_func(node->data, params);
    if (0 != status)
    {
        return status;
    }

    return status;
}

static int AddOne(void *data , void *count)
{	
	(void)data;
	
	*(size_t *)count = *(size_t *)count + 1;
	
	return (0);
}

static void AVLDestroyWithNode(avl_t *avl, avl_node_t *node)
{
    if (node == NULL)
    {
        return;
    }

    AVLDestroyWithNode(avl, node->children[LEFT]);
    AVLDestroyWithNode(avl, node->children[RIGHT]);

    free(node);
}

static void InitNode(avl_node_t *new_node, avl_node_t *left_child, 
                     avl_node_t *right_child, void* data, size_t height)
{
    assert(new_node);

        new_node->children[LEFT] = NULL;
        new_node->children[RIGHT] = NULL;
        new_node->data = data;
        new_node->height = height;
}

static avl_node_t *Rotate(avl_node_t *node, int side)
{
    avl_node_t *new_root = NULL;
    int opposite_side = !side;

    assert(node);

    new_root = node->children[opposite_side];

    /* in case of right-left or left-right rotations. */
    if ((side == LEFT && GetBalance(new_root) > 0) ||
        (side == RIGHT && GetBalance(new_root) < 0))
    {
        new_root = new_root->children[side];
        node->children[opposite_side]->children[side] = new_root->children[opposite_side];
        new_root->children[opposite_side] = node->children[opposite_side];
    }
    
    /* right / left rotation */
    node->children[opposite_side] = new_root->children[side];
    new_root->children[side] = node;

    UpdateHeight(node);
    UpdateHeight(new_root->children[opposite_side]);
    UpdateHeight(new_root);

    return (new_root);
}

static avl_node_t *Balance(avl_node_t *node)
{
    int balance_status = 0;

    balance_status = GetBalance(node);

    if (balance_status > LEFT_UNBALANCE)
    {
        node = Rotate(node, RIGHT);
    }
    else if (balance_status < RIGHT_UNBALANCE)
    {
        node = Rotate(node, LEFT);
    }

    return (node);
}

static int GetBalance(avl_node_t* node)
{
    if (NULL == node)
    {
        return 0;
    }

    return (Height(node->children[LEFT]) - Height(node->children[RIGHT]));
}

static void UpdateHeight(avl_node_t *node)
{
    size_t left_height = 0;
    size_t right_height = 0;

    if (NULL == node)
    {
        return;
    }
    
    /* if no children */
    if(NULL == node->children[LEFT] && NULL == node->children[RIGHT])
    {
        node->height = 0;
    }
    /* if there is a left child */
    else
    {
        if (NULL != node->children[LEFT])
        {
            left_height = node->children[LEFT]->height;
        }

        /* if there is a right child */
        if (NULL != node->children[RIGHT])
        {
            right_height = node->children[RIGHT]->height;
        }

        node->height = 1 + MAX(left_height, right_height);
    }
}
