/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include <iostream>
#include <memory>
#include <set>
#include "CCoord.h"
#include "EColor.h"
#include "EPiece.h"

class CBoard;

class CPiece {
protected:
    CCoord m_Coord;
    EPiece m_Piece;
    EColor m_Color;
    size_t m_LastTurn = 0;
    CBoard & m_Board;
public:
    explicit CPiece(CBoard & board, const CCoord & coord, EPiece piece, EColor color);

    virtual ~CPiece() = default;

//    virtual std::set<CCoord> Moveset() = 0;

    virtual std::ostream & Print(std::ostream & os) const = 0;

    friend std::ostream & operator<<(std::ostream & os, const CPiece & self);

    const CCoord & GetCoord() const {
        return m_Coord;
    }

    EPiece GetName() const {
        return m_Piece;
    }

    EColor GetColor() const {
        return m_Color;
    }
};



