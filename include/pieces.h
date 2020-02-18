#ifndef PIECES_H
#define PIECES_H

#define ABS(N) (((N) < 0) ? (-(N)) : (N))

#include "board.h"
#include "game.h"

#define WK_MASK 1 // (1 << 0)
#define WQ_MASK 2 // (1 << 1)
#define BK_MASK 4 // (1 << 2)
#define BQ_MASK 8 // (1 << 3)

char PIECES_NAME[13][3];

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
enum { ILLEGAL, LEGAL, ENPASS, SHORT_CASTLING, LONG_CASTLING, DOUBLE_PAWN_MOVE, PROMOTE, CHECKMATE, STALEMATE };

/* FUNCTIONS */

int canMove(int from, int to);

int move(int from, int to);

void forceMove(int from, int to);

void forceCastle(int team, int side);

int canMoveWP(int from, int to);

int canMoveBP(int from, int to);

int canMoveN(int from, int to);

int canMoveB(int from, int to);

int canMoveR(int from, int to);

int canMoveQ(int from, int to);

int canMoveK(int from, int to);

int hasCastlePerm(int team, int castle);

#endif // PIECES_H