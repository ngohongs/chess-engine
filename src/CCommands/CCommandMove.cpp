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
    std::string line;
    if (m_Game.IsOver()) {
        m_Interface.GetIstream() >> bin;
        m_Interface.PromptMessage("Game is over. Do you want to restart the game [y/N]: ");
        getline(m_Interface.GetIstream(), line);
        getline(m_Interface.GetIstream(), line);
        if (m_Interface.GetIstream().fail())
            throw std::runtime_error("Error during reading input (move).");

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

    if (!m_Game.IsInitialized()) {
        m_Interface.GetIstream() >> bin;
        m_Interface.PromptMessage("Game is not initialized yet.\n");
        return true;
    }
    if (!m_Game.MakeTurn()) {
        m_Interface.PromptMessage("Game is over. Do you want to restart the game [y/N]: ");
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
    return true;
}
