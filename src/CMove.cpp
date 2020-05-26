/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 25/05/2020.
 */

#include "CMove.h"

CMove::CMove(int from, int to, EPiece capture, bool pawnTwoPush, bool enPassant, EPiece promotion, bool castle, int score)
: m_From(from), m_To(to), m_Capture(capture), m_PawnTwoPush(pawnTwoPush), m_EnPassant(enPassant), m_Promotion(promotion), m_Castle(castle), m_Score(score) {
}

std::ostream & CMove::Print(std::ostream & os) const {
    os << IndexToTile(m_From) << IndexToTile(m_To);
    if (m_Promotion != EPiece::EMPTY)
        os << m_Promotion;
    return os;
}

CMove PushMove(int from, int to) {
    return CMove(from, to);
}

CMove PromotionMove(int from, int to, EPiece capture, EPiece promotion) {
    return CMove(from, to, capture, false, false, promotion, false, 0);
}

CMove PawnTwoForward(int from, int to) {
    return CMove(from, to, EPiece::EMPTY, true);
}

CMove CaptureMove(int from, int to, EPiece capture, bool enPassant) {
    return CMove(from, to, capture, enPassant);
}
