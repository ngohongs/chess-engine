/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 25/05/2020.
 */

#pragma once

#include <iostream>
#include "EPiece.h"
#include "ETile.h"
#include "EConst.h"

class CMove {
private:
    int m_From;
    int m_To;
    EPiece m_Capture = EPiece::EMPTY;
    bool m_PawnTwoPush = false;
    bool m_EnPassant = false;
    EPiece m_Promotion = EPiece::EMPTY;
    bool m_Castle = false;
    int m_Score = 0;
public:
    explicit CMove(int from, int to,
                   EPiece capture = EPiece::EMPTY, bool pawnStart = false, bool enPassant = false,
                   EPiece promotion = EPiece::EMPTY, bool castle = false, int score = 0);

    std::ostream & Print(std::ostream & os) const;
};

CMove PushMove(int from, int to);

CMove CaptureMove(int from, int to, EPiece capture, bool enPassant = false);

CMove PawnTwoForward(int from, int to);

CMove PromotionMove(int from, int to, EPiece capture, EPiece promotion);

CMove CastleMove(int castling);



