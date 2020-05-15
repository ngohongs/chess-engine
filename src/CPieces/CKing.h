/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#pragma once

#include "../CPiece.h"


class CKing : public CPiece {
private:
public:
    explicit CKing(CBoard * board, const CCoord & coord, EColor color);
};



