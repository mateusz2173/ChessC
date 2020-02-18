#include "pieces.h"

char PIECES_NAME[13][3] = {"00", "wP", "wN", "wB", "wR", "wQ", "wK", "bP", "bN", "bB", "bR", "bQ", "bK"};

int canMove(int from, int to)
{
    if (from < 0 || to < 0 || from > 63 || to > 63)
        return ILLEGAL;
    int piece = getPiece(from);
    if (from == to)
        return ILLEGAL;

    switch (piece)
    {
    case wP:
        return canMoveWP(from, to);
        break;
    case bP:
        return canMoveBP(from, to);
        break;
    case wR:
        return canMoveR(from, to);
        break;
    case bR:
        return canMoveR(from, to);
        break;
    case wN:
        return canMoveN(from, to);
        break;
    case bN:
        return canMoveN(from, to);
        break;
    case wB:
        return canMoveB(from, to);
        break;
    case bB:
        return canMoveB(from, to);
        break;
    case wQ:
        return canMoveQ(from, to);
        break;
    case bQ:
        return canMoveQ(from, to);
        break;
    case bK:
        return canMoveK(from, to);
        break;
    case wK:
        return canMoveK(from, to);
        break;
    default:
        return ILLEGAL;
    }
    return ILLEGAL;
}

int move(int from, int to)
{
    int team = getTeam(from);
    int pieceFrom = getPiece(from);
    int pieceTo = getPiece(to);
    int result = canMove(from, to);

    if (team != c.toMove || result == ILLEGAL)
        return ILLEGAL;
    updateHistory(from, pieceFrom, to, pieceTo, result);
    if (result == LEGAL || result == DOUBLE_PAWN_MOVE || result == PROMOTE)
    {
        forceMove(from, to);
        if (result == DOUBLE_PAWN_MOVE)
        {
            if (c.toMove == WHITE)
                c.enPass = __tile(__file(from), __rank(from) + 1);
            else
                c.enPass = __tile(__file(from), __rank(from) - 1);
        }
    }
    if (result == SHORT_CASTLING)
    {
        forceCastle(c.toMove, SHORT_CASTLING);
    }
    if (result == LONG_CASTLING)
    {
        forceCastle(c.toMove, LONG_CASTLING);
    }
    if (result == ENPASS)
    {
        int pawn_tile;
        if (c.toMove == WHITE)
            pawn_tile = __tile(__file(to), RANK_5);
        else
            pawn_tile = __tile(__file(to), RANK_4);
        setTile(pawn_tile, EMPTY);
        forceMove(from, to);
    }
    if(result == PROMOTE)
    {
        paused = true;
        show_promote(team);
        promote_tile = to;
        promote_team = c.toMove;
    }
    if (result)
    {        
        if (isChecked(team))
        {
            undoMove();
            hide_promote();
            promote_tile = -1;
            paused = false;
            return ILLEGAL;
        }
        else
        {
            swapToMove();
            if (!hasLegalMoves(c.toMove))
            {
                if(isChecked(c.toMove))
                {
                   end_game(CHECKMATE, c.toMove);
                   return CHECKMATE;
                }
                else
                {
                    end_game(STALEMATE, c.toMove);
                    return STALEMATE;
                }
            }
            return LEGAL;
        }
    }
    return ILLEGAL;
}

void forceMove(int from, int to)
{
    int fromPiece = getPiece(from);
    if (from == E1 || from == A1)
        c.castlePerm &= ~WK_MASK;
    else if (from == E1 || from == H1)
        c.castlePerm &= ~WQ_MASK;
    else if (from == E8 || from == A8)
        c.castlePerm &= ~BK_MASK;
    else if (from == E8 || from == H8)
        c.castlePerm &= ~BQ_MASK;

    setTile(from, EMPTY);
    setTile(to, fromPiece);
}

void forceCastle(int team, int side)
{
    if (side == SHORT_CASTLING)
    {
        if (team == WHITE)
        {
            setTile(H1, EMPTY);
            setTile(E1, EMPTY);
            setTile(F1, wR);
            setTile(G1, wK);

            c.castlePerm &= ~(WK_MASK | WQ_MASK);
        }
        else
        {
            setTile(H8, EMPTY);
            setTile(E8, EMPTY);
            setTile(F8, bR);
            setTile(G8, bK);

            c.castlePerm &= ~(BK_MASK | BQ_MASK);
        }
    }
    else if (side == LONG_CASTLING)
    {
        if (team == WHITE)
        {
            setTile(E1, EMPTY);
            setTile(A1, EMPTY);
            setTile(D1, wR);
            setTile(C1, wK);

            c.castlePerm &= ~(WK_MASK | WQ_MASK);
        }
        else
        {
            setTile(E8, EMPTY);
            setTile(A8, EMPTY);
            setTile(D8, bR);
            setTile(C8, bK);

            c.castlePerm &= ~(BK_MASK | BQ_MASK);
        }
    }
}

