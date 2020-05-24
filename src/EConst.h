/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 24/05/2020.
 */

#pragma once


const char * const START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

const char PIECE_CODES[12] = {'p', 'n', 'b', 'r', 'q' ,'k', 'P', 'N', 'B', 'R', 'Q', 'K'};
const unsigned int WHITE_KING_CASTLE = 0x8;
const unsigned int WHITE_QUEEN_CASTLE = 0x4;
const unsigned int BLACK_KING_CASTLE = 0x2;
const unsigned int BLACK_QUEEN_CASTLE = 0x1;
const unsigned int NO_CASTLE = 0x0;