/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 17/06/2020.
 */

#pragma once

#include <fstream>
#include "../CCommand.h"
#include "../CGame.h"


class CCommandSave : public CCommand {
private:
    CGame & m_Game;
public:
    CCommandSave(const CInterface & interface, const char * help, CGame & game);

    /**
     * Saves the game
     * @return true
     */
    bool Execute() override;
};



