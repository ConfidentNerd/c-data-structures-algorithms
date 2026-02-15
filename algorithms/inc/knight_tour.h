/*
Owner: Uri Naor
Date: Apr 2, 2024

Knight's Tour

Description:
This library solves the Knight's Tour problem: finding a sequence of moves 
for a knight on a chessboard such that the knight visits every square exactly once.
It utilizes recursive backtracking and optionally applies Warnsdorff's heuristic 
to drastically optimize the search time.
*/

#ifndef KNIGHT_TOUR_H 
#define KNIGHT_TOUR_H

#include <stddef.h> /* size_t */ 

typedef enum status
{
    SUCCESS = 0,
    OUT_OF_TIME = 1,
    FAILURE = 2
} status_t;

/* Complexity: Time: O(8^N) brute-force, ~O(N) with Warnsdorff's | Space: O(N) */
/* (Where 'N' is the total number of squares on the chessboard, e.g., 64)      */
/******************************************************************************/
/* Description:  The function finds and writes a full knight's tour into the  */
/* path array, with each index representing a position visited. */
/* Arguments:    starting_pos - The starting position of the knight (0 to 63) */
/* path - The output array which the path will be written to    */
/* time_out - Maximum time given to find path in seconds        */
/* is_heuristic - Flag (1 or 0) to enable Warnsdorff's heuristic*/
/* Return value: SUCCESS (0) if a path is found, OUT_OF_TIME (1) if it times  */
/* out, or FAILURE (2) if no path exists.                       */
/******************************************************************************/
status_t KnightTour(unsigned char starting_pos, 
                    unsigned char *path, 
                    size_t time_out, 
                    int is_heuristic);

#endif /* KNIGHT_TOUR_H */