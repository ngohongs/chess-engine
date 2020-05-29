/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#include "CPlayer.h"


CPlayer::CPlayer(CInterface & interface, CBoard & board, EColor side)
: m_Interface(interface), m_Board(board), m_Side(side) {
}
