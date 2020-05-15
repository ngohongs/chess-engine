/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#pragma once

#include "../CPiece.h"


class CPawn : public CPiece {
private:
    bool En_Passant = false;
public:
    explicit CPawn(CBoard * board, const CCoord & coord, EColor color);
};



