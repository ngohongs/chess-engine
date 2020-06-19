/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <map>
#include <climits>
#include <iomanip>
#include <vector>
#include <memory>
#include <sstream>
#include <climits>
#include <fstream>
#include "CPiece.h"
#include "EColor.h"
#include "CPieces/CKing.h"
#include "CPieces/CQueen.h"
#include "CPieces/CBishop.h"
#include "CPieces/CKnight.h"
#include "CPieces/CRook.h"
#include "CPieces/CPawn.h"
#include "CPieces/CEmpty.h"
#include "CPieces/COffboard.h"
#include "CMove.h"
#include "CHashKey.h"
#include "CHistory.h"
#include "ETile.h"
#include "EConst.h"
#include "FENTest.h"


class CPiece;

/**
 * Class representing a board
 */
class CBoard {
private:
    // used mailbox method for representing a board
    // source: https://www.chessprogramming.org/Mailbox
    std::shared_ptr<CPiece> m_Board[120];

    // Castling permissions
    unsigned int m_Castling = 0xF;

    // Number of plies
    int m_Plies = 0;

    // Number of turns
    int m_Turns = 1;

    // Number of turns without capture or pawn moving
    int m_FiftyTurns = 0;

    // En passant square
    int m_EnPassant = EMPTY;
    bool m_Checkmate = false;
    EColor m_Side = EColor::WHITE;

    // list of piece ordered by color
    std::list<std::shared_ptr<CPiece>> m_WhitePieces;
    std::list<std::shared_ptr<CPiece>> m_BlackPieces;

    // Positions kings
    int m_WhiteKing = E1;
    int m_BlackKing = E8;

    // State keys for counting repetitions
    CHashKey m_HashKeys;
    uint64_t m_StateKey;

    // White score
    int m_WhiteScore = 0;
    int m_BlackScore = 0;


    // Used for indexing in m_History
    int m_HistoryIndex = 0;
    std::vector<CHistory> m_History;

    // If in game occurred threefold repetitions
    bool m_Repetitions = false;

    // Count of each pieces
    int m_PiecesCount[13] = {};

    // Map holding history of the game
    std::map<uint64_t, int> m_HistoryKeys;
public:
    CBoard();

    /**
     * Print the board
     * @param os output stream
     * @return std::ostream & after output
     */
    std::ostream & Print(std::ostream & os) const;

    /**
     * Read Forsyth-Edwards Notation
     * source: https://www.chessprogramming.org/Forsyth-Edwards_Notation
     * @param fen notation
     * @return true, else false if the FEN is not valid
     */
    bool ReadFEN(const std::string & fen);

    /**
     * Creates FEN notation for the current board
     * @return FEN notations
     */
    std::string CreateFEN() const;

    /**
     * Check if the tile is attacked
     * @param attack attacker
     * @param tile defending square
     * @return true if it is attacked, else false
     */
    bool TileAttacked(EColor attack, int tile) const;

    /**
     * Prints board with all infomartion
     * used for debugging
     */
    void PrintState() const;

    /**
     * Get piece on position
     * @param index position of the asked piece
     * @return std::shared_ptr<CPiece>
     */
    const std::shared_ptr<CPiece> & operator[](int index) const;

    /**
     * Get piece on position
     * @param index position of the asked piece
     * @return std::shared_ptr<CPiece>
     */
    std::shared_ptr<CPiece> & operator[](int index);

    /**
     * Removes piece on position
     * @param index position
     * @return true
     */
    bool RemovePiece(int index);

    /**
     * Add piece on position
     * @param index position
     * @param piece to be added
     * @param color of the piece
     * @return true
     */
    bool AddPiece(int index, EPiece piece, EColor color);

    /**
     * Moves piece on position from to position to
     * @param from position
     * @param to position
     * @return true
     */
    bool MovePiece(int from, int to);

    /**
     * Make a move
     * @param move to be made
     * @return true if the move is legal (current player does not get himself in check), else false
     */
    bool MakeMove(const CMove & move);

    /**
     * Undo last move
     * @return true
     */
    bool UndoMove();

    /**
     * Generates all pseudo-legal moves for current side
     * @return std::list<CMove> of all pseudo-legal moves for current side
     */
    std::list<CMove> GenerateMovesForSide();

    /**
     * Generates all pseudo-legal capture moves for current side
     * @return std::list<CMove> of all pseudo-legal capture moves for current side
     */
    std::list<CMove> GenerateCaptureMovesForSide();

    /**
     * Used for testing move generation
     * @param depth for searching all possible legal moves
     * @param leafNodes number of nodes visited nodes
     */
    void Perft(int depth, uint64_t & leafNodes);

    /**
     * Used for testing move generation
     * @param depth for searching all possible legal moves
     */
    uint64_t PerftTest(int depth);

    /**
     * Check if the move is possible for current board
     * @param move to be checked
     * @return true if it is possible, else false
     */
    bool IsPossibleMove(const CMove & move);


    bool IsEmpty(int index) const {
        return m_Board[index]->GetPiece() == EPiece::EMPTY;
    }

    bool IsOffboard(int index) const {
        return m_Board[index]->GetPiece() == EPiece::OFFBOARD;
    }

    /**
     * Prints number of each piece
     * used for debugging
     */
    void PrintPieceNumTable() const;

    /**
     * Initialize score the board
     */
    void InitialScore();

    int GetPlies() const {
        return m_Plies;
    }

    int GetWhiteKing() const {
        return m_WhiteKing;
    }

    int GetBlackKing() const {
        return m_BlackKing;
    }

    /**
     * Check if the game is a draw
     * @return true if yes, else false
     */
    bool IsDraw();

    /**
     * Get list of all white pieces
     * @return std::list of all white pieces
     */
    const std::list<std::shared_ptr<CPiece>> & GetWhitePieces() const {
        return m_WhitePieces;
    }

    /**
     * Get list of all black pieces
     * @return std::list of all black pieces
     */
    const std::list<std::shared_ptr<CPiece>> & GetBlackPieces() const {
        return m_BlackPieces;
    }

    int GetWhiteScore() const {
        return m_WhiteScore;
    };

    int GetBlackScore() const {
        return m_BlackScore;
    }

    unsigned int GetCastling() const {
        return m_Castling;
    }

    int GetEnPassant() const {
        return m_EnPassant;
    }

    uint64_t GetStateKey() const {
        return m_StateKey;
    }

    EColor GetSide() const {
        return m_Side;
    }

    /**
     * Checks if the king is in check
     * @return true if yes, else false
     */
    bool IsInCheck() const {
        return TileAttacked(OppositeSide(m_Side),m_Side == EColor::WHITE ? m_WhiteKing : m_BlackKing);
    }

    /**
     * Checks if the there are not possible moves for current side
     * @return true if yes, else false
     */
    bool NoPossibleMoves();

    /**
     * Outputting CBoard for saving
     * @param os output stream
     * @param board to be output
     * @return std::ostream & after output
     */
    friend std::ostream & operator<<(std::ostream & os, const CBoard & board);

    /**
     * Inputting CBoard for loading
     * @param is input stream
     * @param board to be input
     * @return std::istream & after input
     */
    friend std::istream & operator>>(std::istream & is, CBoard & board);

    /**
     * Restarts the board
     */
    void Restart();
};



