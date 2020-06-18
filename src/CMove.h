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


/**
 * Class CMove representing a move
 */
class CMove {
private:
    // Mover
    EColor m_Side = EColor::WHITE;

    // Coordinate from which a piece is moved
    int m_From = OFFBOARD;

    // Coordinate to which a piece is moved
    int m_To = OFFBOARD;

    // Capture if capture was made
    EPiece m_Capture = EPiece::EMPTY;

    // If pawn was moved by two from starting rank
    bool m_PawnTwoPush = false;

    // If the move was an en passant capture
    bool m_EnPassant = false;

    // If a pawn was promoted
    EPiece m_Promotion = EPiece::EMPTY;

    // If the move was a castling move
    bool m_Castle = false;

    // Score of the move
    int m_Score = 0;
public:
    CMove() = default;

    explicit CMove(EColor color, int from, int to, EPiece capture = EPiece::EMPTY, bool pawnStart = false,
                   bool enPassant = false, EPiece promotion = EPiece::EMPTY, bool castle = false, int score = 0);

    /**
     * Print the move
     * @param os output stream
     * @return std::ostream & after output
     */
    std::ostream & Print(std::ostream & os) const;

    /**
     * Output CMove
     * @param os output stream
     * @param self move to be output
     * @return std::ostream & after output
     */
    friend std::ostream & operator<<(std::ostream & os, const CMove & self);

    /**
     * Input CMove
     * @param is input stream
     * @param self move to be input
     * @return std::istream & after input
     */
    friend std::istream & operator>>(std::istream & is, CMove & self);

    /**
     * Match if from, to coordinates and promotion are the same
     * @param other CMove to be compared with
     * @return true if they match, else false
     */
    bool operator==(const CMove & other) const;

    /**
     * Match if other CMove is a exact match
     * @param other CMove to be compared with
     * @return true if they match, else false
     */
    bool ExactMatch(const CMove & other) const;

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

    int GetFrom() const {
        return m_From;
    }

    int GetTo() const {
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

    void SetScore(int score) {
        m_Score = score;
    }

    bool IsValid() const {
        return m_From != OFFBOARD && m_To != OFFBOARD;
    }

    bool IsCapture() const {
        return m_Capture != EPiece::EMPTY;
    }

    bool operator<(const CMove & other) const {
        return m_Score > other.m_Score;
    }
};

/**
 * Creates a quiet move (no capture was made)
 * @param color of the mover
 * @param from coordinates
 * @param to coordinates
 * @return a quiet CMove
 */
CMove PushMove(EColor color, int from, int to);

/**
 * Creates a capture
 * @param piece which made the capture
 * @param color of the mover
 * @param from coordinates
 * @param to coordinates
 * @param capture captured piece
 * @param enPassant if the capture was an en passant capture
 * @return a capture CMove
 */
CMove CaptureMove(EPiece piece, EColor color, int from, int to, EPiece capture, bool enPassant = false);

/**
 * Creates a two push move for a pawn
 * @param color of the mover
 * @param from coordinates
 * @param to coordinates
 * @return a two push pawn CMove
 */
CMove PawnTwoForward(EColor color, int from, int to);

/**
 * Creates a promotion move for a pawn
 * @param piece moved piece
 * @param color of the mover
 * @param from coordinates
 * @param to coordinates
 * @param capture captured piece if capture was made
 * @param promotion to which piece promotes
 * @return a promotion CMove
 */
CMove PromotionMove(EPiece piece, EColor color, int from, int to, EPiece capture, EPiece promotion);

/**
 * Creates a castling move
 * @param color of the mover
 * @param castling what castling
 * @return a castling CMove
 */
CMove CastleMove(EColor color, int castling);



