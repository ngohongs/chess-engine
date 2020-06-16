/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 16/06/2020.
 */

#pragma once

#include "../CCommand.h"
#include "../CGame.h"

class CCommandPlay : public CCommand {
private:
    CGame & m_Game;
public:
    CCommandPlay(const CInterface & interface, const char * help, CGame & game);

    bool Execute() override;
};



