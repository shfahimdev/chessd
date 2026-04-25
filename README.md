# chessd

Building a full chess.com clone in C, just to annoy framework bros.

Single-player against an engine, two players over a network, accounts, Elo ratings,
matchmaking, and tournaments. No GUI. No frameworks. No dependencies beyond libc,
pthreads, and ncurses.

---

## Status

**Phase 2 complete** - pieces move.

Moves are entered in coordinate notation (`e2e4`, `b1c3`). The board updates correctly,
captures work, and the turn advances. No legality validation yet — that's Phase 3.

### Board representation

The board is stored as 12 bitboards: one `uint64_t` per piece type per color.
Bit N maps to square N, where square 0 = a1 and square 63 = h8.
The entire board state fits in 12 `uint64_t` values plus a turn flag.

### Move representation

Moves are parsed from pure coordinate notation (no separator, no disambiguation).

---

## Source layout

```
src/
  main.c              — Entry point and game loop
```

---

## Roadmap

- [x] Phase 1  — The Board
- [x] Phase 2  — Movement
- [ ] Phase 3  — Legal Moves
- [ ] Phase 4  — Check
- [ ] Phase 5  — Game Endings
- [ ] Phase 6  — Special Moves
- [ ] Phase 7  — Complete Local Game
- [ ] Phase 8  — Concurrency Primitives
- [ ] Phase 9  — Multiplayer Server
- [ ] Phase 10 — Game Persistence
- [ ] Phase 11 — Accounts
- [ ] Phase 12 — Elo Ratings
- [ ] Phase 13 — Matchmaking
- [ ] Phase 14 — Terminal UI
- [ ] Phase 15 — Time Controls
- [ ] Phase 16 — Spectators & Chat
- [ ] Phase 17 — Engine
- [ ] Phase 18 — Post-Game Analysis
- [ ] Phase 19 — Admin & Config
- [ ] Phase 20 — Hardening & Performance


---

Requirements: GCC, make, pthreads, ncurses.

---

## License

MIT
