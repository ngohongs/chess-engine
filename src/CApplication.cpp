/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#include "CApplication.h"


CApplication::CApplication(const CInterface &interface)
: m_Interface(interface), m_Game(m_Interface)
{
    m_Commands.emplace("move", std::make_unique<CCommandMove>(CCommandMove(m_Interface, "make move", m_Game)));
    m_Commands.emplace("board", std::make_unique<CCommandBoard>(CCommandBoard(m_Interface, "shows the state of chess board", m_Game)));
    m_Commands.emplace("help", std::make_unique<CCommandHelp>(CCommandHelp(m_Interface, "shows commands used by this program", m_Commands)));
    m_Commands.emplace("quit", std::make_unique<CCommandQuit>(CCommandQuit(m_Interface, "quits this program")));
}

int CApplication::Run() {
    while (true) {
        std::string command = m_Interface.PromptCommand([this] (const std::string & command) {
            return m_Commands.find(command) != m_Commands.end();
        });
        if (!m_Commands[command]->Execute())
            break;


    }
    return 0;
}

