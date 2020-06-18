/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#pragma once

#include <list>
#include "../CPlayer.h"
#include "../CInterface.h"
#include "../CMove.h"
#include "../EColor.h"


class CBoard;

/**
 * Class representing a human player
 */
class CPlayerHuman : public CPlayer {
private:
public:
    CPlayerHuman(CInterface & interface,CBoard & board, EColor color);

    /**
     * Ask the player for a move
     * @return true if the game is still in play, else false if the game has ended
     */
    bool TakeTurn() override;
};



