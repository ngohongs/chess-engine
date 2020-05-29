/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#pragma once

#include "../CCommand.h"
#include "../CGame.h"
#include "../ETile.h"
class CCommandMove : public CCommand {
private:
    CGame & m_Game;
public:
    CCommandMove(const CInterface & interface, const char * help, CGame & game);

    bool Execute() override;
};



