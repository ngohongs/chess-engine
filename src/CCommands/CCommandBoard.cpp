/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 22/05/2020.
 */

#include "CCommandBoard.h"

CCommandBoard::CCommandBoard(const CInterface & interface, const char * help, CGame & game)
: CCommand(interface, help), m_Game(game) {
}

bool CCommandBoard::Execute() {
    std::string line;
    getline(m_Interface.GetIstream(), line);
    if (m_Interface.GetIstream().fail())
        throw std::runtime_error("Error during reading input (board).");

    if (line != "") {
        m_Interface.PromptMessage("Command 'board' has no options.\n");
        return true;
    }

    if (!m_Game.IsInitialized()) {
        m_Interface.PromptMessage("Game is not initialized yet.\n");
        return true;
    }
    m_Game.Print(m_Interface.GetOstream());
    return true;
}
