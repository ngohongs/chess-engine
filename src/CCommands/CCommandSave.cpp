/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 17/06/2020.
 */

#include "CCommandSave.h"

CCommandSave::CCommandSave(const CInterface & interface, const char * help, CGame & game)
: CCommand(interface, help), m_Game(game) {
}

bool CCommandSave::Execute() {
    std::string bin;
    std::string line;
    // If game is not initialized yet
    if (!m_Game.IsInitialized()) {
        getline(m_Interface.GetIstream(), bin);
        m_Interface.PromptMessage("Game is not initialized yet.\n");
        return true;
    }
    std::string path;
    if (!(m_Interface.GetIstream() >> path))
        throw std::runtime_error("Error during inputting path for save file.");

    getline(m_Interface.GetIstream(), line);
    if (m_Interface.GetIstream().fail())
        throw std::runtime_error("Error during reading input (saving).");

    if (line != "") {
        m_Interface.PromptMessage("Command 'save' has no options apart from the path to save file.\n");
        return true;
    }

    std::ofstream file;

    file.open(path, std::ios::out | std::ios::binary);

    if (file.fail()) {
        m_Interface.PromptMessage("Error during opening file for save file\n");
        return true;
    }

    if (!(file << m_Game)) {
        m_Interface.PromptMessage("This path cannot be used for save file.\n");
        return true;
    }


    file.close();
    return true;
}
