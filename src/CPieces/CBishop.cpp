/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#include "CBishop.h"
#include "../CBoard.h"


CBishop::CBishop(CBoard & board, int coord, EColor color)
: CPiece(board, coord, EPiece::BISHOP, color, color == EColor::WHITE ? B : b) {
}

std::ostream & CBishop::Print(std::ostream & os) const {
    return os << (m_Color == EColor::WHITE ? 'B' : 'b');
    //return os << (m_Color == EColor::WHITE ? "\u2657" : "\u265d");
}

std::list<CMove> CBishop::MoveList() const {
    std::list<CMove> moveList;
    int tempTile;
    EColor oppositeSide = OppositeSide(m_Color);
    EPiece piece;
    EColor color;
    //Rook attacks
    for (int i : BISHOP_ATTACKS) {
        tempTile = m_Coord + i;
        while (!m_Board.IsOffboard(tempTile)) {
            piece = m_Board[tempTile]->GetPiece();
            color = m_Board[tempTile]->GetColor();
            if (piece == EPiece::EMPTY)
                moveList.push_back(PushMove(m_Color, m_Coord, tempTile));

            if (piece != EPiece::EMPTY) {
                if (color == oppositeSide)
                    moveList.push_back(CaptureMove(m_Color, m_Coord, tempTile, m_Board[tempTile]->GetPiece(),
                                                   false));
                break;
            }
            tempTile += i;
        }
    }
    return moveList;
}
