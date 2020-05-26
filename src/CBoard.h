/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include <list>
#include <vector>
#include <memory>
#include <sstream>
#include <random>
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
#include "ETile.h"
#include "EConst.h"
#include "FENTest.h"


class CPiece;

class CBoard {
private:
    std::shared_ptr<CPiece> m_Board[120];
    unsigned int m_Castling = 0xF;
    int m_Plies = 0;
    int m_Turns = 1;
    int m_EnPassant = EMPTY;
    EColor m_Side = EColor::WHITE;

    std::list<std::shared_ptr<CPiece>> m_WhitePieces;
    std::list<std::shared_ptr<CPiece>> m_BlackPieces;

    int m_WhiteKing = E1;
    int m_BlackKing = E8;

    uint64_t m_PiecesKeys[12][120];
    uint64_t m_CastlingKeys[16];
    uint64_t m_EnPassantKey[120];
    uint64_t m_WhiteTurnKey;

    uint64_t m_StateKey;
    void InitiateHashKeys();
    uint64_t GenerateStateKey();
public:
    CBoard();

    std::ostream & Print(std::ostream & os) const;

    bool ReadFEN(const std::string & fen);

    std::string CreateFEN() const;

    bool TileAttacked(EColor attack, int tile) const;

    void PrintState() const;

    void TilesAttackedBy(EColor attacker) const;

    const std::shared_ptr<CPiece> & operator[](int index) const;

    std::shared_ptr<CPiece> & operator[](int index);

    std::list<CMove> GenerateAllMoves(EColor side) const;

    int GetEnPassant() const;
    unsigned int GetCastling() const;
    bool IsEmpty(int index) const;
    bool IsOffboard(int index) const;
};



