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


/**
 * Class representing a computer player
 */
class CPlayerAI : public CPlayer {
private:
    // Used for searching a move, number of plies made in search
    int m_Ply = 0;

    // Used for optimizing the search
    // source: https://www.chessprogramming.org/History_Heuristic
    std::vector<std::vector<int>> m_SearchHistory;

    // Used for ordering moves
    // source: https://www.chessprogramming.org/Killer_Heuristic
    std::map<int, CMove> m_SearchKillersFirst;
    std::map<int, CMove> m_SearchKillersSecond;

    // Best moves saved here indexed by state key of the board
    // source: https://www.chessprogramming.org/Principal_Variation
    std::map<uint64_t, CMove> m_PrincipleVariation;

    /**
     * Search for the best move upto the depth
     * @param depth for the search
     * @return best move
     */
    CMove Search(int depth);

    /**
     * Search for the best score
     * saves best moves to m_PrincipleVariations
     * source: source: https://www.chessprogramming.org/Alpha-Beta
     * @param alpha best score for alpha (source: https://www.chessprogramming.org/Alpha-Beta)
     * @param beta best score for beta (source: https://www.chessprogramming.org/Alpha-Beta)
     * @param depth of the search
     * @return best score of the board
     */
    int AlphaBeta(int alpha, int beta, int depth);

    /**
     * Last evaluation for move. Trying the remove horizon effect (https://www.chessprogramming.org/Horizon_Effect)
     * goes through only captures
     * saves best moves to m_PrincipleVariations
     * source: https://www.chessprogramming.org/Quiescence_Search
     * @param alpha best score for alpha (source: https://www.chessprogramming.org/Alpha-Beta)
     * @param beta best score for beta (source: https://www.chessprogramming.org/Alpha-Beta)
     * @param qdepth bound for not searching too far
     * @return best score of the board
     */
    int Quiescence(int alpha, int beta, int qdepth);

    /**
     * Resets the search
     */
    void ResetSearch();

    /**
     * Evaluates board score. Use for deciding what is the best move
     * @return board score
     */
    int UpdateScore();

    /**
     * Get the series of the best moves leading to each other (1. best move -> 2. best move (after making 1. best move) ->
     *  3. best move (after making 2. best move) -> ...)
     * @param depth of principle varition
     * @return std::list of the best moves
     */
    std::list<CMove> GetPrincipleVariation(int depth);
public:
    CPlayerAI(CInterface & interface, CBoard & board, EColor side, int difficulty);

    /**
     * Makes the best turn. Searches upto m_Difficulty
     * @return true if the game is still in play, else false if the game has ended
     */
    bool TakeTurn() override;
};



