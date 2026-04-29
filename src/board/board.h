#ifndef BOARD_H
#define BOARD_H

#include "bitboard.h"
#include <stdint.h>

// Castling rights bitmask
#define CASTLE_WK (1 << 0)
#define CASTLE_WQ (1 << 1)
#define CASTLE_BK (1 << 2)
#define CASTLE_BQ (1 << 3)

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

    int turn;                // 0 = white, 1 = black
    uint8_t castling_rights; // bits: 0=WK, 1=WQ, 2=BK, 3=BQ
    int en_passant_sq;       // -1 if none, else square index 0-63
    int halfmove_clock;
    int fullmove_number;
} Board;

void board_init(Board *b);
int piece_on(const Board *b, int sq);
uint64_t get_friendly_bits(const Board *b);
uint64_t get_enemy_bits(const Board *b);
uint64_t get_all_bits(const Board *b);
uint64_t *get_piece_bitboard(Board *b, int piece_number);

#endif // !BOARD_H
