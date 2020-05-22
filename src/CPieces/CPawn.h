/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 22/05/2020.
 */

#pragma once

#include <iostream>
#include "../CPiece.h"


class CPawn : public CPiece {
private:
public:
    explicit CPawn(CBoard & board, const CCoord & coord, EColor color);

    std::ostream & Print(std::ostream & os) const;
};



