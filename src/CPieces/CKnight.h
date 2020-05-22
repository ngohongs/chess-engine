/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#pragma once

#include <iostream>
#include "../CPiece.h"


class CKnight : public CPiece {
private:
public:
    explicit CKnight(CBoard & board, const CCoord & coord, EColor color);

    std::ostream & Print(std::ostream & os) const;
};



