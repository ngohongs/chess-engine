/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "CPiece.h"
#include "EColor.h"
#include "CPieces/CKing.h"
#include "CPieces/CQueen.h"
#include "CPieces/CBishop.h"
#include "CPieces/CKnight.h"
#include "CPieces/CRook.h"
#include "CPieces/CPawn.h"

class CPiece;

class CBoard {
private:
    using TBoard = std::vector<std::vector<std::unique_ptr<CPiece>>>;
    TBoard m_Board;
public:
    CBoard();

    std::ostream & Print(std::ostream & os) const;
};



