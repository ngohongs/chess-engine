/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 22/05/2020.
 */

#include "CPawn.h"
#include "../CBoard.h"


CPawn::CPawn(CBoard & board, const CCoord & coord, EColor color)
: CPiece(board, coord, EPiece::PAWN, color) {
}

std::ostream & CPawn::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? "\u2659" : "\u265f");
}
