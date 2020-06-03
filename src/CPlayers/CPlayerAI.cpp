/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#include "CPlayerAI.h"

#include <iostream>

const int MATE = 29000;

CPlayerAI::CPlayerAI(CInterface & interface, CBoard & board, EColor side)
: CPlayer(interface, board, side) {
    m_Board.PrintState();
    Search(5);
//    char command;
//    while (true) {
//        std::cin >> command;
//        if (command == 'm') {
//            std::list<CMove> moveList = m_Board.GenerateMovesForSide();
//            m_PrincipleVariation.emplace(m_Board.GetStateKey(), moveList.front());
//            m_Board.MakeMove(moveList.front());
//            m_Board.PrintState();
//            std::cout << std::endl;
//            moveList = m_Board.GenerateMovesForSide();
//            m_PrincipleVariation.e1mplace(m_Board.GetStateKey(), moveList.back());
//            m_Board.MakeMove(moveList.back());
//            m_Board.PrintState();
//            std::cout << std::endl;
//            moveList = m_Board.GenerateMovesForSide();
//            m_PrincipleVariation.emplace(m_Board.GetStateKey(), moveList.front());
//            m_Board.MakeMove(moveList.front());
//            m_Board.PrintState();
//            std::cout << std::endl;
//        }
//        else if (command == 'u') {
//            for (int i = 0; i < 3; i++) {
//                m_Board.UndoMove();
//                m_Board.PrintState();
//                std::cout << std::endl;
//            }
//        }
//        else if (command == 'p') {
//            for (const auto & i : GetPrincipleVariation(3))
//                std::cout << i << std::endl;
//        }
//        else
//            break;
//
//    }
}

void CPlayerAI::ResetSearch() {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 120; j++)
            m_SearchHistory[i][j] = 0;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 64; j++)
            m_SearchKillers[i][j] = 0;
    }
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

void CPlayerAI::Search(int depth) {
    CMove bestMove;
    int bestScore = -INFINITE;
    ResetSearch();
    for (int i = 1; i <= depth; i++) {
        bestScore = AlphaBeta(-INFINITE, INFINITE, i, true);
        std::list<CMove> pv = GetPrincipleVariation(depth);
        bestMove = pv.front();
        std::cout << "Depth: " << i << " score: " << bestScore << " move: " << bestMove << " nodes: " << m_VisitedNodes << std::endl;
        for (const auto & j : pv)
            std::cout << j << " ";
        std::cout << std::endl;
        std::cout << "ordering: " << m_FailFirst / m_FailHigh << std::endl << std::endl;
    }
    m_BestMove = bestMove;
    m_BestScore = bestScore;
}

int CPlayerAI::AlphaBeta(int alpha, int beta, int depth, bool nullMove) {
    if (!depth) {
        m_VisitedNodes++;
//        std::cout << "alpha beta score: " << UpdateScore() << std::endl;
        return UpdateScore();

    }

    m_VisitedNodes++;

    if (m_Board.IsDraw()) {
        std::cout << "DRAW" << std::endl;
        return 0;
    }

    std::list<CMove> moveList = m_Board.GenerateMovesForSide();
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
//               if (!i.IsCapture()) {
//                   m_SearchKillers
//               }
               return beta;
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
    return false;
}
