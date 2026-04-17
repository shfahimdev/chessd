#include "board.h"
#include <stdio.h> /* printf */

/*
 * board_init — set up the starting position
 *
 * We receive a pointer to a Board (not the Board itself) because:
 * - We want to MODIFY the board the caller owns
 * - Passing by value would give us a copy; changes wouldn't be visible outside
 */
void board_init(Board *b) {

    /* --- White pieces (positive values) on rows 6 and 7 --- */

    /* Row 7: White's back rank */
    b->squares[7][0] = ROOK;
    b->squares[7][1] = KNIGHT;
    b->squares[7][2] = BISHOP;
    b->squares[7][3] = QUEEN;
    b->squares[7][4] = KING;
    b->squares[7][5] = BISHOP;
    b->squares[7][6] = KNIGHT;
    b->squares[7][7] = ROOK;

    /* Row 6: White pawns */
    for (int col = 0; col < 8; col++) {
        b->squares[6][col] = PAWN;
    }

    /* --- Empty squares: rows 2–5 --- */
    for (int row = 2; row <= 5; row++) {
        for (int col = 0; col < 8; col++) {
            b->squares[row][col] = EMPTY;
        }
    }

    /* --- Black pieces (negative values) on rows 0 and 1 --- */

    /* Row 1: Black pawns */
    for (int col = 0; col < 8; col++) {
        b->squares[1][col] = -PAWN;
    }

    /* Row 0: Black's back rank */
    b->squares[0][0] = -ROOK;
    b->squares[0][1] = -KNIGHT;
    b->squares[0][2] = -BISHOP;
    b->squares[0][3] = -QUEEN;
    b->squares[0][4] = -KING;
    b->squares[0][5] = -BISHOP;
    b->squares[0][6] = -KNIGHT;
    b->squares[0][7] = -ROOK;
}

/*
 * piece_char — return the display character for a piece value
 *
 * We use uppercase for White, lowercase for Black.
 * This is standard in text-based chess (FEN notation).
 *
 * 'static' means this function is private to this file.
 * No other .c file can call it. Good practice for helpers.
 */
static char piece_char(int piece) {
    /* Map each piece type to its letter */
    char white[] = {'.', 'P', 'N', 'B', 'R', 'Q', 'K'};
    char black[] = {'.', 'p', 'n', 'b', 'r', 'q', 'k'};

    if (piece > 0)
        return white[piece]; /* positive = white */
    if (piece < 0)
        return black[-piece]; /* negative = black; negate to index */
    return '.';               /* zero = empty */
}

/*
 * board_print — draw the board to stdout
 */
void board_print(const Board *b) {
    /* Print column labels at the top */
    printf("\n    a   b   c   d   e   f   g   h\n");
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int row = 0; row < 8; row++) {
        /* Rank number on the left. Rank 8 is row 0, rank 1 is row 7. */
        printf("%d |", 8 - row);

        for (int col = 0; col < 8; col++) {
            printf(" %c |", piece_char(b->squares[row][col]));
        }

        /* Rank number on the right too */
        printf(" %d\n", 8 - row);
        printf("  +---+---+---+---+---+---+---+---+\n");
    }

    printf("    a   b   c   d   e   f   g   h\n\n");
}
