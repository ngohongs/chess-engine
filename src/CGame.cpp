/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#include "CGame.h"


CGame::CGame(CInterface & interface)
: m_Interface(interface) {
}


bool CGame::MakeTurn() {
    // If game has ended
    if (m_End) {
        return false;
    }

    // If game has ended after this turn
    if (!(m_Board.GetSide() == EColor::WHITE ? m_White->TakeTurn() : m_Black->TakeTurn())) {
        m_End = true;
        return false;
    }

    // If other player is computer, make its turn
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
        throw std::runtime_error("Error during creating a game.");


    if (m_Board.GetSide() == EColor::WHITE ? m_White->IsComputer() : m_Black->IsComputer()) {
        if (!(m_Board.GetSide() == EColor::WHITE ? m_White->TakeTurn() : m_Black->TakeTurn())) {
            m_End = true;
            return false;
        }
    }

    m_Initialized = true;
    return true;
}

std::ostream & CGame::Print(std::ostream & os) {
    if (m_Board.GetSide() == EColor::WHITE)
        m_Interface.PromptMessage("Side to turn: WHITE\n");
    else
        m_Interface.PromptMessage("Side to turn: BLACK\n");
    m_Board.Print(m_Interface.GetOstream());
    return os;
}

std::ostream & operator<<(std::ostream & os, const CGame & self) {
    os << self.m_Board;
    int difficulty = 1;
    int key = 0;
    if (self.m_White->IsComputer()) {
        // key for checking when loading
        key |= 2;
        os << 'c';
        difficulty = self.m_White->GetDifficulty();
    }
    else
        os << 'p';
    if (self.m_Black->IsComputer()) {
        // key for checking when loading
        key |= 1;
        os << 'c';
        difficulty = self.m_Black->GetDifficulty();
    }
    else
        os << 'p';

    key += difficulty;
    os << difficulty << ':' << key << std::endl;
    return os;
}

std::istream & operator>>(std::istream & is, CGame & self) {

    if (!(is >> self.m_Board)) {
        self.m_Initialized = false;
        return is;
    }

    int difficulty;
    int key = 0;
    int checkKey;
    char playerOne;
    char playerTwo;
    char c;

    if (!(is >> playerOne >> playerTwo >> difficulty >> c >> checkKey)) {
        self.m_Initialized = false;
        return is;
    }

    if (c != ':') {
        is.setstate(std::ios::failbit);
        self.m_Initialized = false;
        return is;
    }

    if (0 >= difficulty || difficulty >= 6) {
        is.setstate(std::ios::failbit);
        self.m_Initialized = false;
        return is;
    }

    key += difficulty;

    if (playerOne == 'c' && playerTwo == 'c') {
        is.setstate(std::ios::failbit);
        self.m_Initialized = false;
        return is;
    }

    if (playerOne == 'p' && playerTwo == 'p' && difficulty != 1) {
        is.setstate(std::ios::failbit);
        self.m_Initialized = false;
        return is;
    }

    if (playerOne == 'p')
        self.m_White = std::make_unique<CPlayerHuman>(self.m_Interface, self.m_Board, EColor::WHITE);
    else if (playerOne == 'c') {
        self.m_White = std::make_unique<CPlayerAI>(self.m_Interface, self.m_Board, EColor::WHITE, difficulty);
        key |= 2;
    }
    else {
        self.m_Initialized = false;
        is.setstate(std::ios::failbit);
        return is;
    }
    if (playerTwo == 'p')
        self.m_Black = std::make_unique<CPlayerHuman>(self.m_Interface, self.m_Board, EColor::BLACK);
    else if (playerTwo == 'c') {
        self.m_Black = std::make_unique<CPlayerAI>(self.m_Interface, self.m_Board, EColor::BLACK, difficulty);
        key |= 1;
    }
    else {
        self.m_Initialized = false;
        is.setstate(std::ios::failbit);
        return is;
    }

    // if keys do not match
    if (key != checkKey) {
        self.m_Initialized = false;
        is.setstate(std::ios::failbit);
        return is;
    }

    self.m_Initialized = true;
    return is;
}

void CGame::Restart() {
    m_White = nullptr;
    m_Black = nullptr;
    m_Initialized = false;
    m_End = false;
    m_Board.Restart();
}


