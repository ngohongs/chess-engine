/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 25/05/2020.
 */

#include "COffboard.h"

COffboard::COffboard(CBoard & board, int coord)
: CPiece(board, coord, EPiece::OFFBOARD, EColor::NONE, EMPTY) {
}

std::ostream & COffboard::Print(std::ostream & os) const {
    return os << '-';
}

std::list<CMove> COffboard::MoveList() const {
    return std::list<CMove>();
}
