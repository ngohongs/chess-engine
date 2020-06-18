/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#pragma once

#include <map>
#include <string>
#include <memory>
#include "../CCommand.h"


class CCommandHelp : public CCommand {
private:
    std::map<std::string, std::unique_ptr<CCommand>> & m_Commands;
public:
    explicit CCommandHelp(const CInterface & interface, const char * help, std::map<std::string, std::unique_ptr<CCommand>> & commands);

    /**
     * Shows help for program
     * @return true
     */
    bool Execute() override;
};
