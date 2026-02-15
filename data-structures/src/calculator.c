/*
Owner: Uri Naor
Date: Mar 20, 2024
*/

#include <stdio.h>
#include <stdlib.h> /* malloc, strtod*/
#include <assert.h> /* assert */
#include <math.h> /* pow */

#include "calculator.h"
#include "stack.h"

#define ASCII_SIZE (128)
#define STATES_NUM (4)
#define PREV_OPER (((operator_t *)StackPeek(calc->operators)))

/******************** STRUCTS & ENUMS ********************/
typedef enum states
{
    WAITING_FOR_NUM = 0,
    WAITING_FOR_OPER = 1,
    ERROR = 2,
    FINAL_STATE = 3
} states_t;

typedef enum priority
{
    VERY_LOW = 0,
    LOW = 1,
    MID = 2,
    HIGH = 3
} priority_t;

typedef struct operator
{
    char oper;
    priority_t priority;
    calc_status_t (*action)(double num1, double num2, double *res);
} operator_t;

typedef struct calc
{
    stack_t *numbers;
    stack_t *operators;
    states_t current_state;
    char *runner;
    double res;
} calc_t;

/******************** GLOBAL VARS ********************/
typedef calc_status_t (*action_func)(calc_t *calc);

action_func state_lut[STATES_NUM][ASCII_SIZE] = {0};
operator_t operator_lut[ASCII_SIZE] = {0};

/******************** FORWARD DECLARATIONS ********************/
static calc_t *CreateCalc(char *expression);
static void DestroyCalc(calc_t *calc);
static void InitStateLUT();
static void InitOperatorLUT();

static calc_status_t Multiply(double num1, double num2, double *res);
static calc_status_t Add(double num1, double num2, double *res);
static calc_status_t Subtract(double num1, double num2, double *res);
static calc_status_t Divide(double num1, double num2, double *res);
static calc_status_t Power(double num1, double num2, double *res);

static calc_status_t NumHandler(calc_t *calc);
static calc_status_t OperatorHandler(calc_t *calc);
static calc_status_t ErrorHandler(calc_t *calc);
static calc_status_t WhiteSpaceHandler(calc_t *calc);
static calc_status_t FinalHandler(calc_t *calc);
static calc_status_t OpenBracHandler(calc_t *calc);
static calc_status_t CloseBracHandler(calc_t *calc);

/******************** FUNCTIONS ********************/
calc_status_t Calculator(const char *str, double *res)
{
    calc_t *calc = NULL;
    char *expression = NULL;
    calc_status_t status = SUCCESS;

    assert(str);

    expression = (char *)str;

    calc = CreateCalc(expression);
    if (NULL == calc)
    {
        return MEMORY_ERR;
    }

    while (calc->current_state != FINAL_STATE && SUCCESS == status)
    {
        status = state_lut[calc->current_state][(unsigned char)*calc->runner](calc);
    }

    *res = calc->res;

    DestroyCalc(calc);

    return status;
}

/******************** HELPER FUNCTIONS ********************/
static calc_t *CreateCalc(char *expression)
{
    calc_t *calc = NULL;
    stack_t *oper_stack = NULL;
    stack_t *nums_stack = NULL;

    assert(expression);

    calc = (calc_t *)calloc(1, sizeof(calc_t));
    if (NULL == calc)
    {
        return NULL;
    }

    oper_stack = StackCreate(100, sizeof(operator_t));
    if (NULL == oper_stack)
    {
        free(calc);
        return (NULL);
    }
    
    nums_stack = StackCreate(100, sizeof(double));

    if (NULL == nums_stack)
    {
        free(calc);
        StackDestroy(oper_stack); 

        return (NULL);
    }

    InitStateLUT();
    InitOperatorLUT();

    calc->current_state = WAITING_FOR_NUM;
    calc->numbers = nums_stack;
    calc->operators = oper_stack;
    calc->runner = expression;

    return calc;
}

static void DestroyCalc(calc_t *calc) 
{
    assert(calc);

    StackDestroy(calc->numbers);
    StackDestroy(calc->operators);

    free(calc);
}

static void InitStateLUT()
{
    char ch = '0';
    int i = 0;
    int j = 0;

    /* all undefined characters lead to error */
    for (i = 0; i < STATES_NUM; i++)
    {
        for (j = 0; j < ASCII_SIZE; j++)
        {
            state_lut[i][j] = ErrorHandler;
        }
    }

    for (ch = '0'; ch <= '9'; ch++)
    {
        state_lut[WAITING_FOR_NUM][(unsigned char)ch] = NumHandler;
    }

    state_lut[WAITING_FOR_NUM]['+'] = NumHandler;
    state_lut[WAITING_FOR_NUM]['-'] = NumHandler;
    state_lut[WAITING_FOR_NUM]['('] = OpenBracHandler;
    state_lut[WAITING_FOR_NUM][' '] = WhiteSpaceHandler;
    state_lut[WAITING_FOR_OPER]['\0'] = FinalHandler;

    state_lut[WAITING_FOR_OPER]['+'] = OperatorHandler;
    state_lut[WAITING_FOR_OPER]['-'] = OperatorHandler;
    state_lut[WAITING_FOR_OPER]['*'] = OperatorHandler;
    state_lut[WAITING_FOR_OPER]['/'] = OperatorHandler;
    state_lut[WAITING_FOR_OPER]['^'] = OperatorHandler;
    state_lut[WAITING_FOR_OPER][' '] = WhiteSpaceHandler;
    state_lut[WAITING_FOR_OPER][')'] = CloseBracHandler;
}

