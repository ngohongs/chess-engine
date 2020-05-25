/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#pragma once

#include <iostream>
#include "../CPiece.h"


class CRook : public CPiece {
private:
public:
    explicit CRook(CBoard & board, int coord, EColor color);

    std::ostream & Print(std::ostream & os) const;
};



