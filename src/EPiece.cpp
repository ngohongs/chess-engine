/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 25/05/2020.
 */

#include "EPiece.h"


std::ostream & operator<<(std::ostream & os, const EPiece & self) {
    if (self == EPiece::PAWN)
        return os << 'p';
    else if (self == EPiece::KNIGHT)
        return os << 'n';
    else if (self == EPiece::ROOK)
        return os << 'r';
    else if (self == EPiece::BISHOP)
        return os << 'b';
    else if (self == EPiece::QUEEN)
        return os << 'q';
    else if (self == EPiece::KING)
        return os << 'k';
    else if (self == EPiece::EMPTY)
        return os << '.';
    else
        return os << '-';
}

int EPieceToCode(EPiece piece) {
    switch (piece) {
        case EPiece::PAWN:
            return 0;
        case EPiece::KNIGHT:
            return 1;
        case EPiece::BISHOP:
            return 2;
        case EPiece::ROOK:
            return 3;
        case EPiece::QUEEN:
            return 4;
        case EPiece::KING:
            return 5;
        default:
            throw std::logic_error("No code for empty or offboard");
    }
}