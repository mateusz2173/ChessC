#include "alImages.h"

bool initImages()
{
    PIECES_IMG[0] = 0;
    PIECES_IMG[wP] = al_load_bitmap(PIECES_PATH(WhitePawn.png));
    PIECES_IMG[wR] = al_load_bitmap(PIECES_PATH(WhiteRook.png));
    PIECES_IMG[wN] = al_load_bitmap(PIECES_PATH(WhiteKnight.png));
    PIECES_IMG[wB] = al_load_bitmap(PIECES_PATH(WhiteBishop.png));
    PIECES_IMG[wQ] = al_load_bitmap(PIECES_PATH(WhiteQueen.png));
    PIECES_IMG[wK] = al_load_bitmap(PIECES_PATH(WhiteKing.png));

    PIECES_IMG[bP] = al_load_bitmap(PIECES_PATH(BlackPawn.png));
    PIECES_IMG[bR] = al_load_bitmap(PIECES_PATH(BlackRook.png));
    PIECES_IMG[bN] = al_load_bitmap(PIECES_PATH(BlackKnight.png));
    PIECES_IMG[bB] = al_load_bitmap(PIECES_PATH(BlackBishop.png));
    PIECES_IMG[bQ] = al_load_bitmap(PIECES_PATH(BlackQueen.png));
    PIECES_IMG[bK] = al_load_bitmap(PIECES_PATH(BlackKing.png));

    for (int i = 1; i < 13; i++)
    {
        if (!PIECES_IMG[i])
        {
            printf("\nNie udalo sie zaladowac figury (%d)!", i);
            running = false;
            return false;
        }
    }
    
    LEAVE_BTN = al_load_bitmap(BUTTONS_PATH(leave_btn.png));
    UNDO_GREEN_BTN = al_load_bitmap(BUTTONS_PATH(undo_green_btn.png));
    UNDO_RED_BTN = al_load_bitmap(BUTTONS_PATH(undo_red_btn.png));
    NEW_GAME_BTN = al_load_bitmap(BUTTONS_PATH(new_game_btn.png));
    FLIP_RED_BTN = al_load_bitmap(BUTTONS_PATH(flip_red_btn.png));
    FLIP_GREEN_BTN = al_load_bitmap(BUTTONS_PATH(flip_green_btn.png));

    if(!(LEAVE_BTN && UNDO_GREEN_BTN && UNDO_RED_BTN && NEW_GAME_BTN && FLIP_GREEN_BTN && FLIP_RED_BTN))
    {
        printf("\nNie udalo sie zaladowac przycisków.");
        running = false;
        return false;
    }

    return true;
}

void drawPiece(int piece, int x, int y)
{
    al_draw_bitmap(PIECES_IMG[piece], x + 20, y, 0);
}

void drawPieceTiled(int piece, int tile)
{
    int rank = __rank(tile);
    int file = __file(tile);
    if (perspective == WHITE)
        rank = 7 - rank;
    int width = al_get_display_width(display) * CHEQUER_SCALE;
    int height = al_get_display_height(display);
    int sq_width = width / 8;
    int sq_height = height / 8;
    int x, y;
    x = file * sq_width;
    y = rank * sq_height;

    drawPiece(piece, x + sq_width / 9, y + sq_height / 9);
}