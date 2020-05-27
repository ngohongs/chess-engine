/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#include "CPiece.h"
//#include "CBoard.h"

//CPiece::CPiece(const CCoord & coord, EPiece piece, EColor color)
//: m_Coord(coord), m_Piece(piece), m_Color(color) {
//}

CPiece::CPiece(CBoard & board, int coord, EPiece piece, EColor color, int code)
: m_Board(board), m_Coord(coord), m_Piece(piece), m_Color(color), m_PieceCode(code) {
}

std::ostream & operator<<(std::ostream & os, const CPiece & self) {
    return self.Print(os);
}

size_t CPiece::GetLastTurn() const {
    return m_LastTurn;
}

void CPiece::SetCoord(int index) {
    m_Coord = index;
}

