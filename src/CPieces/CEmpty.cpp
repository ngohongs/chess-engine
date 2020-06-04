/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 23/05/2020.
 */

#include "CEmpty.h"

CEmpty::CEmpty(CBoard & board, int coord)
: CPiece(board, coord, EPiece::EMPTY, EColor::NONE, EMPTY) {
}

std::ostream & CEmpty::Print(std::ostream & os) const {
    return os << '.';
}

std::list<CMove> CEmpty::MoveList() const {
    return std::list<CMove>();
}

std::list<CMove> CEmpty::CaptureMoveList() const {
    return std::list<CMove>();
}
