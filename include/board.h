#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "pieces.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQUARES 64
#define CASE_DIFF 'A' - 'a'

/* MACROS */

#define __tile(f, r) ((r)*8 + (f))
#define __rank(t) ((t) / 8)
#define __file(t) ((t) % 8)

/* ENUMS */

enum
{
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8
};

enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum { NONE, WHITE, BLACK };

/* FUNCTIONS */

void initBoard();
void setTile(int tile, int piece);

int getPiece(int tile);
int getTeam(int tile);
int isEmpty(int tile);

char* getPieceName(int tile);

/* VARS */

extern int TILE[SQUARES];
extern char FILE_NAME[9];
extern char RANK_NAME[9];
extern char SQ_NAMES[65][6];

#endif // BOARD_H_INCLUDED
