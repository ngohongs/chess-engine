/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#pragma once


#include "CInterface.h"
#include "CGame.h"

class CApplication {
private:

    CInterface m_Interface;
    CGame m_Game;
public:
    explicit CApplication(const CInterface & interface);

    ~CApplication()  = default;

    CApplication(const CApplication &) = delete;

    CApplication & operator=(const CApplication &) = delete;

    int Run();

    void ExecuteCommand(std::string &command);

    void Play();

    void Save() const;

    void Load();

    void Board() const;

    void Move();

    void Help() const;

    void Quit();
};



