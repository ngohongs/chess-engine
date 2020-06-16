/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#include "CPlayerAI.h"

#include <iostream>

const int MATE = 29000;

CPlayerAI::CPlayerAI(CInterface & interface, CBoard & board, EColor side, int difficulty)
: CPlayer(interface, board, side, true), m_Difficulty(difficulty) {
    m_SearchHistory.resize(120);
    for (int i = 0; i < 120; i++)
        m_SearchHistory[i].resize(120);
}

void CPlayerAI::ResetSearch() {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 120; j++)
            m_SearchHistory[i][j] = 0;
    }

    m_SearchKillersFirst = std::map<int, CMove>();
    m_SearchKillersSecond = std::map<int, CMove>();
    m_PrincipleVariation = std::map<uint64_t, CMove>();
    m_Ply = 0;
    m_VisitedNodes = 0;
    m_FailFirst = 0;
    m_FailHigh = 0;
}

std::list<CMove> CPlayerAI::GetPrincipleVariation(int depth) {
    std::list<CMove> res;
    auto move = m_PrincipleVariation.find(m_Board.GetStateKey());
    int count = 0;
//    std::cout << "searching: " << std::hex << m_Board.GetStateKey() << std::dec << std::endl;
//    if (move != m_PrincipleVariation.end())
//        std::cout << "found " << move->second << std::endl;
//    if (m_Board.IsPossibleMove(move->second))
//        std::cout << "possible" << std::endl;
    while (move != m_PrincipleVariation.end() && count < depth) {
        if (m_Board.IsPossibleMove(move->second)) {
            m_Board.MakeMove(move->second);
            res.push_back(move->second);
            count++;
            m_Ply++;
        }
        else {
            break;
        }
        move = m_PrincipleVariation.find(m_Board.GetStateKey());
    }
    for (int i = 0; i < count; i++) {
        m_Board.UndoMove();
        m_Ply--;
    }
    return res;
}

int CPlayerAI::UpdateScore() {
    int score = m_Board.GetWhiteScore() - m_Board.GetBlackScore();
    for (const auto & i : m_Board.GetWhitePieces()) {
        if (i->GetPiece() == EPiece::PAWN)
            score += PAWN_SCORE[i->GetCoord()];
        else if (i->GetPiece() == EPiece::KNIGHT)
            score += KNIGHT_SCORE[i->GetCoord()];
        else if (i->GetPiece() == EPiece::BISHOP)
            score += BISHOP_SCORE[i->GetCoord()];
        else if (i->GetPiece() == EPiece::ROOK)
            score += ROOK_SCORE[i->GetCoord()];
    }

    for (const auto & i : m_Board.GetBlackPieces()) {
        if (i->GetPiece() == EPiece::PAWN)
            score -= PAWN_SCORE[MIRROR[i->GetCoord()]];
        else if (i->GetPiece() == EPiece::KNIGHT)
            score -= KNIGHT_SCORE[MIRROR[i->GetCoord()]];
        else if (i->GetPiece() == EPiece::BISHOP)
            score -= BISHOP_SCORE[MIRROR[i->GetCoord()]];
        else if (i->GetPiece() == EPiece::ROOK)
            score -= ROOK_SCORE[MIRROR[i->GetCoord()]];
    }

    if (m_Board.GetSide() == EColor::BLACK)
        score *= -1;

    return score;
}

CMove CPlayerAI::Search(int depth) {
    CMove bestMove;
    int bestScore = -INFINITE;
    ResetSearch();
    for (int i = 1; i <= depth; i++) {
        bestScore = AlphaBeta(-INFINITE, INFINITE, i, true);
        std::list<CMove> pv = GetPrincipleVariation(depth);
        bestMove = pv.front();
//        std::cout << "Depth: " << i << " score: " << bestScore << " move: " << bestMove << " nodes: " << m_VisitedNodes << std::endl;
//        for (const auto & j : pv)
//            std::cout << j << " ";
//        std::cout << std::endl;
//        std::cout << "ordering: " << m_FailFirst / m_FailHigh << std::endl << std::endl;

    }
    m_BestMove = bestMove;
    m_BestScore = bestScore;
    return bestMove;
}

