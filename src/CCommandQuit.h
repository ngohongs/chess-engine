/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#pragma once

#include "CCommand.h"


class CCommandQuit : public CCommand {
public:
    explicit CCommandQuit(const CInterface &interface, const char * help);

    bool Execute() override;
};



