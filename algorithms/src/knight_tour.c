/*
Owner: Uri Naor
Date: Apr 2, 2024
*/

#include <time.h> /* time() */
#include <assert.h> /* assert() */

#include "knight_tour.h" /* KnightTour() */
#include "bitarr.h" /* bitarr_t */

#define SQUARES_NUM (64)
#define BOARD_ROW_LENGTH (8)
#define INVALID_MOVE (-1)
#define IS_VALID_POSITION(x, y) ((x) >= 0 && (y) >= 0 && \
(x) < BOARD_ROW_LENGTH && (y) < BOARD_ROW_LENGTH)
#define NEXT_MOVE (possible_moves_lut[possible_moves_lut[starting_pos][i]][j])

/*
numbering of chest board:
     0  1  2  3  4  5  6  7
     8  9 10 11 12 13 14 15
    16 17 18 19 20 21 22 23
    24 25 26 27 28 29 30 31
    32 33 34 35 36 37 38 39
    40 41 42 43 44 45 46 47
    48 49 50 51 52 53 54 55
    56 57 58 59 60 61 62 63

    pseudo:
    1. init a LUT to keep track of possible squares from current square
    2. mark each square visited on the board
    3. brute force all possible solutions with backtracking

    we will mark with 100 that a square has been visited.

    how to calculate square_num to row and col:
    row = square_num / 8
    col = square_num % 8

    how to calculate row & col into square num:
    square_num = (row * 8) + col
*/

/******************** FORWARD DECLARATIONS ********************/
static void InitMovesLUT();
static status_t KnightTourRecursive(
    unsigned char starting_pos, 
    unsigned char *path, 
    size_t time_out, 
    int is_heuristic,
    int recursion_depth,
    bitarr_t board,
    size_t start_time
);
static void CalculateNextMoves(
    unsigned char starting_pos, 
    int *next_possible_moves, 
    bitarr_t board
);
static void SortLUT(
    unsigned char starting_pos, 
    int *next_possible_moves);

/******************** GLOBAL VARS ********************/
static int possible_moves_lut[SQUARES_NUM][BOARD_ROW_LENGTH] = {0};

/******************** FUNCTIONS ********************/
status_t KnightTour(
    unsigned char starting_pos, 
    unsigned char *path, 
    size_t time_out, 
    int is_heuristic)
{
    bitarr_t board = 0;
    size_t start_time = time(NULL);
    int recursion_depth = 0;

    board = BitArrSetOn(board, starting_pos);
    path[recursion_depth] = starting_pos;
    ++recursion_depth;

    assert(path);
    assert(starting_pos < SQUARES_NUM);

    InitMovesLUT();

    return (KnightTourRecursive(starting_pos, path, time_out, is_heuristic,
                                recursion_depth, board, start_time));


}

/******************** HELPER FUNCTIONS ********************/
static status_t KnightTourRecursive(
    unsigned char starting_pos, 
    unsigned char *path, 
    size_t time_out, 
    int is_heuristic,
    int recursion_depth,
    bitarr_t board,
    size_t start_time)
{
    size_t i = 0;
    status_t status = SUCCESS;
    int next_possible_moves[BOARD_ROW_LENGTH] = {0};

    if ((size_t)(time(NULL) - start_time) >= time_out)
    {
        return (OUT_OF_TIME);
    }

    if (recursion_depth == SQUARES_NUM)
    {
        return SUCCESS;
    }

    if (is_heuristic)
    {
        CalculateNextMoves(starting_pos, next_possible_moves, board);
        SortLUT(starting_pos, next_possible_moves);
    }

    for (i = 0; i < BOARD_ROW_LENGTH; i++)
    {
        if (possible_moves_lut[starting_pos][i] != INVALID_MOVE && 
           BitArrGetBit(board, possible_moves_lut[starting_pos][i]) != 1)
        {
            board = BitArrSetOn(board, possible_moves_lut[starting_pos][i]);
            path[recursion_depth] = possible_moves_lut[starting_pos][i];
            status = KnightTourRecursive
            (
                possible_moves_lut[starting_pos][i], 
                path, 
                time_out, 
                is_heuristic, 
                recursion_depth + 1, 
                board, 
                start_time
            );

            if (FAILURE == status)
            {
                board = BitArrSetOff(board,possible_moves_lut[starting_pos][i]);
                path[recursion_depth] = 0;
            }

            else
            {
                return status;
            }
        }
    }

    return (FAILURE);
}

static void InitMovesLUT()
{
    int x[BOARD_ROW_LENGTH] = {2, 1, -1, -2, -2, -1, 1, 2};
    int y[BOARD_ROW_LENGTH] = {1, 2, 2, 1, -1, -2, -2, -1};
    int row = 0, col = 0, newRow = 0, newCol = 0;

    size_t i = 0, j = 0;

    for (i = 0; i < SQUARES_NUM; ++i)
    {
        row = i / 8;
        col = i % 8;

        for (j = 0; j < BOARD_ROW_LENGTH; ++j)
        {
            newRow = row + x[j];
            newCol = col + y[j];

            possible_moves_lut[i][j] = IS_VALID_POSITION(newRow, newCol) ? 
                                         newRow * 8 + newCol : -1;
        }
    }
}

static void CalculateNextMoves(
    unsigned char starting_pos, 
    int *next_possible_moves, 
    bitarr_t board)
{
    size_t i = 0;
    int count = 0;
    size_t j = 0;

    for (i = 0; i < BOARD_ROW_LENGTH; i++)
    {
        /* check if the move is valid and hasn't been visited */
        if (possible_moves_lut[starting_pos][i] != INVALID_MOVE &&
           BitArrGetBit(board, possible_moves_lut[starting_pos][i]) != 1)
        {
            count = 0;
            /* count the number of possible next moves from the current move */
            for (j = 0; j < BOARD_ROW_LENGTH; j++)
            {
                /* count if the next move is valid and hasn't been visited */
                if (NEXT_MOVE != INVALID_MOVE && 
                    BitArrGetBit(board, NEXT_MOVE) != 1)
                {
                    count++;
                }
            }
            next_possible_moves[i] = count;
        }
        /* else mark the move as invalid */
        else
        {
            next_possible_moves[i] = INVALID_MOVE;
        }
    }
}

static void SortLUT(unsigned char starting_pos, int *next_possible_moves)
{
    size_t i = 0;
    size_t j = 0;
    int temp_move = 0;
    int temp_count = 0;

    /* bubble sort based on the number of possible next moves */
    for (i = 0; i < BOARD_ROW_LENGTH - 1; i++)
    {
        for (j = 0; j < BOARD_ROW_LENGTH - i - 1; j++)
        {
            if (next_possible_moves[j] > next_possible_moves[j + 1])
            {
                temp_move = possible_moves_lut[starting_pos][j];
                temp_count = next_possible_moves[j];

                possible_moves_lut[starting_pos][j] 
                    = possible_moves_lut[starting_pos][j + 1];

                next_possible_moves[j] = next_possible_moves[j + 1];

                possible_moves_lut[starting_pos][j + 1] = temp_move;
                next_possible_moves[j + 1] = temp_count;
            }
        }
    }
}