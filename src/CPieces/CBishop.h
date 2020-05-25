/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#pragma once

#include <iostream>
#include "../CPiece.h"


class CBishop : public CPiece {
private:
public:
    explicit CBishop(CBoard & board, int coord, EColor color);

    std::ostream & Print(std::ostream & os) const override;
};
