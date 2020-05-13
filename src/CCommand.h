/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#pragma once

#include <string>
#include "CInterface.h"


class CCommand {
protected:
    CInterface m_Interface;
    std::string m_Help;
public:
    explicit CCommand(const CInterface &interface, const char * help)
    : m_Interface(interface), m_Help(std::string(help))
    {}

    const std::string & GetHelp() const
    { return m_Help; }

    virtual bool Execute() = 0;
};



