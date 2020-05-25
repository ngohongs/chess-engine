/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 25/05/2020.
 */

#pragma once

#include <iostream>
#include "EPiece.h"
#include "ETile.h"

class CMove {
private:
    int m_From;
    int m_To;
    EPiece m_Capture = EPiece::EMPTY;
    bool m_PawnStarting = false;
    bool m_EnPassant = false;
    EPiece m_Promotion = EPiece::EMPTY;
    bool m_Castle = false;
public:
    explicit CMove(int from, int to, EPiece capture = EPiece::EMPTY, bool pawnStart = false, bool enPassant = false, EPiece promotion = EPiece::EMPTY, bool castle = false);

    std::ostream & Print(std::ostream & os);
};



