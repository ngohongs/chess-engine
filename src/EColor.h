/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include <iostream>
#include <stdexcept>



/**
 * Enum class for representing color of the piece
 */
enum class EColor : char {
    WHITE = 'W',
    BLACK = 'B',
    NONE = ' '
};

/**
 * Opposite side of the color
 * @param self, opposite side to self
 * @return opposite side
 */
EColor OppositeSide(EColor self);

/**
 * Outputting color
 * @param os output stream
 * @param color to be output
 * @return std::ostream & after output
 */
std::ostream & operator<<(std::ostream & os, EColor color);
