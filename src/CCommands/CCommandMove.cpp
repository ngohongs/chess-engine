/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#include "CCommandMove.h"

CCommandMove::CCommandMove(const CInterface & interface, const char * help, CGame & game)
: CCommand(interface, help), m_Game(game) {
}

bool CCommandMove::Execute() {
    std::string bin;
    if (!m_Game.IsInitialized()) {
        m_Interface.GetIstream() >> bin;
        m_Interface.PromptMessage("Game is not initialzed yet, for help enter the command 'help'\n");
        return true;
    }
    return m_Game.MakeTurn();
}
