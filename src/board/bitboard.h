#ifndef BITBOARD_H
#define BITBOARD_H

#include <stdint.h>

void bb_print(uint64_t bb);
int bb_count(uint64_t bb);
int bb_lsb(uint64_t bb);

#endif // !BITBOARD_H
