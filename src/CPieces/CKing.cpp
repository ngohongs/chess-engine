/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#include "CKing.h"
#include "../CBoard.h"


CKing::CKing(CBoard & board, int coord, EColor color)
: CPiece(board, coord, EPiece::KING, color) {
}

std::ostream & CKing::Print(std::ostream & os) const {
        return os << (m_Color == EColor::WHITE ? 'K' : 'k');
        //return os << (m_Color == EColor::WHITE ? "\u2654" : "\u265a");
}

char CKing::GetCode() const {
    return m_Color == EColor::WHITE ? 'K' : 'k';
}
