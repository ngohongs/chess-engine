/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#include "CCommandQuit.h"

CCommandQuit::CCommandQuit(const CInterface &interface, const char *help)
: CCommand(interface, help)
{}

bool CCommandQuit::Execute() {
    return false;
}


