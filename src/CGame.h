/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#pragma once

#include <memory>
#include "CInterface.h"
#include "CBoard.h"
#include "CPlayer.h"
#include "CPlayers/CPlayerHuman.h"
#include "CPlayers/CPlayerAI.h"


class CGame {
private:
    CBoard m_Board;

    std::unique_ptr<CPlayer> m_White = nullptr;
    std::unique_ptr<CPlayer> m_Black = nullptr;
    bool m_Initialized = false;
    EColor m_Side = EColor::WHITE;
    CInterface & m_Interface;
    EColor m_Computer;
    bool m_End = false;
public:
    CGame(CInterface & m_Interface);

    bool InitializePlayerVsPlayer();

    bool InitializePlayerVsComputer(EColor computerSide, int difficulty);

    bool MakeTurn();

    const CBoard & GetBoard() const {
        return m_Board;
    }

    bool IsOver() const {
        return m_End;
    }

    CBoard & GetBoard() {
        return m_Board;
    }

    friend std::ostream & operator<< (std::ostream & os, const CGame & self);

    bool IsInitialized() const {
        return m_Initialized;
    }
};



