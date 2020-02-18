#include "alMouse.h"

int getTile(int mouseX, int mouseY)
{
    int boardBoundX = al_get_display_width(display) * CHEQUER_SCALE;
    int boardBoundY = al_get_display_height(display);
    if (mouseX <= boardBoundX)
    {
        int file = mouseX / (boardBoundX / 8);
        int rank = mouseY / (boardBoundY / 8);
        if (perspective == WHITE)
            rank = 7 - rank;

        return __tile(file, rank);
    }
    else
        return -1;
}

void drawDragged()
{
    if (draggedTile == -1)
        return;
    int piece = getPiece(draggedTile);
    if (piece == 0)
        return;
    drawPiece(piece, getMouseX() - 20, getMouseY() - 20);
}

int getMouseX()
{
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);

    return state.x;
}

int getMouseY()
{
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);

    return state.y;
}

void tilePressed(int tile)
{
    if(paused) return;
    if (draggedTile == -1)
    {
        draggedTile = tile;
    }
    else
    {
        int result = move(draggedTile, tile);
        draggedTile = -1;
        if (result)
        {
            undo_btn.img = UNDO_GREEN_BTN;
            if(flip)
            {
                if (perspective == WHITE)
                    perspective = BLACK;
                else
                    perspective = WHITE;
            }

        }
        if (result == CHECKMATE)
        {
            end_game(CHECKMATE, c.toMove); 
        }
    }
}

void tileReleased(int tile)
{
    if(paused) return;
    if (draggedTile == -1)
        return;
    if (tile == draggedTile)
        return;
    else
    {
        int result = move(draggedTile, tile);
        draggedTile = -1;
        if (result)
        {
            undo_btn.img = UNDO_GREEN_BTN;
            if(flip)
            {
                if (perspective == WHITE)
                    perspective = BLACK;
                else
                    perspective = WHITE;
            }

        }
        if (result == CHECKMATE)
        {
            end_game(CHECKMATE, c.toMove);
        }
    }
}
