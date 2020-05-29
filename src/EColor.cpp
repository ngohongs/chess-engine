/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 26/05/2020.
 */

#include "EColor.h"


EColor OppositeSide(EColor self) {
    if (self == EColor::NONE)
        throw std::logic_error("NONE is not color");
    return self == EColor::WHITE ? EColor::BLACK : EColor::WHITE;
}

std::ostream & operator<<(std::ostream & os, EColor color) {
    return os << (color == EColor::WHITE ? "WHITE" : "BLACK");
}
