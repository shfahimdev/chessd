#include "board.h"
#include <stdio.h>

int main(void) {
    Board game;         /* Declare a Board on the stack */
    board_init(&game);  /* Pass its address so board_init can fill it in */
    board_print(&game); /* Print it */
    return 0;           /* 0 = success (convention on all Unix systems) */
}
