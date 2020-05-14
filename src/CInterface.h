/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 13/05/2020.
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <limits>
#include <functional>


class CInterface {
private:
    std::ostream & m_Out;
    std::istream & m_In;
public:
    explicit CInterface(std::ostream &out, std::istream &in);

    void PromptMessage(const char * message);
    void PromptMessage(const std::string & message);

    std::string PromptCommand(const std::function<bool (const std::string &)> &valid);

    void Clear();
};



