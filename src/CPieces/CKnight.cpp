/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#include "CKnight.h"

CKnight::CKnight(CBoard * board, const CCoord & coord, EColor color)
: CPiece(board, coord, EPiece::KNIGHT, color) {
}
