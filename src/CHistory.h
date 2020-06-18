/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 27/05/2020.
 */

#pragma once

#include "CMove.h"
#include "EConst.h"


/**
 * Structure for saving state of the CBoard
 */
struct CHistory {
    CHistory() = default;

    // Move made in this state of CBoard
    CMove m_Move;

    // Castling permission
    unsigned int m_Castling = NO_CASTLE;

    // En Passant square
    int m_EnPassant = OFFBOARD;

    // Fifty moves counter
    int m_FiftyTurns = 0;

    // State key of the CBoard
    uint64_t m_StateKey = 0;
};



