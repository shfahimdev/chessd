#ifndef MOVES_H
#define MOVES_H

#include "board/board.h"

typedef struct {
    int from;
    int to;
    int flags;
    int promotion_piece;
} Move;

// Move flags
#define MOVE_QUIET 0
#define MOVE_CAPTURE (1 << 0)
#define MOVE_EN_PASSANT (1 << 1)
#define MOVE_CASTLING (1 << 2)
#define MOVE_PROMOTION (1 << 3)
#define MOVE_DOUBLE_PUSH (1 << 4)

typedef enum {
    MOVE_OK,
    MOVE_INVALID_INPUT,
    MOVE_NO_PIECE,
    MOVE_WRONG_COLOR,
    MOVE_FRIENDLY_FIRE,
    MOVE_ILLEGAL,
} MoveResult;

int parse_move(const char *str, Move *out);
MoveResult make_move(Board *b, Move m);
void unmake_move(Board *b, Move m); // stub, Phase 4+

#endif
