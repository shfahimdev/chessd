#include "board.h"
#include <stdio.h>

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
    b->castling_rights = CASTLE_WK | CASTLE_WQ | CASTLE_BK | CASTLE_BQ;
    b->en_passant_sq = -1;
    b->halfmove_clock = 0;
    b->fullmove_number = 1;
}

int piece_on(const Board *b, int sq) {
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

uint64_t get_friendly_bits(const Board *b) {
    if (b->turn == 0)
        return b->white_pawns | b->white_rooks | b->white_knights | b->white_bishops |
               b->white_queens | b->white_king;
    else
        return b->black_pawns | b->black_rooks | b->black_knights | b->black_bishops |
               b->black_queens | b->black_king;
}

uint64_t get_enemy_bits(const Board *b) {
    if (b->turn == 0)
        return b->black_pawns | b->black_rooks | b->black_knights | b->black_bishops |
               b->black_queens | b->black_king;
    else
        return b->white_pawns | b->white_rooks | b->white_knights | b->white_bishops |
               b->white_queens | b->white_king;
}

uint64_t get_all_bits(const Board *b) { return get_friendly_bits(b) | get_enemy_bits(b); }

uint64_t *get_piece_bitboard(Board *b, int piece_number) {
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
