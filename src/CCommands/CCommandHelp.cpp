/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#include "CCommandHelp.h"


CCommandHelp::CCommandHelp(const CInterface & interface, const char * help, std::map<std::string, std::unique_ptr<CCommand>> &commands)
: CCommand(interface, help), m_Commands(commands) {
}

bool CCommandHelp::Execute() {
    m_Interface.PromptMessage("Chess\nall black pieces are represented with lowercase letters (n stands for knight),\nall white piece are represented with uppercase letters (N stands for knight)\n\n");
    for (const auto &i : m_Commands) {
        m_Interface.PromptMessage((i.first + i.second->GetHelp() + "\n"));
    }
    return true;
}
