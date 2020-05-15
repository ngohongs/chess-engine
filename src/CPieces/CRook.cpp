/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#include "CRook.h"


CRook::CRook(CBoard *board, const CCoord &coord, EColor color)
: CPiece(board, coord, EPiece::ROOK, color) {
}

