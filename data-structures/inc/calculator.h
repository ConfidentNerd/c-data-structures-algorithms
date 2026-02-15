/*
Owner: Uri Naor
Date: Mar 20, 2024

Calculator

Description:
This library provides a mathematical expression calculator that supports 
basic arithmetic operations (+, -, *, /), power (^), and parentheses (). 
The calculator uses a Shunting-yard algorithm variant implemented with 
finite-state machines and stacks.
*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef enum status
{
    SUCCESS = 0,
    SYNTAX_ERR = 1,
    MATH_ERR = 2,
    MEMORY_ERR = 3
} calc_status_t;

/******************************************************************************/
/* Description:  Evaluates a mathematical expression provided as a string     */
/* Arguments:    str - a pointer to a null-terminated string containing the    */
/*                     mathematical expression                                */
/*               res - a pointer to a double where the result will be stored  */
/* Return value: returns SUCCESS (0) if evaluation was successful,            */
/*               otherwise returns an error code:                             */
/*               SYNTAX_ERR - if the expression is malformed                  */
/*               MATH_ERR - for mathematical errors (e.g., division by zero)  */
/*               MEMORY_ERR - if memory allocation failed during evaluation   */
/******************************************************************************/
calc_status_t Calculator(const char *str, double *res);

#endif /* CALCULATOR_H */
