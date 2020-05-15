/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#include "CPiece.h"


CPiece::CPiece(CBoard * board, const CCoord & coord, EPiece piece, EColor color)
: m_Board(board), m_Coord(coord), m_Piece(piece), m_Color(color) {
}
