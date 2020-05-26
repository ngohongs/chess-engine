/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#include "CBoard.h"

CBoard::CBoard() {
    for (int i = 0; i < 120; i++)
        m_Board[i] = std::make_shared<COffboard>(COffboard(*this, i));

    InitiateHashKeys();

    ReadFEN(QUEENMOVE);
    assert(CreateFEN() == QUEENMOVE);


    GenerateStateKey();

    GenerateAllMoves(EColor::WHITE);
}

std::ostream & CBoard::Print(std::ostream & os) const {
    os << "    A B C D E F G H" << std::endl;
    os << "  +-----------------+" << std::endl;
    for (int i = 7; i >= 0; i--) {
        os << i + 1 << " | ";
        for (int j = A1; j <= H1; j++) {
            os << *m_Board[j + i * 10] << ' ';
        }
        os << "| " << i + 1 << std::endl;
    }
    os << "  +-----------------+" << std::endl;
    os << "    A B C D E F G H" << std::endl;
    return os;
}

bool CBoard::ReadFEN(const std::string & fen) {
    std::istringstream iss(fen);
    std::string board;
    char whiteTurn;
    std::string castling;
    std::string enPassant;
    int ply;
    int turn;

    iss >> board >> whiteTurn >> castling >> enPassant >> ply >> turn;

    int position = A8;
    int rank = 8;
    int file = 0;

    for (auto i = board.cbegin(); i != board.cend() && rank > 0; i++) {
            if (*i == ' ')
                break;
            switch (*i) {
                case 'P':
                    m_Board[position] = std::make_shared<CPawn>(CPawn(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'N':
                    m_Board[position] = std::make_shared<CKnight>(CKnight(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'B':
                    m_Board[position] = std::make_shared<CBishop>(CBishop(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'R':
                    m_Board[position] = std::make_shared<CRook>(CRook(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'Q':
                    m_Board[position] = std::make_shared<CQueen>(CQueen(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'K':
                    m_Board[position] = std::make_shared<CKing>(CKing(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    m_WhiteKing = position;
                    position++;
                    file++;
                    break;

                case 'p':
                    m_Board[position] = std::make_shared<CPawn>(CPawn(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'n':
                    m_Board[position] = std::make_shared<CKnight>(CKnight(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'b':
                    m_Board[position] = std::make_shared<CBishop>(CBishop(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'r':
                    m_Board[position] = std::make_shared<CRook>(CRook(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'q':
                    m_Board[position] = std::make_shared<CQueen>(CQueen(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    position++;
                    file++;
                    break;
                case 'k':
                    m_Board[position] = std::make_shared<CKing>(CKing(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    m_BlackKing = position;
                    position++;
                    file++;
                    break;

                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                    for (int j = 0; j < (*i - '0'); j++) {
                        m_Board[position] = std::make_shared<CEmpty>(CEmpty(*this, position));
                        position++;
                        file++;
                    }
                    break;

                case '/':
                    if (file != 8)
                        return false;
                    file = 0;
                    position -= 18;
                    rank--;
                    break;

                default:
                    return false;
            }
    }

    if (rank != 1 || file != 8)
        return false;

    if (whiteTurn == 'w')
        m_Side = EColor::WHITE;
    else if (whiteTurn == 'b')
        m_Side = EColor::BLACK;
    else
        return false;

    m_Castling = NO_CASTLE;
    for (char i : castling) {
        if (i == '-')
            break;
        switch (i) {
            case 'K':
                m_Castling |= WHITE_KING_CASTLE;
                break;
            case 'Q':
                m_Castling |= WHITE_QUEEN_CASTLE;
                break;
            case 'k':
                m_Castling |= BLACK_KING_CASTLE;
                break;
            case 'q':
                m_Castling |= BLACK_QUEEN_CASTLE;
                break;
            default:
                return false;
        }
    }

    if (enPassant == "-")
        m_EnPassant = EMPTY;
    else if ((m_EnPassant = TileToIndex(enPassant)) == OFFBOARD)
        return false;

    if (ply >= 0)
        m_Plies = ply;
    else
        return false;
    if (turn >= 1)
        m_Turns = turn;
    else
        return false;

    return true;
}

void CBoard::PrintState() const {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            m_Board[i * 10 + j]->Print(std::cout);
        }
        std::cout << '\n';
    }
    std::cout << "side: " << (m_Side == EColor::WHITE ? 'w' : 'b') << std::endl;
    std::cout << "En Passant: " << IndexToTile(m_EnPassant) << std::endl;
    std::cout << "Castling: " << (m_Castling & 0x8U ? "K" : "") << (m_Castling & 0x4U ? "Q" : "")
                              << (m_Castling & 0x2U ? "k" : "") << (m_Castling & 0x1U ? "q" : "")
                              << (!m_Castling ? "-" : "") << std::endl;
}

std::string CBoard::CreateFEN() const {
    std::string fen = "";
    int code;
    int count = 0;
    for (int i = 7; i >= 0; i--) {
        for (int j = A1; j <= H1; j++) {
            code = m_Board[i * 10 + j]->GetCode();
            if (code != EMPTY)
                fen.push_back(PIECE_CHAR_CODE[code]);
            else {
                for (; j <= H1 && m_Board[i * 10 + j]->GetCode() == EMPTY; j++)
                        count++;
                j--;
                fen.push_back(count + '0');
                count = 0;
            }
        }
        fen.push_back('/');
    }
    fen.pop_back();

    fen.push_back(' ');
    fen.push_back(m_Side == EColor::WHITE ? 'w' : 'b');
    fen.push_back(' ');
    if (m_Castling & WHITE_KING_CASTLE)
        fen.push_back('K');
    if (m_Castling & WHITE_QUEEN_CASTLE)
        fen.push_back('Q');
    if (m_Castling & BLACK_KING_CASTLE)
        fen.push_back('k');
    if (m_Castling & BLACK_QUEEN_CASTLE)
        fen.push_back('q');
    if (!m_Castling)
        fen.push_back('-');

    fen.push_back(' ');
    if (m_EnPassant == EMPTY)
        fen.push_back('-');
    else
        fen += IndexToTile(m_EnPassant);

    fen.push_back(' ');
    fen += std::to_string(m_Plies);

    fen.push_back(' ');
    fen += std::to_string(m_Turns);
    return fen;
}

void CBoard::InitiateHashKeys() {
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

uint64_t CBoard::GenerateStateKey() {
    uint64_t stateKey = 0;
    for (int i = 0; i < 8; i++)
        for (int j = A1; j <= H1; j++)
            if (m_Board[i * 10 + j]->GetCode() != EMPTY)
                stateKey ^= m_PiecesKeys[m_Board[i * 10 + j]->GetCode()][i * 10 + j];

    if (m_Side == EColor::WHITE)
        stateKey ^= m_WhiteTurnKey;

    stateKey ^= m_CastlingKeys[m_Castling];

    if (m_EnPassant != EMPTY)
        stateKey ^= m_EnPassantKey[m_EnPassant];

    m_StateKey = stateKey;
    return stateKey;
}

bool CBoard::TileAttacked(EColor attacker, int tile) const {
    // Pawn attacking
    if (attacker == EColor::WHITE) {
        if (m_Board[tile - 9]->GetCode() == P || m_Board[tile - 11]->GetCode() == P)
            return true;
    }
    else {
        if (m_Board[tile + 9]->GetCode() == p || m_Board[tile + 11]->GetCode() == p)
            return true;
    }

    //Knight attacking
    for (int i : KNIGHT_ATTACKS) {
        if (m_Board[tile + i ]->GetPiece() == EPiece::KNIGHT && m_Board[tile + i ]->GetColor() == attacker)
            return true;
    }

    int tempTile;
    EPiece piece;
    EColor color;
    //Rook attacks with half of queen attacks
    for (int i : ROOK_ATTACKS) {
        tempTile = tile + i;
        while (!IsOffboard(tempTile)) {
            piece = m_Board[tempTile]->GetPiece();
            color = m_Board[tempTile]->GetColor();
            if (piece != EPiece::EMPTY) {
                if ((piece == EPiece::ROOK || piece == EPiece::QUEEN) && color == attacker)
                    return true;
                break;
            }
        tempTile += i;
        }
    }
    //Bishop attacks with half of queen attacks
    for (int i : BISHOP_ATTACKS) {
        tempTile = tile + i;
        while (!IsOffboard(tempTile)) {
            piece = m_Board[tempTile]->GetPiece();
            color = m_Board[tempTile]->GetColor();
            if (piece != EPiece::EMPTY) {
                if ((piece == EPiece::ROOK || piece == EPiece::QUEEN) && color == attacker)
                    return true;
                break;
            }
            tempTile += i;
        }
    }

    //King attacks
    for (int i : KING_ATTACKS) {
        if (m_Board[tile +  i]->GetPiece() == EPiece::KING && m_Board[tile + i]->GetColor() == attacker)
            return true;
    }

    return false;
}

void CBoard::TilesAttackedBy(EColor attacker) const {
    std::cout << "    A B C D E F G H" << std::endl;
    std::cout << "  +-----------------+" << std::endl;
    for (int i = 7; i >= 0; i--) {
        std::cout << i + 1 << " | ";
        for (int j = A1; j <= H1; j++) {
            if (TileAttacked(attacker ,j + i * 10))
                std::cout << "X ";
            else
                std::cout << ". ";
        }
        std::cout << "| " << i + 1 << std::endl;
    }
    std::cout << "  +-----------------+" << std::endl;
    std::cout << "    A B C D E F G H" << std::endl;
}

const std::shared_ptr<CPiece> & CBoard::operator[](int index) const {
    return m_Board[index];
}

std::shared_ptr<CPiece> & CBoard::operator[](int index) {
    return m_Board[index];
}

bool CBoard::IsEmpty(int index) const {
    return m_Board[index]->GetPiece() == EPiece::EMPTY;
}

bool CBoard::IsOffboard(int index) const {
    return m_Board[index]->GetPiece() == EPiece::OFFBOARD;
}

int CBoard::GetEnPassant() const {
    return m_EnPassant;
}

std::list<CMove> CBoard::GenerateAllMoves(EColor side) const {
    std::list<CMove> moveList;
    int count = 0;
    if (side == EColor::WHITE)
        for (const auto & i : m_WhitePieces)
            moveList.splice(moveList.end(), i->MoveList());
    else
        for (const auto & i : m_BlackPieces)
            moveList.splice(moveList.end(), i->MoveList());


    for (const auto & i : moveList) {
        std::cout << "move #" << ++count << "\t";
        i.Print(std::cout);
        std::cout << std::endl;
    }
    std::cout << "Total moves: " << count << std::endl;

    return moveList;
}
