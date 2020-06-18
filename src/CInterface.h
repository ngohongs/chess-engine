/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include <functional>
#include "CMove.h"


/**
 * Class CInterface for CApplication to interact with the user
 */
class CInterface {
private:
    std::ostream & m_Out;

    std::istream & m_In;
public:
    explicit CInterface(std::ostream &out, std::istream &in);

    /**
     * Outputs message to m_Out
     * @param message
     */
    void PromptMessage(const char * message);

    /**
     * Outputs message to m_Out
     * @param message
     */
    void PromptMessage(const std::string & message);

    std::ostream & GetOstream() const {
        return m_Out;
    }
    std::istream & GetIstream() const {
        return m_In;
    }

    /**
     * Prompts the user for command
     * @param valid function for validation of the command
     * @return command in std::string format, if input reached EOF "quit"
     */
    std::string PromptCommand(const std::function<bool (const std::string &)> &valid);


    /**
     * Clears the m_In for reusing
     */
    void Clear();
};