int canMoveWP(int from, int to)
{
    int rankFrom = __rank(from);
    int fileFrom = __file(from);
    int rankTo = __rank(to);
    int fileTo = __file(to);

    if (to == c.enPass)
    {
        if (__rank(from) == RANK_5 && ABS(__file(from) - __file(c.enPass)) == 1)
            return ENPASS;
        return ILLEGAL;
    }

    if (fileFrom == fileTo)
    {
        if (!isEmpty(to))
            return ILLEGAL;
        if (rankTo == rankFrom + 1)
        {
            if(rankTo == RANK_8) return PROMOTE;
            else return LEGAL;
        }
        if (rankTo == rankFrom + 2 && rankFrom == RANK_2)
            return DOUBLE_PAWN_MOVE;
        return ILLEGAL;
    }
    else
    {
        if (getTeam(to) != BLACK)
            return ILLEGAL;
        if ((rankTo == rankFrom + 1) && ((fileTo == fileFrom + 1) || (fileTo == fileFrom - 1)))
        {
            if (rankTo == RANK_8)
            {
                return PROMOTE;
            }
            else
                return LEGAL;
        }
    }

    return ILLEGAL;
}

int canMoveBP(int from, int to)
{
    int rankFrom = __rank(from);
    int fileFrom = __file(from);
    int rankTo = __rank(to);
    int fileTo = __file(to);

    if (to == c.enPass)
    {
        if (__rank(from) == RANK_4 && ABS(__file(from) - __file(c.enPass)) == 1)
            return ENPASS;
        return ILLEGAL;
    }

    if (fileFrom == fileTo)
    {
        if (!isEmpty(to))
            return ILLEGAL;
        if (rankTo == rankFrom - 1)
        {
            if(rankTo == RANK_1) return PROMOTE;
            else return LEGAL;
        }
        if (rankTo == rankFrom - 2 && rankFrom == RANK_7)
            return DOUBLE_PAWN_MOVE;
        return ILLEGAL;
    }
    else
    {
        if (getTeam(to) != WHITE)
            return ILLEGAL;
        if((rankTo == rankFrom - 1) && ((fileTo == fileFrom + 1) || (fileTo == fileFrom - 1)))
        {
            if(rankTo == RANK_1) return PROMOTE;
            return LEGAL;
        }
    }

    return ILLEGAL;
}

int canMoveN(int from, int to)
{
    int rankFrom = __rank(from);
    int fileFrom = __file(from);
    int rankTo = __rank(to);
    int fileTo = __file(to);

    if (getTeam(from) == getTeam(to))
        return ILLEGAL;

    if ((rankFrom == rankTo + 1) && (fileFrom == fileTo + 2))
        return LEGAL;
    if ((rankFrom == rankTo - 1) && (fileFrom == fileTo + 2))
        return LEGAL;
    if ((rankFrom == rankTo + 1) && (fileFrom == fileTo - 2))
        return LEGAL;
    if ((rankFrom == rankTo - 1) && (fileFrom == fileTo - 2))
        return LEGAL;
    if ((rankFrom == rankTo + 2) && (fileFrom == fileTo + 1))
        return LEGAL;
    if ((rankFrom == rankTo - 2) && (fileFrom == fileTo + 1))
        return LEGAL;
    if ((rankFrom == rankTo + 2) && (fileFrom == fileTo - 1))
        return LEGAL;
    if ((rankFrom == rankTo - 2) && (fileFrom == fileTo - 1))
        return LEGAL;

    return ILLEGAL;
}

