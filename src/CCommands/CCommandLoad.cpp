/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 17/06/2020.
 */

#include "CCommandLoad.h"

CCommandLoad::CCommandLoad(const CInterface & interface, const char * help, CGame & game)
: CCommand(interface, help), m_Game(game) {
}

bool CCommandLoad::Execute() {
    std::string path;
    std::string line;
    if (!(m_Interface.GetIstream() >> path))
        throw std::runtime_error("Error during inputting path for save file.");

    if (m_Game.IsInitialized()) {
        m_Interface.PromptMessage("Game is already initialized. Do you want to use overwrite current game [y/N]: ");
        getline(m_Interface.GetIstream(), line);
        getline(m_Interface.GetIstream(), line);
        if (m_Interface.GetIstream().fail())
            throw std::runtime_error("Error during reading input (loading).");

        for (auto & i : line)
            i = std::tolower(i);

        if (line != "y" && line != "yes") {
            m_Interface.PromptMessage("\n");
            return true;
        }
    }

    std::ifstream file;

    file.open(path, std::ios::in | std::ios::binary);

    if (file.fail()) {
        m_Interface.PromptMessage("Error during opening save file\n");
        return true;
    }

    if (!(file >> m_Game)) {
        m_Interface.PromptMessage("Save file is corrupted.\n");
        return true;
    }

    file.close();
    return true;
}
