/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#pragma once

#include "CBoard.h"


class CGame {
private:
    bool m_Initialized = false;
    CBoard m_Board;
public:
    bool Save() const;

    bool Load();
};



