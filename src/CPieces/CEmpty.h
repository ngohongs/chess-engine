/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 23/05/2020.
 */

#pragma once

#include <iostream>
#include "../CPiece.h"

class CEmpty : public CPiece {
public:
    CEmpty(CBoard & board, int coord);

    std::ostream & Print(std::ostream & os) const;

    std::list<CMove> MoveList() const;
    std::list<CMove> CaptureMoveList() const override;
};



