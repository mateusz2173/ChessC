#ifndef BOARD_H
#define BOARD_H

#include "board.h"
#include "alWindow.h"

typedef struct
{
    int from;
    int to;
    int pieceFrom;
    int pieceTo;
    int castlePerm;
    int bK_tile;
    int wK_tile;
    int toMove;
    int enPass;
    int moveType;
} Position;

/* VARS */

int moveCount;

bool paused;

int promote_tile;
int promote_team;

Position c;
Position history[1024];

/* FUNCTIONS */

void startNewGame();
void swapToMove();
void updateHistory(int from, int pieceFrom, int to, int pieceTo, int moveType);

int undoMove();
int getAttacker(int tile);
int isChecked(int team);
int hasLegalMoves(int team);
void checkGameState();
void end_game(int result, int team);

#endif