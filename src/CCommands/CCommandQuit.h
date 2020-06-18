/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include "../CCommand.h"


class CCommandQuit : public CCommand {
public:
    CCommandQuit(const CInterface & interface, const char * help);

    /**
     * Quits the program
     * @return false
     */
    bool Execute() override;
};



