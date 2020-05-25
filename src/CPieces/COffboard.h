/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 25/05/2020.
 */

#pragma once


#pragma once

#include <iostream>
#include "../CPiece.h"

class COffboard : public CPiece {
public:
    COffboard(CBoard & board, int coord);

    std::ostream & Print(std::ostream & os) const;
};



