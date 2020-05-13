/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#include "CInterface.h"

/* CInterface constructor
 *  @param: std::ostream &out - output stream
 *          std::istream &in  - input stream
 */
CInterface::CInterface(std::ostream &out, std::istream &in)
: m_Out(out), m_In(in)
{}

/* method PromptCommand()
 * - parses input to get command
 * @return command name
 */
std::string CInterface::PromptCommand() const {
    std::cout << "Enter a command, for help enter the command 'help':" << std::endl;
    std::string command;
    m_In >> command;
    if (m_In.fail())
        throw std::runtime_error("Error during inputting command");
    return command;
}

/* method Clear()
 * - clears std::istream state flags and ignores characters in buffer
 * @return true  - if EOF was not encountered
 *         false - if EOF was encountered
 */
bool CInterface::Clear() {
    if (m_In.eof())
        return false;
    m_In.clear();
    m_In.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
}

/* method PromptMessage(const char * message)
 * @param const char * message - C string to be output
 * - outputs to m_Out message
 */
void CInterface::PromptMessage(const char * message) {
    if (!(m_Out << message))
        throw std::runtime_error("Error during outputting message");
}

/* method PromptMessage()
 * @param std::string &message - message to be output
 * - outputs to m_Out message
 */
void CInterface::PromptMessage(const std::string &message) {
    if (!(m_Out << message))
        throw std::runtime_error("Error during outputting message");
}



