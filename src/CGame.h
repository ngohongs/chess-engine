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

    std::shared_ptr<CPlayer> m_White;
    std::shared_ptr<CPlayer> m_Black;
    bool m_Initialized = false;
    EColor m_Side = EColor::WHITE;
    CInterface & m_Interface;
public:
    CGame(CInterface & m_Interface);

    bool MakeTurn();

    const CBoard & GetBoard() const {
        return m_Board;
    }

    CBoard & GetBoard() {
        return m_Board;
    }

    friend std::ostream & operator<< (std::ostream & os, const CGame & self);
};



