/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 17/06/2020.
 */

#pragma once

#include "../CCommand.h"
#include "../CGame.h"

class CCommandRestart : public CCommand {
private:
    CGame & m_Game;
public:
    CCommandRestart(const CInterface & interface, const char * help, CGame & game);

    bool Execute() override;

};



