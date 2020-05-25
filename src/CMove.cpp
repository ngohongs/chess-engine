/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 25/05/2020.
 */

#include "CMove.h"

CMove::CMove(int from, int to, EPiece capture, bool pawnStart, bool enPassant, EPiece promotion, bool castle)
: m_From(from), m_To(to), m_Capture(capture), m_PawnStarting(pawnStart), m_EnPassant(enPassant), m_Promotion(promotion), m_Castle(castle) {
}

std::ostream & CMove::Print(std::ostream & os) {
    os << IndexToTile(m_From) << IndexToTile(m_To);
    if (m_Promotion != EPiece::EMPTY)
        os << m_Promotion;
    return os;
}
