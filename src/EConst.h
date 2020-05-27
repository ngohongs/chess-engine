/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 24/05/2020.
 */

#pragma once


const char * const START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

enum {p, n, b, r, q , k, P, N, B, R, Q, K, EMPTY};

const char PIECE_CHAR_CODE[13] = {'p', 'n', 'b', 'r', 'q', 'k', 'P', 'N', 'B', 'R', 'Q', 'K', ' '};
const int PIECE_SCORE[13] = {100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000, 0};

const int KNIGHT_ATTACKS[8] = {-21, -19, -12, -8, 8, 12, 19, 21};
const int ROOK_ATTACKS[4] = {-10, -1, 1, 10};
const int BISHOP_ATTACKS[4] = {-11, -9, 9, 11};
const int KING_ATTACKS[8] = {-11, -10, -9, -1, 1, 9, 10, 11};

const unsigned int WHITE_KING_CASTLE = 0x8;
const unsigned int WHITE_QUEEN_CASTLE = 0x4;
const unsigned int BLACK_KING_CASTLE = 0x2;
const unsigned int BLACK_QUEEN_CASTLE = 0x1;
const unsigned int NO_CASTLE = 0x0;