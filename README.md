# chessd

Building a full chess.com clone in C, just to annoy everyone who's never touched a pointer.

Single-player against an engine, two players over a network, accounts, Elo ratings,
matchmaking, and tournaments. No GUI. No frameworks. No dependencies beyond libc,
pthreads, and ncurses.

---

## Status

Early development — the board isn't even drawn yet.

---

## Roadmap

- [ ] Phase 1 — The Board
- [ ] Phase 2 — Movement
- [ ] Phase 3 — Legal Moves
- [ ] Phase 4 — Check
- [ ] Phase 5 — Game Endings
- [ ] Phase 6 — Special Moves
- [ ] Phase 7 — Complete Local Game
- [ ] Phase 8 — Concurrency Primitives
- [ ] Phase 9 — Multiplayer Server
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

(Yeah, the Roadmap is AI generated, Don't Judge)
---

## Building

```bash
git clone https://github.com/shfahimdev/chessd.git
cd chessd
make
./chessd
```

Requirements: GCC, make, pthreads, ncurses.

---

## License

MIT
