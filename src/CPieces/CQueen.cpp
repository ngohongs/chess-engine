/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#include "CQueen.h"
#include "../CBoard.h"


CQueen::CQueen(CBoard & board, int coord, EColor color)
: CPiece(board, coord, EPiece::QUEEN, color) {
}

std::ostream & CQueen::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? 'Q' : 'q');
    //return os << (m_Color == EColor::WHITE ? "\u2655" : "\u265b");
}

char CQueen::GetCode() const {
    return m_Color == EColor::WHITE ? 'Q' : 'q';
}
