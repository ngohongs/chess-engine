/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#include "CRook.h"
#include "../CBoard.h"


CRook::CRook(CBoard & board, int coord, EColor color)
: CPiece(board, coord, EPiece::ROOK, color, color == EColor::WHITE ? R : r) {
}

std::ostream & CRook::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? 'R' : 'r');
    //return os << (m_Color == EColor::WHITE ? "\u2656" : "\u265c");
}

std::list<CMove> CRook::MoveList() const {
    std::list<CMove> moveList;
    int tempTile;
    EColor oppositeSide = OppositeSide(m_Color);
    EPiece piece;
    EColor color;
    // Rook attacks
    // For each direction go until a capture or border
    for (int i : ROOK_ATTACKS) {
        tempTile = m_Coord + i;
        while (!m_Board.IsOffboard(tempTile)) {
            piece = m_Board[tempTile]->GetPiece();
            color = m_Board[tempTile]->GetColor();
            if (piece == EPiece::EMPTY)
                moveList.push_back(PushMove(m_Color, m_Coord, tempTile));

            if (piece != EPiece::EMPTY) {
                if (color == oppositeSide)
                    moveList.push_back(CaptureMove(m_Piece, m_Color, m_Coord, tempTile, m_Board[tempTile]->GetPiece(),
                                                   false));
                break;
            }
            tempTile += i;
        }
    }
    return moveList;
}

// Same as MoveList only for captures
std::list<CMove> CRook::CaptureMoveList() const {
    std::list<CMove> moveList;
    int tempTile;
    EColor oppositeSide = OppositeSide(m_Color);
    EPiece piece;
    EColor color;
    //Rook attacks
    for (int i : ROOK_ATTACKS) {
        tempTile = m_Coord + i;
        while (!m_Board.IsOffboard(tempTile)) {
            piece = m_Board[tempTile]->GetPiece();
            color = m_Board[tempTile]->GetColor();
            if (piece != EPiece::EMPTY) {
                if (color == oppositeSide)
                    moveList.push_back(CaptureMove(m_Piece, m_Color, m_Coord, tempTile, m_Board[tempTile]->GetPiece(),
                                                   false));
                break;
            }
            tempTile += i;
        }
    }
    return moveList;
}
