/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#include "CPlayerHuman.h"
#include "../CBoard.h"


CPlayerHuman::CPlayerHuman(CInterface & interface, CBoard & board, EColor side)
: CPlayer(interface, board, side) {

}

bool CPlayerHuman::TakeTurn() {
    CMove move;
    std::list<CMove> moveList = m_Board.GenerateMovesForSide();
    while (true) {
        move = m_Interface.PromptMove();
        m_Board.PrintState();
        if (!move.IsValid()) {
            return false;
        }
        for (const auto & i : moveList) {
            if (move == i) {
                if (!m_Board.MakeMove(i)) {
                    m_Interface.PromptMessage("Illegal move, your king will be in check\n");
                    break;
                }
                m_Board.PrintState();
                return true;
            }
        }
        m_Interface.PromptMessage("Not valid move for this side, enter valid\n");
    }
}
