/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include <stdexcept>
#include <iostream>

enum class EColor : char {
    WHITE = 'W',
    BLACK = 'B',
    NONE = ' '
};

EColor OppositeSide(EColor self);

std::ostream & operator<<(std::ostream & os, EColor color);
