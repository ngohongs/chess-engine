/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#include "CCommandHelp.h"


CCommandHelp::CCommandHelp(const CInterface & interface, const char * help, std::map<std::string, std::unique_ptr<CCommand>> &commands)
: CCommand(interface, help), m_Commands(commands) {
}

bool CCommandHelp::Execute() {
    std::string line;
    getline(m_Interface.GetIstream(), line);
    if (m_Interface.GetIstream().fail())
        throw std::runtime_error("Error during reading input (help).");

    if (line != "") {
        m_Interface.PromptMessage("Command 'help' has no options.\n");
        return true;
    }

    m_Interface.PromptMessage("\nChess\nall black pieces are represented with lowercase letters (n stands for knight),\nall white piece are represented with uppercase letters (N stands for knight)\n\n");
    for (const auto &i : m_Commands) {
        m_Interface.PromptMessage((i.first + i.second->GetHelp() + "\n"));
    }
    m_Interface.PromptMessage("\n");
    return true;
}