int CPlayerAI::AlphaBeta(int alpha, int beta, int depth, bool nullMove) {
    if (!depth) {
        m_VisitedNodes++;
//        std::cout << "alpha beta score: " << UpdateScore() << std::endl;
        return Quiescence(alpha, beta, 1);

    }

    m_VisitedNodes++;

    if (m_Board.IsDraw() && m_Ply) {
        return 1;
    }

    std::list<CMove> moveList = m_Board.GenerateMovesForSide();
    const auto & pvMove = m_PrincipleVariation.find(m_Board.GetStateKey());
    for (auto & i : moveList) {
        if (pvMove != m_PrincipleVariation.end()) {
            if (i.ExactMatch(pvMove->second))
                i.SetScore(2000000);
        }
        if (!i.IsCapture()) {
            auto moveFirst = m_SearchKillersFirst.find(m_Ply);
            auto moveSecond = m_SearchKillersSecond.find(m_Ply);
            if (moveFirst != m_SearchKillersFirst.end()) {
                if (moveFirst->second.ExactMatch(i))
                    i.SetScore(900000);
            }
            else if (moveSecond != m_SearchKillersSecond.end()) {
                if (moveSecond->second.ExactMatch(i))
                    i.SetScore(800000);
            }
            else
                i.SetScore(m_SearchHistory[i.GetFrom()][i.GetTo()]);
        }
    }
    moveList.sort();

    int legal = 0;
    int oldAlpha = alpha;
    CMove bestMove;
    int score;



    for (const auto & i : moveList) {
        if (!m_Board.MakeMove(i))
            continue;

        legal++;
        m_Ply++;
        score = -AlphaBeta(-beta, -alpha, depth - 1, true);
        m_Board.UndoMove();
        m_Ply--;
       if (score > alpha) {
           if (score >= beta) {
               if (legal == 1)
                   m_FailFirst++;
               m_FailHigh++;
               if (!i.IsCapture()) {
                   m_SearchKillersSecond[m_Ply] = m_SearchKillersFirst[m_Ply];
                   m_SearchKillersFirst[m_Ply] = i;
               }
               return beta;
           }
           if (!i.IsCapture()) {
               m_SearchHistory[i.GetFrom()][i.GetTo()] += depth;
           }
           alpha = score;
           bestMove = i;
       }
    }


    if (!legal) {
        int kingTile = m_Board.GetSide() == EColor::WHITE ? m_Board.GetWhiteKing() : m_Board.GetBlackKing();
        if (m_Board.TileAttacked(OppositeSide(m_Side), kingTile)) {
            return -MATE + m_Ply;
        }
        else
            return 0;
    }

    if (alpha != oldAlpha) {
//        std::cout << "Storing: " << std::hex << m_Board.GetStateKey() << std::dec << " " << bestMove << std::endl;
        m_PrincipleVariation[m_Board.GetStateKey()] = bestMove;
    }

    return alpha;
}

bool CPlayerAI::TakeTurn() {
    CMove move = Search(m_Difficulty);
    if (!m_Board.MakeMove(move)) {
        std::cout << "ERJAKJRKLAJERKLAJ\n";
        return false;
    }
    m_Interface.GetOstream() << '\n' << m_Side << "'s move: " << move << '\n' << std::endl;
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
    return true;;
}

int CPlayerAI::Quiescence(int alpha, int beta, int qdepth) {
    m_VisitedNodes++;
    if (m_Board.IsDraw())
        return 0;

    if (qdepth >= 64)
        return UpdateScore();

    int score = UpdateScore();

    if (score >= beta)
        return beta;

    if (score > alpha)
        alpha = score;

    std::list<CMove> moveList = m_Board.GenerateCaptureMovesForSide();
    const auto & pvMove = m_PrincipleVariation.find(m_Board.GetStateKey());
    for (auto & i : moveList) {
        if (!i.IsCapture())
            std::cout << "ERRORRR\n";
    }
    moveList.sort();
    int legal = 0;
    int oldAlpha = alpha;
    CMove bestMove;

    for (const auto & i : moveList) {
        if (!m_Board.MakeMove(i))
            continue;

        legal++;
        m_Ply++;
        score = -Quiescence(-beta, -alpha, qdepth + 1);
        m_Board.UndoMove();
        m_Ply--;
        if (score > alpha) {
            if (score >= beta) {
                if (legal == 1)
                    m_FailFirst++;
                m_FailHigh++;
                return beta;
            }
            alpha = score;
            bestMove = i;
        }
    }


    if (alpha != oldAlpha)
        m_PrincipleVariation[m_Board.GetStateKey()] = bestMove;

    return alpha;
}
