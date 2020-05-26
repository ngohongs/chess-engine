/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 22/05/2020.
 */

#include "CPawn.h"
#include "../CBoard.h"


CPawn::CPawn(CBoard & board, int coord, EColor color)
: CPiece(board, coord, EPiece::PAWN, color, color == EColor::WHITE ? P : p) {
}

std::ostream & CPawn::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? 'P' : 'p');
    //return os << (m_Color == EColor::WHITE ? "\u2659" : "\u265f");
}

std::list<CMove> CPawn::MoveList() const {
    std::list<CMove> moveList;
    
    int forward = m_Color == EColor::WHITE ? 10 : -10;
    int diagonalOne = m_Color == EColor::WHITE ? 9 : -9;
    int diagonalTwo = m_Color == EColor::WHITE ? 11 : -11;
    EColor oppositeSide = m_Color == EColor::WHITE ? EColor::BLACK : EColor::WHITE;
    int startRank = m_Color == EColor::WHITE ? RANK_2 : RANK_7;
    int promotionRank = m_Color == EColor::WHITE ? RANK_7 : RANK_2;
    //Push move
    if (m_Board.IsEmpty(m_Coord + forward)) {
        if (GetRank(m_Coord) == promotionRank) {
            moveList.push_back(PromotionMove(m_Coord, m_Coord + forward, EPiece::EMPTY, EPiece::QUEEN));
            moveList.push_back(PromotionMove(m_Coord, m_Coord + forward, EPiece::EMPTY, EPiece::ROOK));
            moveList.push_back(PromotionMove(m_Coord, m_Coord + forward, EPiece::EMPTY, EPiece::BISHOP));
            moveList.push_back(PromotionMove(m_Coord, m_Coord + forward, EPiece::EMPTY, EPiece::KNIGHT));
        }
        else {
            moveList.push_back(PushMove(m_Coord, m_Coord + forward));
            if (GetRank(m_Coord) == startRank && m_Board.IsEmpty(m_Coord + 2 * forward)) {
                moveList.push_back(PawnTwoForward(m_Coord, m_Coord + 2 * forward));
            }
        }
    }

    //Capture moves
    if (!m_Board.IsOffboard(m_Coord + diagonalOne) && m_Board[m_Coord + diagonalOne]->GetColor() == oppositeSide) {
        if (GetRank(m_Coord) == promotionRank) {
            moveList.push_back(PromotionMove(m_Coord, m_Coord + diagonalOne, m_Board[m_Coord + diagonalOne]->GetPiece(),
                                             EPiece::QUEEN));
            moveList.push_back(PromotionMove(m_Coord, m_Coord + diagonalOne, m_Board[m_Coord + diagonalOne]->GetPiece(),
                                             EPiece::ROOK));
            moveList.push_back(PromotionMove(m_Coord, m_Coord + diagonalOne, m_Board[m_Coord + diagonalOne]->GetPiece(),
                                             EPiece::BISHOP));
            moveList.push_back(PromotionMove(m_Coord, m_Coord + diagonalOne, m_Board[m_Coord + diagonalOne]->GetPiece(),
                                             EPiece::KNIGHT));
        }
        else
            moveList.push_back(CaptureMove(m_Coord, m_Coord + diagonalOne, m_Board[m_Coord + diagonalOne]->GetPiece()));
    }
    if (!m_Board.IsOffboard(m_Coord + diagonalTwo) && m_Board[m_Coord + diagonalTwo]->GetColor() == oppositeSide) {
        if (GetRank(m_Coord) == promotionRank) {
            moveList.push_back(PromotionMove(m_Coord, m_Coord + diagonalTwo, m_Board[m_Coord + diagonalTwo]->GetPiece(),
                                             EPiece::QUEEN));
            moveList.push_back(PromotionMove(m_Coord, m_Coord + diagonalTwo, m_Board[m_Coord + diagonalTwo]->GetPiece(),
                                             EPiece::ROOK));
            moveList.push_back(PromotionMove(m_Coord, m_Coord + diagonalTwo, m_Board[m_Coord + diagonalTwo]->GetPiece(),
                                             EPiece::BISHOP));
            moveList.push_back(PromotionMove(m_Coord, m_Coord + diagonalTwo, m_Board[m_Coord + diagonalTwo]->GetPiece(),
                                             EPiece::KNIGHT));
        }
        else
            moveList.push_back(CaptureMove(m_Coord, m_Coord + diagonalTwo, m_Board[m_Coord + diagonalTwo]->GetPiece()));
    }

    //En Passant capture
    if (m_Coord + diagonalOne == m_Board.GetEnPassant())
        moveList.push_back(CaptureMove(m_Coord, m_Coord + diagonalOne, EPiece::PAWN, true));
    if (m_Coord + diagonalTwo == m_Board.GetEnPassant())
        moveList.push_back(CaptureMove(m_Coord, m_Coord + diagonalTwo, EPiece::PAWN, true));
    return moveList;
}
