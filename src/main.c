#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint64_t white_pawns;
    uint64_t white_rooks;
    uint64_t white_knights;
    uint64_t white_bishops;
    uint64_t white_queens;
    uint64_t white_king;
    uint64_t black_pawns;
    uint64_t black_rooks;
    uint64_t black_knights;
    uint64_t black_bishops;
    uint64_t black_queens;
    uint64_t black_king;
    int turn;
} Board;

void board_init(Board *b) {
    b->white_pawns = 0x000000000000FF00ULL;
    b->white_rooks = (1ULL << 0) | (1ULL << 7);
    b->white_knights = (1ULL << 1) | (1ULL << 6);
    b->white_bishops = (1ULL << 2) | (1ULL << 5);
    b->white_queens = (1ULL << 3);
    b->white_king = (1ULL << 4);

    b->black_pawns = 0x00FF000000000000ULL;
    b->black_rooks = (1ULL << 56) | (1ULL << 63);
    b->black_knights = (1ULL << 57) | (1ULL << 62);
    b->black_bishops = (1ULL << 58) | (1ULL << 61);
    b->black_queens = (1ULL << 59);
    b->black_king = (1ULL << 60);

    b->turn = 0;
}

int piece_on(Board *b, int sq) {
    uint64_t bit = (1ULL << sq);

    if (b->white_pawns & bit)
        return 1;
    if (b->white_rooks & bit)
        return 2;
    if (b->white_knights & bit)
        return 3;
    if (b->white_bishops & bit)
        return 4;
    if (b->white_queens & bit)
        return 5;
    if (b->white_king & bit)
        return 6;

    if (b->black_pawns & bit)
        return -1;
    if (b->black_rooks & bit)
        return -2;
    if (b->black_knights & bit)
        return -3;
    if (b->black_bishops & bit)
        return -4;
    if (b->black_queens & bit)
        return -5;
    if (b->black_king & bit)
        return -6;

    return 0;
}

const char *piece_symbol(int piece) {
    switch (piece) {
    case -1:
        return "♙";
    case 1:
        return "♟";
    case -2:
        return "♘";
    case 2:
        return "♞";
    case -3:
        return "♗";
    case 3:
        return "♝";
    case -4:
        return "♖";
    case 4:
        return "♜";
    case -5:
        return "♕";
    case 5:
        return "♛";
    case -6:
        return "♔";
    case 6:
        return "♚";
    default:
        return " ";
    }
}

void board_print(Board *b) {
    printf("\033[2J\033[H"); // clear screen
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

int main(void) {
    Board b;
    board_init(&b);
    board_print(&b);

    return 0;
}
