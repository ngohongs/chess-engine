/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#include "CKnight.h"
#include "../CBoard.h"


CKnight::CKnight(CBoard & board, int coord, EColor color)
: CPiece(board, coord, EPiece::KNIGHT, color, color == EColor::WHITE ? N : n) {
}

std::ostream & CKnight::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? 'N' : 'n');
    //return os << (m_Color == EColor::WHITE ? "\u2658" : "\u265e");
}

std::list<CMove> CKnight::MoveList() const {
    std::list<CMove> moveList;
    EColor oppositeSide = m_Color == EColor::WHITE ? EColor::BLACK : EColor::WHITE;
    for (const auto & i : KNIGHT_ATTACKS) {
        if (m_Board.IsOffboard(m_Coord + i))
            continue;
        // Push move
        if (m_Board.IsEmpty(m_Coord + i))
            moveList.push_back(PushMove(m_Coord, m_Coord + i));
        // Capture move
        if (m_Board[m_Coord + i]->GetColor() == oppositeSide)
            moveList.push_back(CaptureMove(m_Coord, m_Coord + i, m_Board[m_Coord + i]->GetPiece()));
    }
    return moveList;
}