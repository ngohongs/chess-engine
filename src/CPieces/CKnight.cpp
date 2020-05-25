/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#include "CKnight.h"
#include "../CBoard.h"


CKnight::CKnight(CBoard & board, int coord, EColor color)
: CPiece(board, coord, EPiece::KNIGHT, color, color == EColor::WHITE ? N : n) {
}

std::ostream & CKnight::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? 'N' : 'n');
    //return os << (m_Color == EColor::WHITE ? "\u2658" : "\u265e");
}
