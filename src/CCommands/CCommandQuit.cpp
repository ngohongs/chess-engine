/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#include "CCommandQuit.h"


CCommandQuit::CCommandQuit(const CInterface & interface, const char * help)
: CCommand(interface, help) {
}

bool CCommandQuit::Execute() {
    std::string line;
    getline(m_Interface.GetIstream(), line);
    if (m_Interface.GetIstream().fail())
        throw std::runtime_error("Error during reading input (quitting).");

    if (line != "") {
        m_Interface.PromptMessage("Command 'quit' has no options.\n");
        return true;
    }

    m_Interface.PromptMessage("Do you want to quit the game without saving? [y/N]: ");
    getline(m_Interface.GetIstream(), line);
    if (m_Interface.GetIstream().fail())
        throw std::runtime_error("Error during reading input (quit).");

    for (auto & i : line)
        i = std::tolower(i);

    if (line == "y" || line == "yes") {
        return false;
    }

    return true;
}

