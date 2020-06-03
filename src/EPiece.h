/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#pragma once

#include <iostream>

enum class EPiece : char {
    KING = 'K',
    QUEEN = 'Q',
    ROOK = 'R',
    BISHOP = 'B',
    KNIGHT = 'N',
    PAWN = 'P',
    EMPTY = '.',
    OFFBOARD = ' '
};

int EPieceToCode(EPiece piece);

std::ostream & operator<< (std::ostream & os, const EPiece & self);
