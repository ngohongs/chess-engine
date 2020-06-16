/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#include "CPlayer.h"


CPlayer::CPlayer(CInterface & interface, CBoard & board, EColor side, bool computer, int difficulty)
: m_Interface(interface), m_Board(board), m_Side(side), m_Computer(computer), m_Difficulty(difficulty) {
}
