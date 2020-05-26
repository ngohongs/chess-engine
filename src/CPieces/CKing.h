/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#pragma once

#include <iostream>
#include "../CPiece.h"


class CKing : public CPiece {
private:
    bool KingNeighbour(int index) const;
public:
    explicit CKing(CBoard & board, int coord, EColor color);

    std::ostream & Print(std::ostream & os) const;

    std::list<CMove> MoveList() const;
};



