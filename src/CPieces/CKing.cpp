/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#include "CKing.h"
#include "../CBoard.h"


CKing::CKing(CBoard & board, int coord, EColor color)
: CPiece(board, coord, EPiece::KING, color, color == EColor::WHITE ? K : k) {
}

std::ostream & CKing::Print(std::ostream & os) const {
        return os << (m_Color == EColor::WHITE ? 'K' : 'k');
        //return os << (m_Color == EColor::WHITE ? "\u2654" : "\u265a");
}

std::list<CMove> CKing::MoveList() const {
    std::list<CMove> moveList;
    EColor oppositeSide = m_Color == EColor::WHITE ? EColor::BLACK : EColor::WHITE;
    for (const auto & i : KING_ATTACKS) {
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

