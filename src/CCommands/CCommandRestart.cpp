/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 17/06/2020.
 */

#include "CCommandRestart.h"


CCommandRestart::CCommandRestart(const CInterface & interface, const char * help, CGame & game)
: CCommand(interface, help), m_Game(game) {
}

bool CCommandRestart::Execute() {
    std::string line;
    // If game is not initialized yet
    if (!m_Game.IsInitialized()) {
        m_Interface.PromptMessage("Game is not initialzed yet, for help enter the command 'help'\n");
        return true;
    }
    m_Interface.PromptMessage("Do you want to restart the game? [y/N]: ");
    getline(m_Interface.GetIstream(), line);
    getline(m_Interface.GetIstream(), line);
    if (m_Interface.GetIstream().fail())
        throw std::runtime_error("Error during reading input (loading).");

    for (auto & i : line)
        i = std::tolower(i);

    if (line == "y" || line == "yes") {
        m_Game.Restart();
        return true;
    }
    else {
        m_Interface.PromptMessage("\n");
        return true;
    }
}