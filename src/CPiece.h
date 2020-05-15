/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include <memory>
#include <set>
#include "CCoord.h"
#include "EColor.h"
#include "EPiece.h"
#include "CBoard.h"


class CPiece {
protected:
    CCoord m_Coord;
    EPiece m_Piece;
    EColor m_Color;
    size_t m_LastTurn = 0;
    CBoard * m_Board;
public:
    explicit CPiece(CBoard * board, const CCoord & coord, EPiece piece, EColor color);

    virtual ~CPiece() = default;

//    virtual std::set<CCoord> MoveSet() const = 0;
//
//    bool Move(const CCoord & destination);

    CCoord & GetCoord() const;

    EPiece GetName() const;

    EColor GetColor() const;
};



