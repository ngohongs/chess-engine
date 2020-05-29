/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#include "CCommandMove.h"

CCommandMove::CCommandMove(const CInterface & interface, const char * help, CGame & game)
: CCommand(interface, help), m_Game(game) {
}

bool CCommandMove::Execute() {
    return m_Game.MakeTurn();
}
