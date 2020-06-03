/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#include "CQueen.h"
#include "../CBoard.h"


CQueen::CQueen(CBoard & board, int coord, EColor color)
: CPiece(board, coord, EPiece::QUEEN, color, color == EColor::WHITE ? Q : q) {
}

std::ostream & CQueen::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? 'Q' : 'q');
    //return os << (m_Color == EColor::WHITE ? "\u2655" : "\u265b");
}

std::list<CMove> CQueen::MoveList() const {
    std::list<CMove> moveList;
    int tempTile;
    EColor oppositeSide = OppositeSide(m_Color);
    EPiece piece;
    EColor color;
    //Rook attacks
    for (int i : KING_ATTACKS) {
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
