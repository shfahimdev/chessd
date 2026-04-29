#include "moves.h"
#include <stdio.h>
#include <string.h>

int parse_move(const char *str, Move *out) {
    if (strlen(str) != 4)
        return 0;
    if (str[0] < 'a' || str[0] > 'h')
        return 0;
    if (str[2] < 'a' || str[2] > 'h')
        return 0;
    if (str[1] < '1' || str[1] > '8')
        return 0;
    if (str[3] < '1' || str[3] > '8')
        return 0;

    int from_file = str[0] - 'a';
    int from_rank = str[1] - '1'; // subtracting '1' gives 0-indexed rank directly
    int to_file = str[2] - 'a';
    int to_rank = str[3] - '1';

    out->from = from_rank * 8 + from_file;
    out->to = to_rank * 8 + to_file;
    out->flags = MOVE_QUIET;
    out->promotion_piece = 0;

    return 1;
}

MoveResult make_move(Board *b, Move m) {
    int piece_number = piece_on(b, m.from);

    // No piece on source square
    if (piece_number == 0)
        return MOVE_NO_PIECE;

    // Wrong color
    if (b->turn == 0 && piece_number < 0)
        return MOVE_WRONG_COLOR;
    if (b->turn == 1 && piece_number > 0)
        return MOVE_WRONG_COLOR;

    // Friendly fire
    if (get_friendly_bits(b) & (1ULL << m.to))
        return MOVE_FRIENDLY_FIRE;

    // Capture: clear the captured piece
    int captured = piece_on(b, m.to);
    if (captured != 0) {
        uint64_t *cap_bb = get_piece_bitboard(b, captured);
        if (cap_bb)
            *cap_bb &= ~(1ULL << m.to);
    }

    // Move the piece
    uint64_t *piece_bb = get_piece_bitboard(b, piece_number);
    *piece_bb &= ~(1ULL << m.from);
    *piece_bb |= (1ULL << m.to);

    // Update halfmove clock
    int is_pawn = (piece_number == 1 || piece_number == -1);
    int is_capture = (captured != 0);
    if (is_pawn || is_capture)
        b->halfmove_clock = 0;
    else
        b->halfmove_clock++;

    // Update fullmove number (increments after black moves)
    if (b->turn == 1)
        b->fullmove_number++;

    // Update en passant square
    int from_rank = m.from / 8;
    int to_rank = m.to / 8;
    if (is_pawn && (to_rank - from_rank == 2))
        b->en_passant_sq = m.from + 8; // white double push
    else if (is_pawn && (from_rank - to_rank == 2))
        b->en_passant_sq = m.from - 8; // black double push
    else
        b->en_passant_sq = -1;

    // Flip turn
    b->turn ^= 1;

    return MOVE_OK;
}

void unmake_move(Board *b, Move m) {
    // TODO: Phase 4+
    (void)b;
    (void)m;
}