int canMoveB(int from, int to)
{
    int rankFrom = __rank(from);
    int fileFrom = __file(from);
    int rankTo = __rank(to);
    int fileTo = __file(to);

    if (getTeam(from) == getTeam(to))
        return ILLEGAL;

    int diffR = rankTo - rankFrom;
    int diffF = fileTo - fileFrom;

    if ((fileTo - fileFrom != diffR) && (fileFrom - fileTo != diffR))
        return ILLEGAL;

    if (diffR > 0)
    {
        if (diffF > 0)
        {
            for (int r = rankFrom + 1, f = fileFrom + 1; r < rankTo && f < fileTo; r++, f++)
            {
                if (!isEmpty(__tile(f, r)))
                    return ILLEGAL;
            }
        }
        else
        {
            for (int r = rankFrom + 1, f = fileFrom - 1; r < rankTo && f > fileTo; r++, f--)
            {
                if (!isEmpty(__tile(f, r)))
                    return ILLEGAL;
            }
        }
    }
    else
    {
        if (diffF > 0)
        {
            for (int r = rankFrom - 1, f = fileFrom + 1; r > rankTo && f < fileTo; r--, f++)
            {
                if (!isEmpty(__tile(f, r)))
                    return ILLEGAL;
            }
        }
        else
        {
            for (int r = rankFrom - 1, f = fileFrom - 1; r > rankTo && f > fileTo; r--, f--)
            {
                if (!isEmpty(__tile(f, r)))
                    return ILLEGAL;
            }
        }
    }

    return LEGAL;
}

int canMoveR(int from, int to)
{
    int rankFrom = __rank(from);
    int fileFrom = __file(from);
    int rankTo = __rank(to);
    int fileTo = __file(to);

    if (getTeam(from) == getTeam(to))
        return ILLEGAL;
    if (fileFrom != fileTo && rankFrom != rankTo)
        return ILLEGAL;

    if (fileFrom > fileTo)
    {
        for (int f = fileFrom - 1; f > fileTo; f--)
        {
            if (!isEmpty(__tile(f, rankFrom)))
                return ILLEGAL;
        }

        return LEGAL;
    }
    else if (fileFrom < fileTo)
    {
        for (int f = fileFrom + 1; f < fileTo; f++)
        {
            if (!isEmpty(__tile(f, rankFrom)))
                return ILLEGAL;
        }

        return LEGAL;
    }

    else if (rankFrom > rankTo)
    {
        for (int r = rankFrom - 1; r > rankTo; r--)
        {
            if (!isEmpty(__tile(fileFrom, r)))
                return ILLEGAL;
        }

        return LEGAL;
    }

    else if (rankFrom < rankTo)
    {
        for (int r = rankFrom + 1; r < rankTo; r++)
        {
            if (!isEmpty(__tile(fileFrom, r)))
                return ILLEGAL;
        }

        return LEGAL;
    }

    return ILLEGAL;
}

int canMoveQ(int from, int to)
{
    return canMoveR(from, to) || canMoveB(from, to);
}

int canMoveK(int from, int to)
{
    int rankFrom = __rank(from);
    int fileFrom = __file(from);
    int rankTo = __rank(to);
    int fileTo = __file(to);

    int team = getTeam(from);

    if (team == getTeam(to))
        return ILLEGAL;

    int diffR = rankTo - rankFrom;
    int diffF = fileTo - fileFrom;

    if (ABS(diffR) <= 1 && ABS(diffF) <= 1)
        return LEGAL;

    if (team == WHITE && from == E1 && to == G1 && hasCastlePerm(WHITE, SHORT_CASTLING))
    {
        if (!isEmpty(F1) || !isEmpty(G1))
            return ILLEGAL;
        return SHORT_CASTLING;
    }
    if (team == WHITE && from == E1 && to == C1 && hasCastlePerm(WHITE, LONG_CASTLING))
    {
        if (!isEmpty(B1) || !isEmpty(C1) || !isEmpty(D1))
            return ILLEGAL;
        return LONG_CASTLING;
    }
    if (team == BLACK && from == E8 && to == G8 && hasCastlePerm(BLACK, SHORT_CASTLING))
    {
        if (!isEmpty(F8) || !isEmpty(G8))
            return ILLEGAL;
        return SHORT_CASTLING;
    }
    if (team == BLACK && from == E8 && to == C8 && hasCastlePerm(BLACK, LONG_CASTLING))
    {
        if (!isEmpty(B8) || !isEmpty(C8) || !isEmpty(D8))
            return ILLEGAL;
        return LONG_CASTLING;
    }

    return ILLEGAL;
}

int hasCastlePerm(int team, int castle)
{
    if (team == WHITE && castle == SHORT_CASTLING)
        return c.castlePerm & WK_MASK;
    if (team == WHITE && castle == LONG_CASTLING)
        return c.castlePerm & WQ_MASK;
    if (team == BLACK && castle == SHORT_CASTLING)
        return c.castlePerm & BK_MASK;
    if (team == WHITE && castle == LONG_CASTLING)
        return c.castlePerm & BQ_MASK;

    return ILLEGAL;
}