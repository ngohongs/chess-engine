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
//    os << (m_Side == EColor::WHITE ? 'w' : 'b');
    os << IndexToTile(m_From) << IndexToTile(m_To);
    if (m_Promotion != EPiece::EMPTY)
        os << m_Promotion;
//    else
//        os << '-';
//
//    if (m_Capture != EPiece::EMPTY)
//        os << m_Capture;
//    else
//        os << '-';
//
//    os << (m_Castle ? 'C' : '-' );
//    os << (m_PawnTwoPush ? '2' : '-');
//    os << (m_EnPassant ? 'E' : '-');
    return os;
}

std::ostream & operator<<(std::ostream & os, const CMove & self) {
    self.Print(os);
    return os;
}

std::istream & operator>>(std::istream & is, CMove & self) {
    std::string input;
    is >> input;
    input.push_back('\n');

    char fromFile;
    char fromRank;
    char toFile;
    char toRank;
    char promotion;

    if (sscanf(input.c_str(), "%c%c%c%c%c ", &fromFile, &fromRank, &toFile, &toRank, &promotion) != 5) {
        is.setstate(std::ios::failbit);
        return is;
    }

    std::string from = "";
    from.push_back(fromFile);
    from.push_back(fromRank);

    std::string to = "";
    to.push_back(toFile);
    to.push_back(toRank);

    if (TileToIndex(from) == OFFBOARD || TileToIndex(to) == OFFBOARD ) {
        is.setstate(std::ios::failbit);
        return is;
    }

    self.m_From = TileToIndex(from);
    self.m_To = TileToIndex(to);

    if (promotion == '\n')
        return is;


    if (promotion != 'q' && promotion != 'r' && promotion != 'b' && promotion != 'n') {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (promotion == 'q')
        self.m_Promotion = EPiece::QUEEN;
    else if (promotion == 'r')
        self.m_Promotion = EPiece::ROOK;
    else if (promotion == 'b')
        self.m_Promotion = EPiece::BISHOP;
    else
        self.m_Promotion = EPiece::KNIGHT;

    return is;
}

bool CMove::operator==(const CMove & other) const {
    if (m_From != other.m_From)
        return false;
    if (m_To != other.m_To)
        return false;
    if (m_Promotion != other.m_Promotion)
        return false;
    return true;
}

bool CMove::IsValid() const {
    return m_From != OFFBOARD && m_To != OFFBOARD;
}

bool CMove::ExactMatch(const CMove & other) const {
    if (m_Side != other.m_Side)
        return false;
    if (m_From != other.m_From)
        return false;
    if (m_To != other.m_To)
        return false;
    if (m_Promotion != other.m_Promotion)
        return false;
    if (m_Capture != other.m_Capture)
        return false;
    if (m_PawnTwoPush != other.m_PawnTwoPush)
        return false;
    if (m_EnPassant != other.m_EnPassant)
        return false;
    if (m_Castle != other.m_Castle)
        return false;
    return true;
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
    return CMove(color, from, to, capture, false, enPassant, EPiece::EMPTY, false, 100);
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
