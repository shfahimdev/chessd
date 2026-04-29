#include "ui.h"
#include <stdio.h>

static const char *piece_symbol(int piece) {
    switch (piece) {
    case 1:
        return "♙";
    case 2:
        return "♖";
    case 3:
        return "♘";
    case 4:
        return "♗";
    case 5:
        return "♕";
    case 6:
        return "♔";
    case -1:
        return "♟";
    case -2:
        return "♜";
    case -3:
        return "♞";
    case -4:
        return "♝";
    case -5:
        return "♛";
    case -6:
        return "♚";
    default:
        return " ";
    }
}

void board_print(const Board *b) {
    printf("\n    a   b   c   d   e   f   g   h\n\n");
    for (int rank = 7; rank >= 0; rank--) {
        printf(" %d ", rank + 1);
        for (int file = 0; file <= 7; file++) {
            int sq = rank * 8 + file;
            int piece = piece_on(b, sq);

            if ((rank + file) % 2 == 0)
                printf("\033[48;5;136m");
            else
                printf("\033[48;5;222m");

            printf(" %s ", piece_symbol(piece));
            printf("\033[0m");
        }
        printf("  %d\n", rank + 1);
    }
    printf("\n    a   b   c   d   e   f   g   h\n\n");
    printf(" %s to move\n\n", b->turn == 0 ? "White" : "Black");
}

int read_move(char *buf, int bufsize) {
    printf("Enter move: ");
    if (scanf("%*[ \t\n]") == EOF)
        return 0;
    if (scanf("%9s", buf) != 1)
        return 0;
    (void)bufsize;
    return 1;
}

void print_move_result(MoveResult r) {
    switch (r) {
    case MOVE_OK:
        break;
    case MOVE_INVALID_INPUT:
        printf("Invalid input. Use format: e2e4\n");
        break;
    case MOVE_NO_PIECE:
        printf("No piece on that square.\n");
        break;
    case MOVE_WRONG_COLOR:
        printf("That's not your piece.\n");
        break;
    case MOVE_FRIENDLY_FIRE:
        printf("Your own piece is on that square.\n");
        break;
    case MOVE_ILLEGAL:
        printf("Illegal move.\n");
        break;
    }
}
