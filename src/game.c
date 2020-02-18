#include "game.h"

void startNewGame()
{
    moveCount = 0;
    promote_tile = -1;
    paused = false;

    c.from = -1;
    c.to = -1;
    c.pieceFrom = -1;
    c.pieceTo = -1;
    c.castlePerm = 15; // 1 1 1 1
    c.bK_tile = E8;
    c.wK_tile = E1;
    c.toMove = WHITE;
    c.enPass = -1;

    perspective = WHITE;
    undo_btn.img = UNDO_RED_BTN;
    result_label.visible = false;

    initBoard();
    hide_promote();
}

void swapToMove()
{
    if (c.toMove == WHITE)
        c.toMove = BLACK;
    else
        c.toMove = WHITE;
}

int getAttacker(int tile)
{
    int team = getTeam(tile);

    for (int p = 0; p < 64; p++)
    {
        if (p == tile)
            continue;
        if (getTeam(p) == team || getTeam(p) == NONE)
            continue;
        if (canMove(p, tile))
            return p;
    }

    return -1;
}

int isChecked(int team)
{
    int tile = (team == WHITE ? c.wK_tile : c.bK_tile);
    return getAttacker(tile) != -1;
}

int undoMove()
{
    if (moveCount == 0)
        return 0;
    result_label.visible = false;
    paused = false;
    c = history[--moveCount];
    setTile(c.from, c.pieceFrom);
    setTile(c.to, c.pieceTo);
    if (c.moveType == SHORT_CASTLING)
    {
        if (c.toMove == WHITE)
        {
            setTile(F1, EMPTY);
            setTile(G1, EMPTY);
            setTile(H1, wR);
        }
        else
        {
            setTile(F8, EMPTY);
            setTile(G8, EMPTY);
            setTile(H8, bR);
        }
    }
    else if (c.moveType == LONG_CASTLING)
    {
        if (c.toMove == WHITE)
        {
            setTile(A1, wR);
            setTile(B1, EMPTY);
            setTile(C1, EMPTY);
            setTile(D1, EMPTY);
        }
        else
        {
            setTile(A8, bR);
            setTile(B8, EMPTY);
            setTile(C8, EMPTY);
            setTile(D8, EMPTY);
        }
    }
    else if (c.moveType == ENPASS)
    {
        if (c.toMove == WHITE)
        {
            setTile(__tile(__file(c.enPass), RANK_5), bP);
        }
        else
        {
            setTile(__tile(__file(c.enPass), RANK_4), wP);
        }
    }

    return 1;
}

void updateHistory(int from, int pieceFrom, int to, int pieceTo, int moveType)
{
    history[moveCount] = c;
    history[moveCount].from = from;
    history[moveCount].to = to;
    history[moveCount].pieceFrom = pieceFrom;
    history[moveCount].pieceTo = pieceTo;
    history[moveCount].moveType = moveType;

    moveCount++;
}

int hasLegalMoves(int team)
{
    for (int i = 0; i < 64; i++)
    {
        if (getTeam(i) == team)
        {
            int pieceFrom = getPiece(i);
            for (int j = 0; j < 64; j++)
            {
                if (getTeam(j) != team && canMove(i, j))
                {
                    int pieceTo = getPiece(j);
                    forceMove(i, j);
                    updateHistory(i, pieceFrom, j, pieceTo, LEGAL);
                    if (isChecked(team))
                    {
                        undoMove();
                        continue;
                    }
                    else
                    {
                        undoMove();
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void checkGameState()
{
    if(!hasLegalMoves(c.toMove))
    {
        if(isChecked(c.toMove))
        {
            end_game(CHECKMATE, c.toMove);
        }
        else
        {
            end_game(STALEMATE, c.toMove);
        } 
    }
}

void end_game(int result, int team)
{
    if(result == STALEMATE)
    {
        result_label.text = "REMIS!";
    }
    else if(result == CHECKMATE)
    {
        if(team == WHITE)
        {
            result_label.text = "WYGRYWAJA CZARNE!";
        }
        else
        {
            result_label.text = "WYGRYWAJA BIALE!";
        }
    }
    paused = true;
    result_label.visible = true;
}
