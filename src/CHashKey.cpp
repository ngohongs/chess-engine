/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 27/05/2020.
 */

#include "CHashKey.h"

CHashKey::CHashKey() {
    InitiateHashKeys();
}

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
    // xor state key with piece key at its position
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

uint64_t CHashKey::HashPiece(int pieceCode, int tile) {
    return m_StateKey ^= m_PiecesKeys[pieceCode][tile];
}

uint64_t CHashKey::HashCastling(unsigned int castling) {
    return m_StateKey ^= m_CastlingKeys[castling];
}

uint64_t CHashKey::HashSide() {
    return m_StateKey ^= m_WhiteTurnKey;
}

uint64_t CHashKey::HashEnPassant(int tile) {
    return m_StateKey ^= m_EnPassantKey[tile];
}

std::ostream & operator<<(std::ostream & os, const CHashKey & self) {
    // for checking when loading CHashKey
    uint64_t key = 0;
    // for checking when loading CHashKey
    uint64_t sum = 0;
    // for checking when loading CHashKey
    uint64_t finalKey = 0;

    // output every key to stream
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 120; j++) {
            os << self.m_PiecesKeys[i][j] << ' ' << key << ' ';
            key ^= self.m_PiecesKeys[i][j];
            finalKey ^= self.m_PiecesKeys[i][j];
            sum += self.m_PiecesKeys[i][j];
        }
    }
    // key for the line, used for checking when loading
    os << key << std::endl;

    key = 0;
    for (int i = 0; i < 16; i++) {
        os << self.m_CastlingKeys[i] << ' ' << key << ' ';
        key ^= self.m_CastlingKeys[i];
        finalKey ^= self.m_CastlingKeys[i];
        sum += self.m_CastlingKeys[i];
    }
    os << key << std::endl;

    key = 0;
    for (int i = 0; i < 120; i++) {
        os << self.m_EnPassantKey[i] << ' ' << key << ' ';
        key ^= self.m_EnPassantKey[i];
        finalKey ^= self.m_EnPassantKey[i];
        sum += self.m_EnPassantKey[i];
    }
    os << key << std::endl;

    os << self.m_WhiteTurnKey << std::endl;
    finalKey ^= self.m_WhiteTurnKey;
    sum += self.m_WhiteTurnKey;

    os << self.m_StateKey << std::endl;
    finalKey ^= self.m_StateKey;
    sum += self.m_StateKey;

    // key for checking inputting this CHashKey
    os << finalKey << ' ' << sum << std::endl;
    return os;
}

std::istream & operator>>(std::istream & is, CHashKey & self) {
    // key for checking if the loading was successful
    uint64_t key = 0;
    // key for checking if the loading was successful
    uint64_t checkKey = 0;
    // key for checking if the loading was successful
    uint64_t sum = 0;
    // key for checking if the loading was successful
    uint64_t finalKey = 0;

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 120; j++) {
            if (!(is >> self.m_PiecesKeys[i][j] >> checkKey) || checkKey != key) {
                is.setstate(std::ios::failbit);
                return is;
            }
            key ^= self.m_PiecesKeys[i][j];
            finalKey ^= self.m_PiecesKeys[i][j];
            sum += self.m_PiecesKeys[i][j];
        }
    }

    if (!(is >> checkKey))
        return is;

    // if the keys do not match, file was overwritten
    if (key != checkKey) {
        is.setstate(std::ios::failbit);
        return is;
    }

    key = 0;
    for (int i = 0; i < 16; i++) {
        if(!(is >> self.m_CastlingKeys[i] >> checkKey) || checkKey != key) {
            is.setstate(std::ios::failbit);
            return is;
        }
        key ^= self.m_CastlingKeys[i];
        finalKey ^= self.m_CastlingKeys[i];
        sum += self.m_CastlingKeys[i];
    }

    if (!(is >> checkKey))
        return is;

    // if the keys do not match, file was overwritten
    if (key != checkKey) {
        is.setstate(std::ios::failbit);
        return is;
    }

    key = 0;
    for (int i = 0; i < 120; i++) {
        if (!(is >> self.m_EnPassantKey[i] >> checkKey) || checkKey != key) {
            is.setstate(std::ios::failbit);
            return is;
        }
        key ^= self.m_EnPassantKey[i];
        finalKey ^= self.m_EnPassantKey[i];
        sum += self.m_EnPassantKey[i];
    }

    if (!(is >> checkKey))
        return is;

    // if the keys do not match, file was overwritten
    if (key != checkKey) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (!(is >> self.m_WhiteTurnKey))
        return is;

    finalKey ^= self.m_WhiteTurnKey;
    sum += self.m_WhiteTurnKey;


    if (!(is >> self.m_StateKey))
        return is;

    finalKey ^= self.m_StateKey;
    sum += self.m_StateKey;

    if (!(is >> checkKey))
        return is;

    // if the keys do not match, file was overwritten
    if (finalKey != checkKey) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (!(is >> checkKey))
        return is;

    // if the keys do not match, file was overwritten
    if (sum != checkKey) {
        is.setstate(std::ios::failbit);
        return is;
    }


    return is;
}


