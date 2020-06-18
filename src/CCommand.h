/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#pragma once

#include <string>
#include "CInterface.h"

/**
 * Abstract class CCommand representing a command
 */
class CCommand {
protected:
    CInterface m_Interface;

    // Help text
    std::string m_Help;
public:
    explicit CCommand(const CInterface &interface, const char * help)
    : m_Interface(interface), m_Help(std::string(help)) {
    }

    virtual ~CCommand() = default;

    const std::string & GetHelp() const {
        return m_Help;
    }

    virtual bool Execute() = 0;
};



