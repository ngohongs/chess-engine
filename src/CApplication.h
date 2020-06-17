/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include "CInterface.h"
#include "CGame.h"
#include "CCommand.h"
#include "CCommands/CCommandHelp.h"
#include "CCommands/CCommandQuit.h"
#include "CCommands/CCommandBoard.h"
#include "CCommands/CCommandMove.h"
#include "CCommands/CCommandPlay.h"
#include "CCommands/CCommandSave.h"
#include "CCommands/CCommandLoad.h"
#include "CCommands/CCommandRestart.h"

class CApplication {
private:
    std::map<std::string, std::unique_ptr<CCommand>> m_Commands;
    CInterface m_Interface;
    CGame m_Game;
public:
    explicit CApplication(const CInterface & interface);

    ~CApplication()  = default;

    CApplication(const CApplication &) = delete;

    CApplication & operator=(const CApplication &) = delete;

    int Run();
};



