/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#pragma once

#include <list>
#include "CInterface.h"
#include "CMove.h"
#include "EColor.h"
#include "CBoard.h"


class CPlayer {
protected:
    EColor m_Side = EColor::WHITE;
    CBoard & m_Board;
    CInterface & m_Interface;
    bool m_Computer = false;
public:
    CPlayer(CInterface & interface, CBoard & board, EColor side, bool computer);

    virtual ~CPlayer() = default;

    virtual bool TakeTurn() = 0;

    bool IsComputer() const {
        return m_Computer;
    }
};



