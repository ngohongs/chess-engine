/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#include "CBoard.h"


CBoard::CBoard() {
    m_Board.resize(8);
    for (int i = 0; i < 8; i++)
        m_Board[i].resize(8);

    m_Board[0][0] = std::make_unique<CRook>(CRook(*this, CCoord(0, 0), EColor::BLACK));
    m_Board[0][1] = std::make_unique<CKnight>(CKnight(*this, CCoord(0, 1), EColor::BLACK));
    m_Board[0][2] = std::make_unique<CBishop>(CBishop(*this, CCoord(0, 2), EColor::BLACK));
    m_Board[0][3] = std::make_unique<CQueen>(CQueen(*this, CCoord(0, 3), EColor::BLACK));
    m_Board[0][4] = std::make_unique<CKing>(CKing(*this, CCoord(0, 4), EColor::BLACK));
    m_Board[0][5] = std::make_unique<CBishop>(CBishop(*this, CCoord(0, 5), EColor::BLACK));
    m_Board[0][6] = std::make_unique<CKnight>(CKnight(*this, CCoord(0, 6), EColor::BLACK));
    m_Board[0][7] = std::make_unique<CRook>(CRook(*this, CCoord(0, 7), EColor::BLACK));
    for (int i = 0; i < 8; i++)
        m_Board[1][i] = std::make_unique<CPawn>(CPawn(*this, CCoord(1, i), EColor::BLACK));

    m_Board[7][0] = std::make_unique<CRook>(CRook(*this, CCoord(7, 0), EColor::WHITE));
    m_Board[7][1] = std::make_unique<CKnight>(CKnight(*this, CCoord(7, 1), EColor::WHITE));
    m_Board[7][2] = std::make_unique<CBishop>(CBishop(*this, CCoord(7, 2), EColor::WHITE));
    m_Board[7][3] = std::make_unique<CQueen>(CQueen(*this, CCoord(7, 3), EColor::WHITE));
    m_Board[7][4] = std::make_unique<CKing>(CKing(*this, CCoord(7, 4), EColor::WHITE));
    m_Board[7][5] = std::make_unique<CBishop>(CBishop(*this, CCoord(7, 5), EColor::WHITE));
    m_Board[7][6] = std::make_unique<CKnight>(CKnight(*this, CCoord(7, 6), EColor::WHITE));
    m_Board[7][7] = std::make_unique<CRook>(CRook(*this, CCoord(7, 7), EColor::WHITE));
    for (int i = 0; i < 8; i++)
        m_Board[6][i] = std::make_unique<CPawn>(CPawn(*this, CCoord(6, i), EColor::WHITE));
}

std::ostream & CBoard::Print(std::ostream & os) const {
    os << "    A B C D E F G H" << std::endl;
    os << "  +-----------------+" << std::endl;
    for (int i = 0; i < 8; i++) {
        os << i + 1 << " | ";
        for (int j = 0; j < 8; j++) {
            if (m_Board[i][j])
                os << *m_Board[i][j] << ' ';
            else
                os << ". ";
        }
        os << "| " << i + 1 << std::endl;
    }
    os << "  +-----------------+" << std::endl;
    os << "    A B C D E F G H" << std::endl;
    return os;
}
