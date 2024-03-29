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
    // Go through all king move patterns
    for (const auto & i : KING_ATTACKS) {
        if (m_Board.IsOffboard(m_Coord + i))
            continue;
        // Push move
        if (m_Board.IsEmpty(m_Coord + i))// && !KingNeighbour(m_Coord + i))
            moveList.push_back(PushMove(m_Color, m_Coord, m_Coord + i));
        // Capture move
        if (m_Board[m_Coord + i]->GetColor() == oppositeSide)
            moveList.push_back(CaptureMove(m_Piece, m_Color, m_Coord, m_Coord + i, m_Board[m_Coord + i]->GetPiece(),
                                           false));
    }

    // Castling
    if (m_Board.GetCastling()) {
        if (m_Color == EColor::WHITE) {
            if (m_Board.GetCastling() & WHITE_KING_CASTLE) {
                if (m_Board[H1]->GetCode() == R) {
                    if (m_Board.IsEmpty(F1) && m_Board.IsEmpty(G1)) {
                        if (!m_Board.TileAttacked(EColor::BLACK, E1) && !m_Board.TileAttacked(EColor::BLACK, F1)) {
                            moveList.push_back(CastleMove(EColor::WHITE, WHITE_KING_CASTLE));
                        }
                    }
                }
            }
            if (m_Board.GetCastling() & WHITE_QUEEN_CASTLE) {
                if (m_Board[A1]->GetCode() == R) {
                    if (m_Board.IsEmpty(B1) && m_Board.IsEmpty(C1) && m_Board.IsEmpty(D1)) {
                        if (!m_Board.TileAttacked(EColor::BLACK, D1) && !m_Board.TileAttacked(EColor::BLACK, E1)) {
                            moveList.push_back(CastleMove(EColor::WHITE, WHITE_QUEEN_CASTLE));
                        }
                    }
                }
            }
        } else {
            if (m_Board.GetCastling() & BLACK_KING_CASTLE) {
                if (m_Board[H8]->GetCode() == r) {
                    if (m_Board.IsEmpty(F8) && m_Board.IsEmpty(G8)) {
                        if (!m_Board.TileAttacked(EColor::WHITE, E8) && !m_Board.TileAttacked(EColor::WHITE, F8)) {
                            moveList.push_back(CastleMove(EColor::BLACK, BLACK_KING_CASTLE));
                        }
                    }
                }
            }
            if (m_Board.GetCastling() & BLACK_QUEEN_CASTLE) {
                if (m_Board[A8]->GetCode() == r) {
                    if (m_Board.IsEmpty(B8) && m_Board.IsEmpty(C8) && m_Board.IsEmpty(D8)) {
                        if (!m_Board.TileAttacked(EColor::WHITE, D8) && !m_Board.TileAttacked(EColor::WHITE, E8)) {
                            moveList.push_back(CastleMove(EColor::BLACK, BLACK_QUEEN_CASTLE));
                        }
                    }
                }
            }
        }
    }

    return moveList;
}

bool CKing::KingNeighbour(int index) const {
    EColor oppositeSide = OppositeSide(m_Color);
    for (const auto & i : KING_ATTACKS)
        if (m_Board[index + i]->GetPiece() == EPiece::KING && m_Board[index + i]->GetColor() == oppositeSide)
            return true;
    return false;
}

std::list<CMove> CKing::CaptureMoveList() const {
    std::list<CMove> moveList;
    EColor oppositeSide = m_Color == EColor::WHITE ? EColor::BLACK : EColor::WHITE;
    for (const auto & i : KING_ATTACKS) {
        if (m_Board.IsOffboard(m_Coord + i))
            continue;

        // Capture move
        if (m_Board[m_Coord + i]->GetColor() == oppositeSide)
            moveList.push_back(CaptureMove(m_Piece, m_Color, m_Coord, m_Coord + i, m_Board[m_Coord + i]->GetPiece(),
                                           false));
    }
    return moveList;
}

