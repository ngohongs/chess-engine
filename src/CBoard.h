/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include <vector>
#include <memory>
#include "CPiece.h"
#include "EColor.h"

class CBoard {
private:
    std::vector<std::vector<std::unique_ptr<CPiece>>> m_Board;
public:
    CBoard();

    void Print() const;
};



