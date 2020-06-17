/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 17/06/2020.
 */

#pragma once

#include <fstream>
#include "../CGame.h"
#include "../CCommand.h"


class CCommandLoad : public CCommand {
private:
    CGame & m_Game;
public:
    CCommandLoad(const CInterface & interface, const char * help, CGame & game);

    bool Execute() override;
};