static void InitOperatorLUT()
{
    operator_lut['('].oper = '(';
    operator_lut['('].priority = VERY_LOW;
    operator_lut['('].action = NULL;

    operator_lut['+'].oper = '+';
    operator_lut['+'].priority = LOW;
    operator_lut['+'].action = Add;

    operator_lut['-'].oper = '-';
    operator_lut['-'].priority = LOW;
    operator_lut['-'].action = Subtract;

    operator_lut['*'].oper = '*';
    operator_lut['*'].priority = MID;
    operator_lut['*'].action = Multiply;

    operator_lut['/'].oper = '/';
    operator_lut['/'].priority = MID;
    operator_lut['/'].action = Divide;
    
    operator_lut['^'].oper = '^';
    operator_lut['^'].priority = HIGH;
    operator_lut['^'].action = Power;
}

/********************** HANDLERS *********************/
static calc_status_t NumHandler(calc_t *calc)
{
    char *end_ptr = NULL;
    double number = 0;

    number = strtod(calc->runner, &end_ptr);

    StackPush(calc->numbers, &number);

    calc->runner = end_ptr;
    calc->current_state = WAITING_FOR_OPER;

    return (SUCCESS);
}

static calc_status_t OperatorHandler(calc_t *calc)
{
    operator_t curr_oper;
    double num1 = 0;
    double num2 = 0;
    double res = 0;
    calc_status_t status = SUCCESS;

    assert(calc);

    curr_oper = operator_lut[(unsigned char)*calc->runner];

    while (!StackIsEmpty(calc->operators) &&
          (PREV_OPER->priority >= curr_oper.priority))
    {
        num2 = *(double *)StackPeek(calc->numbers);
        StackPop(calc->numbers);
        num1 = *(double *)StackPeek(calc->numbers);
        StackPop(calc->numbers);

        status = PREV_OPER->action(num1, num2, &res);

        StackPop(calc->operators);

        StackPush(calc->numbers, &res);
    }

    StackPush(calc->operators, &curr_oper);

    calc->runner++;
    calc->current_state = WAITING_FOR_NUM;

    return (status);
}

static calc_status_t ErrorHandler(calc_t *calc)
{
    assert(calc);

    calc->current_state = ERROR;
    calc->res = 0;

    return (SYNTAX_ERR);
}

static calc_status_t WhiteSpaceHandler(calc_t *calc)
{
    calc->runner++;

    return (SUCCESS);
}

static calc_status_t FinalHandler(calc_t *calc)
{
    double num1 = 0;
    double num2 = 0;
    double res = 0;
    calc_status_t status = SUCCESS;

    assert(calc);

    if (StackSize(calc->numbers) <= StackSize(calc->operators))
    {
        return SYNTAX_ERR;
    }

    while (!StackIsEmpty(calc->operators) && status == SUCCESS)
    {
        if (NULL == PREV_OPER->action)
        {
            return SYNTAX_ERR;
        }

        num2 = *(double *)StackPeek(calc->numbers);
        StackPop(calc->numbers);
        num1 = *(double *)StackPeek(calc->numbers);
        StackPop(calc->numbers);

        status = PREV_OPER->action(num1, num2, &res);

        StackPop(calc->operators);

        StackPush(calc->numbers, &res);
    }

    calc->res = (status == SUCCESS) ? *(double *)StackPeek(calc->numbers) : 0;

    calc->current_state = FINAL_STATE;

    return (status);
}

static calc_status_t OpenBracHandler(calc_t *calc)
{
    assert(calc);

    StackPush(calc->operators, &operator_lut[(unsigned char)*calc->runner]);
    calc->current_state = WAITING_FOR_NUM;

    calc->runner++;

    return (SUCCESS);
}

static calc_status_t CloseBracHandler(calc_t *calc)
{
    double num1 = 0;
    double num2 = 0;
    double res = 0;
    calc_status_t status = SUCCESS;
    operator_t *oper = (operator_t *)StackPeek(calc->operators);

    assert(calc);

    while (!StackIsEmpty(calc->operators) && oper->priority != 0)
    {
        num2 = *(double *)StackPeek(calc->numbers);
        StackPop(calc->numbers);
        num1 = *(double *)StackPeek(calc->numbers);
        StackPop(calc->numbers);

        status = PREV_OPER->action(num1, num2, &res);

        StackPop(calc->operators);

        StackPush(calc->numbers, &res);

        oper = (operator_t *)StackPeek(calc->operators);
    }

    if (StackIsEmpty(calc->operators))
    {
        status = ErrorHandler(calc);
    }
    else
    {
        StackPop(calc->operators);
    }

    calc->runner++;

    return (status);
}

/******************** MATH OPERATIONS ********************/
static calc_status_t Multiply(double num1, double num2, double *res)
{
    *res = num1 * num2;

    return (SUCCESS);
}

static calc_status_t Add(double num1, double num2, double *res)
{
    *res = num1 + num2;

    return (SUCCESS);
}

static calc_status_t Subtract(double num1, double num2, double *res)
{
    *res = num1 - num2;

    return (SUCCESS);
}

static calc_status_t Divide(double num1, double num2, double *res)
{
    if (0 == num2)
    {
        return (MATH_ERR);
    }

    *res = num1 / num2;

    return (SUCCESS);
}

static calc_status_t Power(double num1, double num2, double *res)
{
    *res = pow(num1, num2);

    return (SUCCESS);
}
