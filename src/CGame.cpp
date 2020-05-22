/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 12/05/2020.
 */

#include "CGame.h"


std::ostream & operator<<(std::ostream & os, const CGame & self) {
    return self.m_Board.Print(os);
}
