/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#pragma once

#include <list>
#include "CInterface.h"
#include "EColor.h"
#include "CBoard.h"


/**
 * Abstract class CPlayer representing a player in a game
 */
class CPlayer {
protected:
    CInterface & m_Interface;

    CBoard & m_Board;

    // Side for the player
    EColor m_Side = EColor::WHITE;

    // If the player is AI
    bool m_Computer = false;

    // Difficulty upto 5 for AI, if the players is a person 0
    int m_Difficulty = 0;
public:
    explicit CPlayer(CInterface & interface, CBoard & board, EColor side, bool computer, int difficulty);

    virtual ~CPlayer() = default;

    /**
     * Takes a turn in game
     * @return true if game has not ended, else false
     */
    virtual bool TakeTurn() = 0;

    int GetDifficulty() const {
        return m_Difficulty;
    }
    bool IsComputer() const {
        return m_Computer;
    }
};



