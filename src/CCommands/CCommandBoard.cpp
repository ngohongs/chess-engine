/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 22/05/2020.
 */

#include "CCommandBoard.h"

CCommandBoard::CCommandBoard(const CInterface & interface, const char * help, CGame & game)
: CCommand(interface, help), m_Game(game) {
}

bool CCommandBoard::Execute() {
    m_Interface.GetOstream() << m_Game;
    return true;
}
