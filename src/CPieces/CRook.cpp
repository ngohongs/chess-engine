/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#include "CRook.h"
#include "../CBoard.h"


CRook::CRook(CBoard & board, const CCoord &coord, EColor color)
: CPiece(board, coord, EPiece::ROOK, color) {
}

std::ostream & CRook::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? "\u2656" : "\u265c");
}

