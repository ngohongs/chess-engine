/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 29/05/2020.
 */

#include "CPlayerAI.h"

#include <iostream>


const int MATE = 29000;

CPlayerAI::CPlayerAI(CInterface & interface, CBoard & board, EColor side, int difficulty)
: CPlayer(interface, board, side, true, difficulty) {
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
}

std::list<CMove> CPlayerAI::GetPrincipleVariation(int depth) {
    std::list<CMove> res;
    // Find the best move for current board
    auto move = m_PrincipleVariation.find(m_Board.GetStateKey());

    // Length of series
    int count = 0;

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
        // Find the best move after making the move
        move = m_PrincipleVariation.find(m_Board.GetStateKey());
    }

    // Undo all the moves made by the serach
    for (int i = 0; i < count; i++) {
        m_Board.UndoMove();
        m_Ply--;
    }
    return res;
}

int CPlayerAI::UpdateScore() {
    // Evaluate the board
    // Score each piece and their positions
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

    // If the moving side is black return negation of the score
    if (m_Board.GetSide() == EColor::BLACK)
        score *= -1;

    return score;
}

CMove CPlayerAI::Search(int depth) {
    CMove bestMove;
//    int bestScore = -INFINITE;
    ResetSearch();

    // Used iterative deepening
    // source: https://www.chessprogramming.org/Iterative_Deepening
    for (int i = 1; i <= depth; i++) {
        AlphaBeta(-INFINITE, INFINITE, i);
        std::list<CMove> pv = GetPrincipleVariation(depth);
        bestMove = pv.front();
        // Used for debugging
//        std::cout << "Depth: " << i << " score: " << bestScore << " move: " << bestMove << " nodes: " << m_VisitedNodes << std::endl;
//        for (const auto & j : pv)
//            std::cout << j << " ";
//        std::cout << std::endl;
//        std::cout << "ordering: " << m_FailFirst / m_FailHigh << std::endl << std::endl;

    }
    return bestMove;
}


// source: https://www.chessprogramming.org/Alpha-Beta
int CPlayerAI::AlphaBeta(int alpha, int beta, int depth) {
    // At the end of the search use Quiescence search
    // https://www.chessprogramming.org/Quiescence_Search
    if (!depth)
        return Quiescence(alpha, beta, 1);

    // If in search we get a draw
    if (m_Board.IsDraw() && m_Ply)
        return 0;

    std::list<CMove> moveList = m_Board.GenerateMovesForSide();
    const auto & pvMove = m_PrincipleVariation.find(m_Board.GetStateKey());
    for (auto & i : moveList) {
        // If we get board (board with the same state key) and have a principle variation, score the 2000000
        // this encourages the AI to use these moves
        if (pvMove != m_PrincipleVariation.end()) {
            if (i.ExactMatch(pvMove->second))
                i.SetScore(2000000);
        }
        // If the move is not a capture and made a alpha beta cutoff score it 900000, change the score
        // of the previous move that made a cutoff to 800000
        // this encourages the AI to use the moves that made the search faster
        // source: https://www.chessprogramming.org/Killer_Heuristic
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
            // Other moves score the number in m_SearchHistory (sum of depths where these moves
            // were made in previous search)
            // https://www.chessprogramming.org/History_Heuristic
            else
                i.SetScore(m_SearchHistory[i.GetFrom()][i.GetTo()]);
        }
    }
    // Sort the moves from best to worst (descending order of their scores)
    moveList.sort();

    // Counting legal moves
    int legal = 0;

    // Storing alpha if there was a cutoff
    int oldAlpha = alpha;
    CMove bestMove;
    int score;

    // Go through all legal moves and search deeper
    // source: https://www.chessprogramming.org/Negamax
    for (const auto & i : moveList) {
        if (!m_Board.MakeMove(i))
            continue;

        legal++;
        m_Ply++;
        score = -AlphaBeta(-beta, -alpha, depth - 1);
        m_Board.UndoMove();
        m_Ply--;
        // If the score is better than alpha the score is the new alpha
        if (score > alpha) {
            // If the score is better than beta then a beta cutoff occurred
            if (score >= beta) {
                // If the move is not a capture store the move in killer heuristics
                if (!i.IsCapture()) {
                    m_SearchKillersSecond[m_Ply] = m_SearchKillersFirst[m_Ply];
                    m_SearchKillersFirst[m_Ply] = i;
                }
               return beta;
            }
            // If the moves is not a capture add the depth to search history
            if (!i.IsCapture()) {
               m_SearchHistory[i.GetFrom()][i.GetTo()] += depth;
            }
            // New alpha is the score
            alpha = score;
            // Best move is the current move
            bestMove = i;
       }
    }

    // If zero legal moves were made
    if (!legal) {
        // Check if the board is in checkmate
        int kingTile = m_Board.GetSide() == EColor::WHITE ? m_Board.GetWhiteKing() : m_Board.GetBlackKing();
        if (m_Board.TileAttacked(OppositeSide(m_Side), kingTile)) {
            return -MATE + m_Ply;
        }
        // Else it is a draw
        else
            return 0;
    }

    // If the current alpha is different from older alpha store the best move in principle variation
    if (alpha != oldAlpha) {
        m_PrincipleVariation[m_Board.GetStateKey()] = bestMove;
    }

    return alpha;
}

bool CPlayerAI::TakeTurn() {
    CMove move = Search(m_Difficulty);
    // If the best move is not legal, game has come to an end
    if (!m_Board.MakeMove(move)) {
        return false;
    }
    m_Interface.GetOstream() << '\n' << m_Side << "'s move: " << move << '\n' << std::endl;
    m_Board.Print(m_Interface.GetOstream());

    // Check for check and checkmate
    if (m_Board.IsInCheck()) {
        if (m_Board.NoPossibleMoves()) {
            m_Interface.PromptMessage("Checkmate ");
            if (!(m_Interface.GetOstream() << m_Side << " won\n"))
                throw std::runtime_error("Error during outputting result");
            return false;
        }
        m_Interface.PromptMessage("Check\n");
        return true;
    }
    // Check for draw
    if (m_Board.IsDraw()) {
        m_Interface.PromptMessage("Draw\n");
        return false;
    }
    return true;;
}

// source: https://www.chessprogramming.org/Quiescence_Search
int CPlayerAI::Quiescence(int alpha, int beta, int qdepth) {
    if (m_Board.IsDraw())
        return 0;

    // Bound for searching. Quiescence slows down search
    if (qdepth >= 64)
        return UpdateScore();

    int score = UpdateScore();

    // If the score is better than beta, all next moves will be better than beta
    if (score >= beta)
        return beta;

    // If the score is better than alpha, this is the best state for alpha
    if (score > alpha)
        alpha = score;

    // Same as AlphaBeta
    std::list<CMove> moveList = m_Board.GenerateCaptureMovesForSide();

    moveList.sort();
    int oldAlpha = alpha;
    CMove bestMove;

    for (const auto & i : moveList) {
        if (!m_Board.MakeMove(i))
            continue;

        m_Ply++;
        score = -Quiescence(-beta, -alpha, qdepth + 1);
        m_Board.UndoMove();
        m_Ply--;
        if (score > alpha) {
            if (score >= beta) {
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
