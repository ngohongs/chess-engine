/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#include "CCommandHelp.h"


CCommandHelp::CCommandHelp(const CInterface &interface, const char * help, const std::map<std::string, std::unique_ptr<CCommand>> &commands)
: CCommand(interface, help), m_Commands(commands)
{}

bool CCommandHelp::Execute() {
    for (const auto &i : m_Commands) {
        m_Interface.PromptMessage((i.first + " : " + i.second->GetHelp()));
    }
    return true;
}
