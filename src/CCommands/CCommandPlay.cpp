/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 16/06/2020.
 */

#include "CCommandPlay.h"

CCommandPlay::CCommandPlay(const CInterface & interface, const char * help, CGame & game)
: CCommand(interface, help), m_Game(game) {
}

bool CCommandPlay::Execute() {
    std::string bin;
    if (m_Game.IsInitialized()) {
        getline(m_Interface.GetIstream(), bin);
        m_Interface.PromptMessage("Game is already initialized.\n");
        return true;
    }
    std::string input;
    char white;
    char black;
    char difficulty;

    m_Game.Restart();

    m_Interface.GetIstream() >> input;
    input.push_back(' ');

    std::string line;
    getline(m_Interface.GetIstream(), line);
    if (m_Interface.GetIstream().fail())
        throw std::runtime_error("Error during reading input (play).");

    if (line != "") {
        m_Interface.PromptMessage("Command 'play' has no options apart from play mode.\n");
        return true;
    }

    if (m_Interface.GetIstream().eof())
        return false;
    if (m_Interface.GetIstream().fail())
        throw std::runtime_error("Error during execution of command 'play'");

    if (sscanf(input.c_str()," %c%c%c", &white, &black, &difficulty) != 3) {
        m_Interface.GetIstream().ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        m_Interface.PromptMessage("Invalid format\n");
        return true;
    }

    if (white == 'p' && black == 'p' && difficulty == ' ')
        return m_Game.InitializePlayerVsPlayer();
    else if (white == 'c' && black == 'p' && '0' < difficulty && difficulty < '6')
        return m_Game.InitializePlayerVsComputer(EColor::WHITE, difficulty - '0');
    else if (white == 'p' && black == 'c' && '0' < difficulty && difficulty < '6')
        return m_Game.InitializePlayerVsComputer(EColor::BLACK, difficulty - '0');
    else {
        m_Interface.PromptMessage("Invalid format\n");
        return true;
    }
}
