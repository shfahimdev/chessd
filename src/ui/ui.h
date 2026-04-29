#ifndef UI_H
#define UI_H

#include "board/board.h"
#include "moves/moves.h"

void board_print(const Board *b);
int read_move(char *buf, int bufsize);
void print_move_result(MoveResult r);

#endif
