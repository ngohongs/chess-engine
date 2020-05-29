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

class CPlayerHuman : public CPlayer {
private:
public:
    CPlayerHuman(CInterface & interface,CBoard & board, EColor color);

    bool TakeTurn() override;
};



