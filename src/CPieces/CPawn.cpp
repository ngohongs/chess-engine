/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#include "CPawn.h"


CPawn::CPawn(CBoard * board, const CCoord & coord, EColor color)
: CPiece(board, coord, EPiece::PAWN, color) {
}
