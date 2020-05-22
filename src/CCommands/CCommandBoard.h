/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 22/05/2020.
 */

#pragma once

#include "../CCommand.h"
#include "../CGame.h"
#include "../CBoard.h"

class CCommandBoard : public CCommand {
private:
    CGame & m_Game;
public:
    CCommandBoard(const CInterface & interface, const char * help, CGame & game);

    bool Execute() override;
};



