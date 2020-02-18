#ifndef ALIMAGES_H
#define ALIMAGES_H

#include "board.h"
#include "alWindow.h"

#define STRINGIFY(s) #s
#define PIECES_PATH(piece) STRINGIFY(res/pieces/piece)
#define BUTTONS_PATH(button) STRINGIFY(res/buttons/button)

ALLEGRO_BITMAP *PIECES_IMG[13];
ALLEGRO_BITMAP *LEAVE_BTN;
ALLEGRO_BITMAP *UNDO_GREEN_BTN;
ALLEGRO_BITMAP *UNDO_RED_BTN;
ALLEGRO_BITMAP *NEW_GAME_BTN;
ALLEGRO_BITMAP *FLIP_GREEN_BTN;
ALLEGRO_BITMAP *FLIP_RED_BTN;

bool initImages();

void drawPiece(int piece, int x, int y);
void drawPieceTiled(int piece, int tile);

#endif
