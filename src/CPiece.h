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

class CPiece {
protected:
    int m_Coord;
    EPiece m_Piece;
    EColor m_Color;
    int m_PieceCode;
    size_t m_LastTurn = 0;
    CBoard & m_Board;
public:
    explicit CPiece(CBoard & board, int coord, EPiece piece, EColor color, int code);

    virtual ~CPiece() = default;

    virtual std::list<CMove> MoveList() const = 0;

    virtual std::ostream & Print(std::ostream & os) const = 0;

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

    size_t GetLastTurn() const;
};



