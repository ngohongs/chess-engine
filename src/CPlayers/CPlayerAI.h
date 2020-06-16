/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#pragma once

#include <map>
#include <list>
#include "../CPlayer.h"
#include "../CMove.h"
#include "../EConst.h"


class CPlayerAI : public CPlayer {
private:
    std::list<CMove> m_PrincipleVariationMoves;
    CMove m_BestMove;
    int m_BestScore;
    int m_VisitedNodes = 0;
    int m_Ply = 0;
    std::vector<std::vector<int>> m_SearchHistory;
    std::map<int, CMove> m_SearchKillersFirst;
    std::map<int, CMove> m_SearchKillersSecond;
    std::map<uint64_t, CMove> m_PrincipleVariation;
    double m_FailFirst = 0;
    double m_FailHigh = 0;
public:
    CPlayerAI(CInterface & interface, CBoard & board, EColor side, int difficulty);

    bool TakeTurn() override;

    std::list<CMove> GetPrincipleVariation(int depth);

    CMove Search(int depth);

    int AlphaBeta(int alpha, int beta, int depth, bool nullMove);

    int Quiescence(int alpha, int beta, int qdepth);

    void ResetSearch();

    int UpdateScore();
};



