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


/**
 * Class representing a game, contains players and the board
 */
class CGame {
private:
    CInterface & m_Interface;

    CBoard m_Board;

    std::unique_ptr<CPlayer> m_White = nullptr;

    std::unique_ptr<CPlayer> m_Black = nullptr;

    // If the game is initialized
    bool m_Initialized = false;

    // If the game has ended
    bool m_End = false;
public:
    explicit CGame(CInterface & m_Interface);

    /**
     * Initialize players to player vs player
     * @return true
     */
    bool InitializePlayerVsPlayer();

    /**
     * Initialize players to player vs computer
     * @param computerSide side computer is playing
     * @param difficulty of the computer AI
     * @return false if the game after the computer's move has ended, else true
     */
    bool InitializePlayerVsComputer(EColor computerSide, int difficulty);

    /**
     * Asks the players for a move
     * @return true if the game is still in play, else if the game has ended false
     */
    bool MakeTurn();

    /**
     * Restarts the game
     */
    void Restart();

    const CBoard & GetBoard() const {
        return m_Board;
    }

    bool IsOver() const {
        return m_End;
    }

    CBoard & GetBoard() {
        return m_Board;
    }

    bool IsInitialized() const {
        return m_Initialized;
    }

    /**
     * Prints board
     * @param os output stream
     * @return std::ostream & after output
     */
    std::ostream & Print (std::ostream & os);

    /**
     * Output game for saving game
     * @param os output stream
     * @param self CGame to be saved
     * @return std::ostream & after output
     */
    friend std::ostream & operator<<(std::ostream & os, const CGame & self);

    /**
     * Input game
     * @param is input stream
     * @param self game to be loaded
     * @return std::istream & after input
     */
    friend std::istream & operator>>(std::istream & is, CGame & self);
};



