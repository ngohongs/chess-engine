/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 15/05/2020.
 */

#pragma once


struct CCoord {
public:
    int m_X = 0;
    int m_Y = 0;
    CCoord() = default;
    explicit CCoord(int x, int y): m_X(x), m_Y(y) {}
};
