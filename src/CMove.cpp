/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 25/05/2020.
 */

#include "CMove.h"

CMove::CMove(EColor color, int from, int to, EPiece capture, bool pawnStart, bool enPassant, EPiece promotion,
             bool castle,
             int score)
: m_Side(color), m_From(from), m_To(to), m_Capture(capture), m_PawnTwoPush(pawnStart), m_EnPassant(enPassant), m_Promotion(promotion), m_Castle(castle), m_Score(score) {
}

std::ostream & CMove::Print(std::ostream & os) const {
    os << IndexToTile(m_From) << IndexToTile(m_To);
    if (m_Promotion != EPiece::EMPTY)
        os << m_Promotion;
    return os;
}

CMove PushMove(EColor color, int from, int to) {
    return CMove(color, from, to, EPiece::EMPTY, false, false, EPiece::EMPTY, false, 0);
}

CMove PromotionMove(EColor color, int from, int to, EPiece capture, EPiece promotion) {
    return CMove(color, from, to, capture, false, false, promotion, false, 0);
}

CMove PawnTwoForward(EColor color, int from, int to) {
    return CMove(color, from, to, EPiece::EMPTY, true, false, EPiece::EMPTY, false, 0);
}

CMove CaptureMove(EColor color, int from, int to, EPiece capture, bool enPassant) {
    return CMove(color, from, to, capture, enPassant, false, EPiece::EMPTY, false, 0);
}

CMove CastleMove(EColor color, int castling) {
    if (castling & WHITE_KING_CASTLE)
        return CMove(color, E1, G1, EPiece::EMPTY, false, false, EPiece::EMPTY, true, 0);
    else if (castling & WHITE_QUEEN_CASTLE)
        return CMove(color, E1, C1, EPiece::EMPTY, false, false, EPiece::EMPTY, true, 0);
    else if (castling & BLACK_KING_CASTLE)
        return CMove(color, E8, G8, EPiece::EMPTY, false, false, EPiece::EMPTY, true, 0);
    else if (castling & BLACK_QUEEN_CASTLE)
        return CMove(color, E8, C8, EPiece::EMPTY, false, false, EPiece::EMPTY, true, 0);
    else
        throw std::logic_error("Cannot castle");
}
