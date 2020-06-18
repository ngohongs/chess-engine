/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include <iostream>
#include <memory>
#include <list>
#include "CMove.h"
#include "EColor.h"
#include "EPiece.h"
#include "ETile.h"
#include "EConst.h"


class CBoard;

/**
 * Abstract class representing a piece on board
 */
class CPiece {
protected:
    // Board containing this piece
    CBoard & m_Board;

    // Its coordinates
    int m_Coord;

    // Piece type
    EPiece m_Piece;

    // Color the piece
    EColor m_Color;

    // Piece code
    int m_PieceCode;

    // TODO remove m_Lasturn
    size_t m_LastTurn = 0;
public:
    explicit CPiece(CBoard & board, int coord, EPiece piece, EColor color, int code);

    virtual ~CPiece() = default;

    /**
     * Generates all pseudo-legal moves (can get itself in check) for the piece
     * @return std::list of all pseudo-legal moves
     */
    virtual std::list<CMove> MoveList() const = 0;

    /**
     * Generate all pseudo-legal capture moves (can get itself in check) for the piece
     * @return std::list of all pseudo-legal captures
     */
    virtual std::list<CMove> CaptureMoveList() const = 0;

    /**
     * Print itself
     * @param os output stream
     * @return std::ostream & after output
     */
    virtual std::ostream & Print(std::ostream & os) const = 0;

    /**
     * Output self
     * @param os output stream
     * @param self
     * @return std::ostream & os after output
     */
    friend std::ostream & operator<<(std::ostream & os, const CPiece & self);

    int GetCoord() const {
        return m_Coord;
    }

    EPiece GetPiece() const {
        return m_Piece;
    }

    EColor GetColor() const {
        return m_Color;
    }

    int GetCode() const {
        return m_PieceCode;
    }

    size_t GetLastTurn() const {
        return m_LastTurn;
    }

    void SetCoord(int index) {
        m_Coord = index;
    }
};



