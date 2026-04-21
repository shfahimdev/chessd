#include <inttypes.h>
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
    case 1:
        return "♙"; // pawn
    case 2:
        return "♖"; // rook
    case 3:
        return "♘"; // knight
    case 4:
        return "♗"; // bishop
    case 5:
        return "♕"; // queen
    case 6:
        return "♔"; // king

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

void board_print(Board *b) {
    // printf("\033[2J\033[H"); // clear screen
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

uint64_t *get_piece_bit(Board *b, int piece_number) {
    switch (piece_number) {
    case 1:
        return &b->white_pawns;
    case 2:
        return &b->white_rooks;
    case 3:
        return &b->white_knights;
    case 4:
        return &b->white_bishops;
    case 5:
        return &b->white_queens;
    case 6:
        return &b->white_king;
    case -1:
        return &b->black_pawns;
    case -2:
        return &b->black_rooks;
    case -3:
        return &b->black_knights;
    case -4:
        return &b->black_bishops;
    case -5:
        return &b->black_queens;
    case -6:
        return &b->black_king;
    default:
        return NULL;
    }
}

uint64_t get_friendly_bits(Board *b) {
    if (b->turn == 0) {
        uint64_t friendly_bits = (b->white_pawns | b->white_rooks | b->white_knights |
                                  b->white_bishops | b->white_queens | b->white_king);
        return friendly_bits;
    }
    if (b->turn == 1) {
        uint64_t friendly_bits = (b->black_pawns | b->black_rooks | b->black_knights |
                                  b->black_bishops | b->black_queens | b->black_king);
        return friendly_bits;
    }
}

void print_bits(uint64_t x) {
    for (int i = 63; i >= 0; i--) {
        printf("%d", (int)((x >> i) & 1ULL));

        // optional: spacing every 8 bits for readability
        if (i % 8 == 0)
            printf(" ");
    }
    printf("\n");
}

void make_move(Board *b, char str[]) {
    int file = str[0] - 'a';
    int rank = str[1] - '0';
    int file_prime = str[2] - 'a';
    int rank_prime = str[3] - '0';

    int square_from = (rank - 1) * 8 + file;
    int square_to = (rank_prime - 1) * 8 + file_prime;

    int piece_number = piece_on(b, square_from);
    int prime_piece_number = piece_on(b, square_to);

    uint64_t *piece_bit = get_piece_bit(b, piece_number);
    uint64_t *prime_piece_bit = get_piece_bit(b, prime_piece_number);

    if (piece_bit && *piece_bit) {
        uint64_t friendly_bits = get_friendly_bits(b);

        if (friendly_bits & (1ULL << square_to)) {
            printf("Not a valid move (Friendly Pieace Detected)\n");
            return;
        }

    } else {
        printf("No Targeted piece\n");
        return;
    }

    if (prime_piece_bit && *prime_piece_bit) {
        printf("Destination Square has: %d\n", prime_piece_number);
        *prime_piece_bit &= ~(1ULL << square_to);
        *piece_bit &= ~(1ULL << square_from);
        *piece_bit |= (1ULL << square_to);
    } else {
        printf("No destination piece\n");
        *piece_bit &= ~(1ULL << square_from);
        *piece_bit |= (1ULL << square_to);
    }

    board_print(b);
}

int main(void) {
    Board b;
    board_init(&b);
    board_print(&b);

    char str[10];
    printf("Enter Move: ");
    scanf("%9s", str);

    make_move(&b, str);
    return 0;
}
