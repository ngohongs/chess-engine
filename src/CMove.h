/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 25/05/2020.
 */

#pragma once

#include <iostream>
#include "EPiece.h"
#include "EColor.h"
#include "ETile.h"
#include "EConst.h"

class CMove {
private:
    EColor m_Side = EColor::WHITE;
    int m_From = OFFBOARD;
    int m_To = OFFBOARD;
    EPiece m_Capture = EPiece::EMPTY;
    bool m_PawnTwoPush = false;
    bool m_EnPassant = false;
    EPiece m_Promotion = EPiece::EMPTY;
    bool m_Castle = false;
    int m_Score = 0;
public:
    CMove() = default;

    explicit CMove(EColor color, int from, int to, EPiece capture = EPiece::EMPTY, bool pawnStart = false,
                   bool enPassant = false, EPiece promotion = EPiece::EMPTY, bool castle = false, int score = 0);

    std::ostream & Print(std::ostream & os) const;

    bool IsEnPassant() const {
        return m_EnPassant;
    }

    bool IsPawnTwoPush() const {
        return m_PawnTwoPush;
    }

    bool IsCastling() const {
        return m_Castle;
    }

    bool IsWhiteMove() const {
        return m_Side == EColor::WHITE;
    }

    bool GetFrom() const {
        return m_From;
    }

    bool GetTo() const {
        return m_To;
    }

    EPiece GetCapture() const {
        return m_Capture;
    }

    EPiece GetPromotion() const {
        return m_Promotion;
    }

    EColor GetColor() const {
        return m_Side;
    }
};

CMove PushMove(EColor color, int from, int to);

CMove CaptureMove(EColor color, int from, int to, EPiece capture, bool enPassant = false);

CMove PawnTwoForward(EColor color, int from, int to);

CMove PromotionMove(EColor color, int from, int to, EPiece capture, EPiece promotion);

CMove CastleMove(EColor color, int castling);



