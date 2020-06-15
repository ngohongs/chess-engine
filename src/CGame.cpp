/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#include "CGame.h"


std::ostream & operator<<(std::ostream & os, const CGame & self) {
    if (self.m_Board.GetSide() == EColor::WHITE)
        self.m_Interface.PromptMessage("Side to turn: WHITE\n");
    else
        self.m_Interface.PromptMessage("Side to turn: BLACK\n");
    return self.m_Board.Print(os);
}

CGame::CGame(CInterface & interface)
: m_Interface(interface),
  m_White(std::make_shared<CPlayerAI>(interface, m_Board, EColor::WHITE, 2)),
  m_Black(std::make_shared<CPlayerHuman>(interface, m_Board, EColor::BLACK)) {
    m_Interface.GetOstream() << m_Board;
    if (m_Board.GetSide() == EColor::WHITE ? m_White->IsComputer() : m_Black->IsComputer())
        m_End = !MakeTurn();
}

bool CGame::MakeTurn() {
    if (m_End)
        return false;
    if (!(m_Board.GetSide() == EColor::WHITE ? m_White->TakeTurn() : m_Black->TakeTurn())) {
        m_End = true;
        return false;
    }
    m_Interface.GetOstream() << m_Board;
    if (m_Board.GetSide() == EColor::WHITE ? m_White->IsComputer() : m_Black->IsComputer()) {
        if (!(m_Board.GetSide() == EColor::WHITE ? m_White->TakeTurn() : m_Black->TakeTurn())) {
            m_End = true;
            return false;
        }
    }
    return true;
}
