/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#pragma once

#include "../CPiece.h"


class CKnight : public CPiece {
private:
public:
    explicit CKnight(CBoard * board, const CCoord & coord, EColor color);
};



