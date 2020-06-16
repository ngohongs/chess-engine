/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#include "CPlayerHuman.h"
#include "../CBoard.h"


CPlayerHuman::CPlayerHuman(CInterface & interface, CBoard & board, EColor side)
: CPlayer(interface, board, side, false, 0) {

}

bool CPlayerHuman::TakeTurn() {
    CMove move;
    std::list<CMove> moveList = m_Board.GenerateMovesForSide();

    m_Interface.GetIstream() >> move;

    if (m_Interface.GetIstream().eof())
        return false;

    if (m_Interface.GetIstream().fail()) {
        m_Interface.PromptMessage("Invalid move, for help enter the command 'help'\n");
        m_Interface.Clear();
        return true;
    }
//        m_Board.PrintState();

    for (const auto & i : moveList) {
        if (move == i) {
            if (!m_Board.MakeMove(i)) {
                m_Interface.PromptMessage("Illegal move, your king will be in check\n");
                break;
            }

            m_Interface.GetOstream() << '\n' << m_Side << "'s move p: " << i << '\n' << std::endl;
            if (m_Board.IsInCheck()) {
                if (m_Board.NoPossibleMoves()) {
                    m_Interface.PromptMessage("Checkmate\n");
                    return false;
                }
                m_Interface.PromptMessage("Check\n");
                return true;
            }
            if (m_Board.IsDraw()) {
                m_Interface.PromptMessage("Draw\n");
                return false;
            }
            return true;
        }
    }
    m_Interface.PromptMessage("Invalid move, for help enter the command 'help'\n");
    m_Interface.Clear();
    return true;

}
