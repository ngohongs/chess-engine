/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#include "CInterface.h"


CInterface::CInterface(std::ostream &out, std::istream &in)
: m_Out(out), m_In(in)
{}


std::string CInterface::PromptCommand(const std::function<bool (const std::string &)> &valid) {
    std::cout << "Enter a command, for help enter the command 'help':" << std::endl;
    std::string command;
    while (true) {
        m_In >> command;

        if (m_In.eof())
            return "quit";
        else if (m_In.fail())
            throw std::runtime_error("Error during inputting command");
        else if (!valid(command)) {
            std::cout << "Non-existing command, Enter a valid command, for help enter the command 'help':" << std::endl;
            Clear();
            }
        else
            return command;
    }
}

void CInterface::Clear() {
    m_In.clear();
    m_In.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void CInterface::PromptMessage(const char * message) {
    if (!(m_Out << message))
        throw std::runtime_error("Error during outputting message");
}

void CInterface::PromptMessage(const std::string &message) {
    if (!(m_Out << message))
        throw std::runtime_error("Error during outputting message");
}
