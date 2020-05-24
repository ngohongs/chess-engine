/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 21/05/2020.
 */

#pragma once

#include <iostream>
#include "../CPiece.h"


class CKing : public CPiece {
private:
public:
    explicit CKing(CBoard & board, int coord, EColor color);

    std::ostream & Print(std::ostream & os) const;

    char GetCode() const override;
};



