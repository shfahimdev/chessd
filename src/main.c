#include "board/board.h"
#include "moves/moves.h"
#include "ui/ui.h"

int main(void) {
    Board b;
    board_init(&b);
    board_print(&b);

    while (1) {
        char buf[10];
        if (!read_move(buf, sizeof(buf)))
            break;

        Move m;
        if (!parse_move(buf, &m)) {
            print_move_result(MOVE_INVALID_INPUT);
            continue;
        }

        MoveResult result = make_move(&b, m);
        print_move_result(result);

        if (result == MOVE_OK)
            board_print(&b);
    }

    return 0;
}
