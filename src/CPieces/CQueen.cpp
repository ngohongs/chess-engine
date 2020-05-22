/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#include "CQueen.h"
#include "../CBoard.h"


CQueen::CQueen(CBoard & board, const CCoord & coord, EColor color)
: CPiece(board, coord, EPiece::QUEEN, color) {
}

std::ostream & CQueen::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? "\u2655" : "\u265b");
}
