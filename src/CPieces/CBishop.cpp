/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#include "CBishop.h"
#include "../CBoard.h"


CBishop::CBishop(CBoard & board, const CCoord & coord, EColor color)
: CPiece(board, coord, EPiece::BISHOP, color) {
}

std::ostream & CBishop::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? "\u2657" : "\u265d");
}

