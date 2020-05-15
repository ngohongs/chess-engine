/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#include "CCommandQuit.h"


CCommandQuit::CCommandQuit(const CInterface & interface, const char * help)
: CCommand(interface, help) {
}

bool CCommandQuit::Execute() {
    return false;
}

