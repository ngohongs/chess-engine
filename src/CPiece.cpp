/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#include "CPiece.h"
//#include "CBoard.h"

//CPiece::CPiece(const CCoord & coord, EPiece piece, EColor color)
//: m_Coord(coord), m_Piece(piece), m_Color(color) {
//}

CPiece::CPiece(CBoard & board, int coord, EPiece piece, EColor color)
: m_Board(board), m_Coord(coord), m_Piece(piece), m_Color(color) {
}

std::ostream & operator<<(std::ostream & os, const CPiece & self) {
    return self.Print(os);
}

