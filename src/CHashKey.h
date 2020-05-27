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


class CHashKey {
private:
    uint64_t m_PiecesKeys[12][120];
    uint64_t m_CastlingKeys[16];
    uint64_t m_EnPassantKey[120];
    uint64_t m_WhiteTurnKey;

    uint64_t m_StateKey;
    void InitiateHashKeys();
public:
    CHashKey();

    uint64_t GenerateStateKey(const std::shared_ptr<CPiece> * board, EColor side, unsigned castling, int enPassant);

    uint64_t HashPiece(int pieceCode, int tile);

    uint64_t HashCastling(int castling);

    uint64_t HashSide(EColor color);

    uint64_t HashEnPassant(int tile);

    uint64_t GetStateKey() const;
};



