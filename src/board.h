#ifndef BOARD_H /* include guard — prevents this file being included twice */
#define BOARD_H

/*
 * Piece encoding:
 *
 * We use plain integers. The sign encodes color:
 *   positive = White
 *   negative = Black
 *   zero     = empty square
 *
 * The value encodes the piece type:
 *   1 = Pawn
 *   2 = Knight
 *   3 = Bishop
 *   4 = Rook
 *   5 = Queen
 *   6 = King
 *
 * So:
 *   +4 = White Rook
 *   -6 = Black King
 *    0 = empty
 */

#define EMPTY 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6

/*
 * The board itself.
 * board[row][col]
 * row 0 = rank 8 (Black's back rank, top of board)
 * row 7 = rank 1 (White's back rank, bottom of board)
 */
typedef struct {
    int squares[8][8];
} Board;

/* Function declarations */
void board_init(Board *b);
void board_print(const Board *b);

#endif /* BOARD_H */
