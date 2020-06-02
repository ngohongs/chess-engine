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
  m_White(std::make_shared<CPlayerHuman>(interface, m_Board, EColor::BLACK)),
  m_Black(std::make_shared<CPlayerAI>(interface, m_Board, EColor::WHITE)) {
}

bool CGame::MakeTurn() {
    return m_Board.GetSide() == EColor::WHITE ? m_White->TakeTurn() : m_Black->TakeTurn();
}
