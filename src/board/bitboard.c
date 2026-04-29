#include "bitboard.h"
#include <stdio.h>

void bb_print(uint64_t bb) {
    printf("\n    a b c d e f g h\n\n");
    for (int rank = 7; rank >= 0; rank--) {
        printf(" %d  ", rank + 1);
        for (int file = 0; file < 8; file++) {
            int sq = rank * 8 + file;
            printf("%d ", (int)((bb >> sq) & 1ULL));
        }
        printf(" %d\n", rank + 1);
    }
    printf("\n    a b c d e f g h\n\n");
}

int bb_count(uint64_t bb) {
    int count = 0;
    while (bb) {
        bb &= bb - 1;
        count++;
    }
    return count;
}

int bb_lsb(uint64_t bb) {
    // undefined if bb == 0; caller must check
    return __builtin_ctzll(bb);
}
