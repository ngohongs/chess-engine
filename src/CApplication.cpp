/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#include "CApplication.h"


CApplication::CApplication(const CInterface &interface)
: m_Interface(interface), m_Game(m_Interface)
{
    m_Commands.emplace("play", std::make_unique<CCommandPlay>(m_Interface,
            " [p|c][p|c][1|2|3|4|5] : initialize the game - first letter is the white player, second black player (all must be lowercase), if a game against computer is initialized a number between 1 - 5 is needed for the computer difficulty (example: 'play pc4' for game as white against black computer with difficulty 4)", m_Game));
    m_Commands.emplace("restart", std::make_unique<CCommandRestart>(m_Interface, " : restarts the game", m_Game));
    m_Commands.emplace("save", std::make_unique<CCommandSave>(m_Interface, " [filename] : saves game to 'filename'", m_Game));
    m_Commands.emplace("load", std::make_unique<CCommandLoad>(m_Interface, " [filename] : loads 'filename'", m_Game));
    m_Commands.emplace("move", std::make_unique<CCommandMove>(CCommandMove(m_Interface,
            " [a|b|c|d|e|f|g|h][1|2|3|4|5|6|7|8][a|b|c|d|e|f|g|h]][1|2|3|4|5|6|7|8]][q|r|b|n] : make a move - first two letters is the position of a piece to be move, following two letters is the position of the destination. If a pawn is going to promote, a piece is needed for a pawn to promote to (q, r, b, n). (all must be lowercase) (example: move a1b2)", m_Game)));
    m_Commands.emplace("board", std::make_unique<CCommandBoard>(CCommandBoard(m_Interface, " : shows the state of the chess board", m_Game)));
    m_Commands.emplace("help", std::make_unique<CCommandHelp>(CCommandHelp(m_Interface, " : shows commands used by this program", m_Commands)));
    m_Commands.emplace("quit", std::make_unique<CCommandQuit>(CCommandQuit(m_Interface, " : quits this program")));
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

