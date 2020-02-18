#include "board.h"

int TILE[64] = {0};
char FILE_NAME[9] = "ABCDEFGH";
char RANK_NAME[9] = "12345678";
char SQ_NAMES[65][6] =
    {
        "A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
        "A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
        "A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
        "A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
        "A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
        "A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
        "A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
        "A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8", "NO_SQ"};

void initBoard()
{
    for(int i = 0; i < 64; i++)
        setTile(i, EMPTY);

    for (int i = A2; i <= H2; i++)
    {
        setTile(i, wP);
        setTile(i + 40, bP);
    }
    setTile(A1, wR);
    setTile(B1, wN);
    setTile(C1, wB);
    setTile(D1, wQ);
    setTile(E1, wK);
    setTile(F1, wB);
    setTile(G1, wN);
    setTile(H1, wR);

    setTile(A8, bR);
    setTile(B8, bN);
    setTile(C8, bB);
    setTile(D8, bQ);
    setTile(E8, bK);
    setTile(F8, bB);
    setTile(G8, bN);
    setTile(H8, bR);
}

void setTile(int tile, int piece)
{
    if (piece == wK)
        c.wK_tile = tile;
    else if (piece == bK)
        c.bK_tile = tile;
    TILE[tile] = piece;
}

int getPiece(int tile)
{
    if (tile < 0 || tile > 63)
        return -1;
    return TILE[tile];
}

char *getPieceName(int tile)
{
    return PIECES_NAME[getPiece(tile)];
}

int getTeam(int tile)
{
    int piece = getPiece(tile);
    if (piece == EMPTY)
        return NONE;
    if (piece >= bP)
        return BLACK;
    else
        return WHITE;
}

int isEmpty(int tile)
{
    return TILE[tile] == EMPTY;
}
