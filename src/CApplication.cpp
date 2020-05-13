/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#include <iostream>
#include <string>
#include "CApplication.h"

CApplication::CApplication(const CInterface &interface)
: m_Interface(interface)
{}

int CApplication::Run() {
    while (true) {
        std::string command = m_Interface.PromptCommand();
        if (command == "play")
            Play();
        else if (command == "save")
            Save();
        else if (command == "load")
            Load();
        else if (command == "board")
            Board();
        else if (command == "move")
            Move();
        else if (command == "help")
            Help();
        else if (command == "quit")
            Quit();
        else
            m_Interface.Clear();
            m_Interface.PromptMessage("Command not found, type 'help' ")

    }
    return 0;
}

void CApplication::ExecuteCommand(std::string &command) {

}
