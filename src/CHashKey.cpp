/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 27/05/2020.
 */

#include "CHashKey.h"


void CHashKey::InitiateHashKeys() {
    std::random_device seed;
    std::mt19937_64 gen(seed());
    std::uniform_int_distribution<uint64_t> dist;

    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 120; j++)
            m_PiecesKeys[i][j] = dist(gen);
    for (int i = 0; i < 16; i++)
        m_CastlingKeys[i] = dist(gen);
    for (int i = 0; i < 120; i++)
        m_EnPassantKey[i] = dist(gen);
    m_WhiteTurnKey = dist(gen);
}

uint64_t CHashKey::GenerateStateKey(const std::shared_ptr<CPiece> * board, EColor side, unsigned castling, int enPassant) {
    uint64_t stateKey = 0;
    for (int i = 0; i < 8; i++)
        for (int j = A1; j <= H1; j++)
            if (board[i * 10 + j]->GetCode() != EMPTY)
                stateKey ^= m_PiecesKeys[board[i * 10 + j]->GetCode()][i * 10 + j];

    if (side == EColor::WHITE)
        stateKey ^= m_WhiteTurnKey;

    stateKey ^= m_CastlingKeys[castling];

    if (enPassant != EMPTY)
        stateKey ^= m_EnPassantKey[enPassant];

    m_StateKey = stateKey;
    return stateKey;
}

CHashKey::CHashKey() {
    InitiateHashKeys();
}

uint64_t CHashKey::HashPiece(int pieceCode, int tile) {
    return m_StateKey ^= m_PiecesKeys[pieceCode][tile];
}

uint64_t CHashKey::HashCastling(unsigned int castling) {
    return m_StateKey ^= m_CastlingKeys[castling];
}

uint64_t CHashKey::HashSide(EColor color) {
    return m_StateKey ^= m_WhiteTurnKey;
}

uint64_t CHashKey::HashEnPassant(int tile) {
    return m_StateKey ^= m_EnPassantKey[tile];
}

uint64_t CHashKey::GetStateKey() const {
    return m_StateKey;
}


