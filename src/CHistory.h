/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 27/05/2020.
 */

#pragma once


#include "CMove.h"
struct CHistory {
    CHistory() {}

    CMove m_Move;
    unsigned int m_Castling;
    int m_EnPassant;
    int m_FiftyTurns;
    uint64_t m_StateKey;
};



