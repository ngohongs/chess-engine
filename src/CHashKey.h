/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 27/05/2020.
 */

#pragma once

#include <random>
#include <memory>
#include "CPiece.h"
#include "EPiece.h"
#include "EColor.h"


/**
 * Class enconding state
 * source: https://www.chessprogramming.org/Zobrist_Hashing
 */
class CHashKey {
private:
    // Hash keys for each piece for each position
    uint64_t m_PiecesKeys[12][120];

    // Hash keys for castling every combination of castling permission
    uint64_t m_CastlingKeys[16];

    // Hash keys for every tile on board for en passant square
    uint64_t m_EnPassantKey[120];

    // Hash keys for the side
    uint64_t m_WhiteTurnKey;

    uint64_t m_StateKey;

    // Initialize hash keys
    void InitiateHashKeys();
public:
    CHashKey();

    /**
     * Generates state key
     * @param board array representing the board
     * @param side playing side
     * @param castling permissions
     * @param enPassant enpassant square
     * @return state key
     */
    uint64_t GenerateStateKey(const std::shared_ptr<CPiece> * board, EColor side, unsigned castling, int enPassant);

    /**
     * Hash piece
     * @param pieceCode piece to hash
     * @param tile position of the piece
     * @return state key
     */
    uint64_t HashPiece(int pieceCode, int tile);

    /**
     * Hash castling permissions
     * @param castling permissions
     * @return state key
     */
    uint64_t HashCastling(unsigned int castling);

    /**
     * Hash side
     * @return state key
     */
    uint64_t HashSide();

    /**
     * Hash en passant square
     * @param tile position of en passant square
     * @return state key
     */
    uint64_t HashEnPassant(int tile);

    uint64_t GetStateKey() const {
        return m_StateKey;
    }

    /**
     * Outputting CHashKey for save file
     * @param os output stream
     * @param self CHashKey to be output
     * @return std::ostream & after output
     */
    friend std::ostream & operator<<(std::ostream & os, const CHashKey & self);

    /**
     * Inputting CHashKeys
     * @param is input stream
     * @param self CHashKey to be input
     * @return std::istream & after input
     */
    friend std::istream & operator>>(std::istream & is, CHashKey & self);
};



