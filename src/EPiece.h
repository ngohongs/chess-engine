/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#pragma once

#include <iostream>
#include <stdexcept>


/**
 * Enum class representing each element of board
 */
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

/**
 * Get the int representation of a piece used for indexing array
 * @param piece from which to get the int representation, all EPieces apart from EMPTY OFFBOARD
 * @return int representation of the piece
 */
int EPieceToCode(EPiece piece);

/**
 * Outputting EPiece
 * @param os output stream
 * @param self piece to be output
 * @return std::ostream & after output
 */
std::ostream & operator<< (std::ostream & os, const EPiece & self);
