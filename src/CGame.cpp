/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#include "CGame.h"


std::ostream & CGame::Print(std::ostream & os) {
    if (m_Board.GetSide() == EColor::WHITE)
        m_Interface.PromptMessage("Side to turn: WHITE\n");
    else
        m_Interface.PromptMessage("Side to turn: BLACK\n");
    return m_Board.Print(os);
}

CGame::CGame(CInterface & interface)
: m_Interface(interface) {
//    m_Interface.GetOstream() << m_Board;
//    if (m_Board.GetSide() == EColor::WHITE ? m_White->IsComputer() : m_Black->IsComputer())
//        m_End = !MakeTurn();
}


bool CGame::MakeTurn() {
    if (m_End)
        return false;
    if (!(m_Board.GetSide() == EColor::WHITE ? m_White->TakeTurn() : m_Black->TakeTurn())) {
        m_End = true;
        return false;
    }
    m_Board.Print(m_Interface.GetOstream());
    if (m_Board.GetSide() == EColor::WHITE ? m_White->IsComputer() : m_Black->IsComputer()) {
        if (!(m_Board.GetSide() == EColor::WHITE ? m_White->TakeTurn() : m_Black->TakeTurn())) {
            m_End = true;
            return false;
        }
    }
    return true;
}

bool CGame::InitializePlayerVsPlayer() {
    m_White = std::make_unique<CPlayerHuman>(m_Interface, m_Board, EColor::WHITE);
    m_Black = std::make_unique<CPlayerHuman>(m_Interface, m_Board, EColor::BLACK);

    m_Initialized = true;
    std::cout << *this;
    return true;
}

bool CGame::InitializePlayerVsComputer(EColor computerSide, int difficulty) {
    if (computerSide == EColor::WHITE) {
        m_White = std::make_unique<CPlayerAI>(m_Interface, m_Board, EColor::WHITE, difficulty);
        m_Black = std::make_unique<CPlayerHuman>(m_Interface, m_Board, EColor::BLACK);
    }
    else if (computerSide == EColor::BLACK) {
        m_White = std::make_unique<CPlayerHuman>(m_Interface, m_Board, EColor::WHITE);
        m_Black = std::make_unique<CPlayerAI>(m_Interface, m_Board, EColor::BLACK, difficulty);
    }
    else
        throw std::runtime_error("Error during creating game.");


    m_Board.Print(m_Interface.GetOstream());
    if (m_Board.GetSide() == EColor::WHITE ? m_White->IsComputer() : m_Black->IsComputer()) {
        if (!(m_Board.GetSide() == EColor::WHITE ? m_White->TakeTurn() : m_Black->TakeTurn())) {
            m_End = true;
            return false;
        }
    }

    m_Initialized = true;
    return true;
}

std::ostream & operator<<(std::ostream & os, const CGame & self) {
    os << self.m_Board;
    int difficulty = 0;
    int key = 0;
    if (self.m_White->IsComputer()) {
        key |= 2;
        os << 'c';
        difficulty = self.m_White->GetDifficulty();
    }
    else
        os << 'p';
    if (self.m_Black->IsComputer()) {
        key |= 1;
        os << 'c';
        difficulty = self.m_Black->GetDifficulty();
    }
    else
        os << 'p';
    os << difficulty << ' ' << key << std::endl;
    return os;
}


