/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#pragma once

#include <map>
#include <list>
#include "../CPlayer.h"
#include "../CMove.h"


class CPlayerAI : public CPlayer {
private:
    std::list<CMove> m_PrincipleVariationMoves;
    CMove m_BestMove;
    int m_BestScore;
    int m_VisitedNodes = 0;
    int m_Ply = 0;
    int m_SearchHistory[13][120];
    int m_SearchKillers[2][64];
    std::map<uint64_t, CMove> m_PrincipleVariation;
    double m_FailFirst = 0;
    double m_FailHigh = 0;
public:
    CPlayerAI(CInterface & interface, CBoard & board, EColor side);

    bool TakeTurn() override;

    std::list<CMove> GetPrincipleVariation(int depth);

    void Search(int depth);

    int AlphaBeta(int alpha, int beta, int depth, bool nullMove);

    void ResetSearch();

    int UpdateScore();
};



