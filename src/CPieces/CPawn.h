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
    explicit CPawn(CBoard & board, int coord, EColor color);

    /**
     * Print itself
     * @param os output stream
     * @return std::ostream & after output
     */
    std::ostream & Print(std::ostream & os) const override;

    /**
     * Generates all pseudo-legal moves (can get itself in check) for the piece
     * @return std::list of all pseudo-legal moves
     */
    std::list<CMove> MoveList() const override;

    /**
    * Generate all pseudo-legal capture moves (can get itself in check) for the piece
    * @return std::list of all pseudo-legal captures
    */
    std::list<CMove> CaptureMoveList() const override;
};



