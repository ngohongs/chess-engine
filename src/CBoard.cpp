/*
 * @author Hong Son Ngo <ngohongs@fit.cvut.cz>
 * @date 14/05/2020.
 */

#include "CBoard.h"


CBoard::CBoard() {
    ReadFEN(START_FEN);
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
    m_HistoryKeys = {};
    m_WhiteScore = 0;
    m_BlackScore = 0;
    m_HistoryIndex = 0;
    std::vector<CHistory> m_History = {};
    m_Repetitions = false;
    m_WhitePieces = {};
    m_BlackPieces = {};
    m_Plies = 0;
    m_Plies = 0;
    m_Turns = 1;
    m_FiftyTurns = 0;


    for (int i = 0; i < 120; i++)
        m_Board[i] = std::make_shared<COffboard>(COffboard(*this, i));

    for (int i = 0; i < 13; i++)
        m_PiecesCount[i] = 0;

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
                    if (++(m_PiecesCount[P]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'N':
                    m_Board[position] = std::make_shared<CKnight>(CKnight(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    if (++(m_PiecesCount[N]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'B':
                    m_Board[position] = std::make_shared<CBishop>(CBishop(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    if (++(m_PiecesCount[B]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'R':
                    m_Board[position] = std::make_shared<CRook>(CRook(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    if (++(m_PiecesCount[R]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'Q':
                    m_Board[position] = std::make_shared<CQueen>(CQueen(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    if (++(m_PiecesCount[Q]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'K':
                    m_Board[position] = std::make_shared<CKing>(CKing(*this, position, EColor::WHITE));
                    m_WhitePieces.push_back(m_Board[position]);
                    m_WhiteKing = position;
                    if (++(m_PiecesCount[K]) > 1)
                        return false;
                    position++;
                    file++;
                    break;

                case 'p':
                    m_Board[position] = std::make_shared<CPawn>(CPawn(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    if (++(m_PiecesCount[p]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'n':
                    m_Board[position] = std::make_shared<CKnight>(CKnight(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    if (++(m_PiecesCount[n]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'b':
                    m_Board[position] = std::make_shared<CBishop>(CBishop(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    if (++(m_PiecesCount[b]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'r':
                    m_Board[position] = std::make_shared<CRook>(CRook(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    if (++(m_PiecesCount[r]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'q':
                    m_Board[position] = std::make_shared<CQueen>(CQueen(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    if (++(m_PiecesCount[q]) > 10)
                        return false;
                    position++;
                    file++;
                    break;
                case 'k':
                    m_Board[position] = std::make_shared<CKing>(CKing(*this, position, EColor::BLACK));
                    m_BlackPieces.push_back(m_Board[position]);
                    m_BlackKing = position;
                    if (++(m_PiecesCount[k]) > 10)
                        return false;
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
        m_FiftyTurns = ply / 2;
    else
        return false;
    if (turn >= 1)
        m_Turns = turn;
    else
        return false;

    // Check for the order of castling permissions
    if (fen != CreateFEN())
        return false;

    m_StateKey = m_HashKeys.GenerateStateKey(m_Board, m_Side, m_Castling, m_EnPassant);
    m_HistoryKeys[m_StateKey] = 1;
    InitialScore();
    return true;
}

void CBoard::PrintState() const {
    Print(std::cout);
    std::cout << "Fifty moves: " << m_FiftyTurns << std::endl;
    std::cout << "side: " << (m_Side != EColor::WHITE ? 'w' : 'b') << std::endl;
    std::cout << "En Passant: " << IndexToTile(m_EnPassant) << std::endl;
    std::cout << "Castling: " << (m_Castling & 0x8U ? "K" : "") << (m_Castling & 0x4U ? "Q" : "")
                              << (m_Castling & 0x2U ? "k" : "") << (m_Castling & 0x1U ? "q" : "")
                              << (!m_Castling ? "-" : "") << std::endl;
    std::cout << "Key: " << std::hex << m_StateKey << std::dec << std::endl;
}

std::string CBoard::CreateFEN() const {
    std::string fen;
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

bool CBoard::TileAttacked(EColor attacker, int tile) const {
    // check all possible attacking patterns
    // if one of the square on the pattern is piece of opposite side with the attacking patern return true

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
                if ((piece == EPiece::BISHOP || piece == EPiece::QUEEN) && color == attacker)
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

const std::shared_ptr<CPiece> & CBoard::operator[](int index) const {
    return m_Board[index];
}

std::shared_ptr<CPiece> & CBoard::operator[](int index) {
    return m_Board[index];
}

bool CBoard::RemovePiece(int index) {
    EColor targetColor = m_Board[index]->GetColor();
    int targetCode = m_Board[index]->GetCode();
    if (--(m_PiecesCount[targetCode]) < 0)
        throw std::logic_error("Cannot remove not existing piece");

    if (IsOffboard(index) || IsEmpty(index)) {
        std::cout << CreateFEN() << std::endl;
        PrintState();
        throw std::logic_error("Cannot remove piece offboard or empty piece");
    }

    if (targetColor == EColor::WHITE) {
        m_WhitePieces.remove(m_Board[index]);
        m_WhiteScore -= PIECE_SCORE[targetCode];
    }
    else {
        m_BlackPieces.remove(m_Board[index]);
        m_BlackScore -= PIECE_SCORE[targetCode];
    }

    m_StateKey = m_HashKeys.HashPiece(m_Board[index]->GetCode(), index);
    m_Board[index] = std::make_shared<CEmpty>(CEmpty(*this, index));
    return true;
}

bool CBoard::AddPiece(int index, EPiece piece, EColor color) {
    if (!(m_Board[index]->GetPiece() == EPiece::EMPTY))
        throw std::runtime_error("Cannot add piece to occupied tile");

    std::shared_ptr<CPiece> target;
    if (piece == EPiece::PAWN)
        target = std::make_shared<CPawn>(CPawn(*this, index, color));
    else if (piece == EPiece::KNIGHT)
        target = std::make_shared<CKnight>(CKnight(*this, index, color));
    else if (piece == EPiece::ROOK)
        target = std::make_shared<CRook>(CRook(*this, index, color));
    else if (piece == EPiece::BISHOP)
        target = std::make_shared<CBishop>(CBishop(*this, index, color));
    else if (piece == EPiece::QUEEN)
        target = std::make_shared<CQueen>(CQueen(*this, index, color));
    else if (piece == EPiece::KING)
        target = std::make_shared<CKing>(CKing(*this, index, color));
    else
        throw std::logic_error("Cannot add empty or offboard piece");

    m_Board[index] = target;

    if (++(m_PiecesCount[target->GetCode()]) > 10)
        throw std::logic_error("Cannot add more pieces");

    // Hash in the piece
    m_StateKey = m_HashKeys.HashPiece(target->GetCode(), index);

    if (color == EColor::WHITE) {
        m_WhitePieces.push_back(target);
        m_WhiteScore += PIECE_SCORE[target->GetCode()];
    }
    else {
        m_BlackPieces.push_back(target);
        m_BlackScore += PIECE_SCORE[target->GetCode()];
    }
    return true;
}

bool CBoard::MovePiece(int from, int to) {

    int pieceToMoveCode = m_Board[from]->GetCode();

    if (IsOffboard(from) || IsOffboard(to) || !IsEmpty(to)) {
        std::cout << CreateFEN();
        PrintState();
        throw std::runtime_error("Cannot move from or to offboard piece");
    }

    // Hash out the piece
    m_StateKey = m_HashKeys.HashPiece(pieceToMoveCode, from);

    m_Board[from]->SetCoord(to);
    m_Board[to] = m_Board[from];
    m_Board[from] = std::make_shared<CEmpty>(CEmpty(*this, from));

    // Hash in the piece
    m_StateKey = m_HashKeys.HashPiece(pieceToMoveCode, to);
    return true;
}

bool CBoard::MakeMove(const CMove & move) {
    CHistory undo;
    undo.m_StateKey = m_StateKey;
    m_History.push_back(undo);

    int from = move.GetFrom();
    int to = move.GetTo();

    // If the king is moved change king position
    if (m_Board[from]->GetPiece() == EPiece::KING) {
        if (move.IsWhiteMove()) {
            m_WhiteKing = to;
        }
        else {
            m_BlackKing = to;
        }
    }

    // If the move is an en passant capture remove the pawn
    if (move.IsEnPassant()) {
        if (move.IsWhiteMove())
            RemovePiece(to - 10);
        else
            RemovePiece(to + 10);
    }

    // If the move is castling move, move rook
    if (move.IsCastling()) {
        switch (to) {
            case C1:
                MovePiece(A1, D1);
                break;
            case C8:
                MovePiece(A8, D8);
                break;
            case G1:
                MovePiece(H1, F1);
                break;
            case G8:
                MovePiece(H8, F8);
                break;
            default:
                throw std::logic_error("Invalid castling move");

        }
    }

    // Hash out en passant square
    if (m_EnPassant != EMPTY)
        m_StateKey = m_HashKeys.HashEnPassant(m_EnPassant);

    // Hash out castling permission
    m_StateKey = m_HashKeys.HashCastling(m_Castling);

    // Store board state
    m_History[m_HistoryIndex].m_Move = move;
    m_History[m_HistoryIndex].m_FiftyTurns = m_FiftyTurns;
    m_History[m_HistoryIndex].m_EnPassant = m_EnPassant;
    m_History[m_HistoryIndex].m_Castling = m_Castling;

    // Change if castling permissions
    if (from == A1 || to == A1)
        m_Castling &= 0xBU;
    if (from == H1 || to == H1)
        m_Castling &= 0x7U;
    if (from == A8 || to == A8)
        m_Castling &= 0xEU;
    if (from == H8 || to == H8)
        m_Castling &= 0xDU;
    if (from == E1 || to == E1)
        m_Castling &= 0x3U;
    if (from == E8 || to == E8)
        m_Castling &= 0xCU;

    m_EnPassant = EMPTY;

    // Hash in castling permissions
    m_StateKey = m_HashKeys.HashCastling(m_Castling);

    // If black increment turns;
    if (m_Side == EColor::BLACK) {
        m_Turns++;
        m_FiftyTurns++;
    }
    // Increment ply after move
    m_Plies++;
    m_HistoryIndex++;

    // If move was a capturing move
    if (move.GetCapture() != EPiece::EMPTY && !move.IsEnPassant()) {
        RemovePiece(to);
        m_FiftyTurns = 0;
    }

    // If moved piece was pawn
    if (m_Board[from]->GetPiece() == EPiece::PAWN) {
        m_FiftyTurns = 0;
        if (move.IsPawnTwoPush()) {
            if (move.IsWhiteMove()) {
                m_EnPassant = from + 10;
//                assert(GetRank(m_EnPassant) == RANK_3);
            }
            else {
                m_EnPassant = from - 10;
//                assert(GetRank(m_EnPassant) == RANK_6);
            }
            m_StateKey = m_HashKeys.HashEnPassant(m_EnPassant);
        }
    }

    MovePiece(from , to);

    // If it is a promotion move
    if (move.GetPromotion() != EPiece::EMPTY) {
        RemovePiece(to);
        AddPiece(to, move.GetPromotion(), move.GetColor());
    }

    // Used for checking if after the move player is in check (illegal move)
    int king;
    if (m_Side == EColor::WHITE)
        king = m_WhiteKing;
    else
        king = m_BlackKing;

    // Hash in side
    m_Side = OppositeSide(m_Side);
    m_StateKey = m_HashKeys.HashSide();

    // Check if the game is a repetition
    if (m_HistoryKeys.find(m_StateKey) != m_HistoryKeys.end()) {
        if (++m_HistoryKeys[m_StateKey] == 3) {
            m_Repetitions = true;
        }
    }
    else {
        m_HistoryKeys.emplace(m_StateKey, 1);
    }

    // If the move is illegal undo it
    if (TileAttacked(m_Side,king)) {
        UndoMove();
        return false;
    }

    // If the game is in checkmate
    if (IsInCheck() && GenerateMovesForSide().empty())
        m_Checkmate = true;

    return true;
}

bool CBoard::UndoMove() {
    // If the game was a threefold repetition
    if (m_HistoryKeys[m_StateKey] == 3) {
        m_Repetitions = false;
    }

    m_HistoryKeys[m_StateKey]--;

    // Decrement turns and plies
    if (m_Side == EColor::WHITE) {
        m_Turns--;
        m_FiftyTurns--;
    }
    m_Plies--;
    m_HistoryIndex--;

    CHistory undo = m_History[m_HistoryIndex];
    // Move to be undone
    CMove undoMove = undo.m_Move;
    int from = undoMove.GetFrom();
    int to = undoMove.GetTo();

    // If en passant square is set hash it out
    if (m_EnPassant != EMPTY)
        m_StateKey = m_HashKeys.HashEnPassant(m_EnPassant);

    // Hash out castling permissions
    m_StateKey = m_HashKeys.HashCastling(m_Castling);

    m_Castling = undo.m_Castling;
    m_FiftyTurns = undo.m_FiftyTurns;
    m_EnPassant = undo.m_EnPassant;

    // If en passant square is set hash it in
    if (m_EnPassant != EMPTY)
        m_StateKey = m_HashKeys.HashEnPassant(m_EnPassant);

    // Hash in castling permissions
    m_StateKey = m_HashKeys.HashCastling(m_Castling);

    m_Side = OppositeSide(m_Side);
    m_StateKey = m_HashKeys.HashSide();

    // If the undo move is an en passant capture add the pawn back
    if (undoMove.IsEnPassant()) {
        if (undoMove.IsWhiteMove())
            AddPiece(to - 10, EPiece::PAWN, EColor::BLACK);
        else
            AddPiece(to + 10, EPiece::PAWN, EColor::WHITE);
    }

    // If the move is an castling move, move back the rook
    if (undoMove.IsCastling()) {
        switch (to) {
            case C1:
                MovePiece(D1, A1);
                break;
            case C8:
                MovePiece(D8, A8);
                break;
            case G1:
                MovePiece(F1, H1);
                break;
            case G8:
                MovePiece(F8, H8);
                break;
            default:
                throw std::logic_error("Invalid castling move");

        }
    }

    MovePiece(to, from);

    // If king was moved change king position
    if (m_Board[from]->GetPiece() == EPiece::KING) {
        if (undoMove.IsWhiteMove()) {
            m_WhiteKing = from;
        }
        else {
            m_BlackKing = from;
        }
    }

    // If the move was a capture, add the captured piece back
    if (undoMove.GetCapture() != EPiece::EMPTY && !undoMove.IsEnPassant()) {
        AddPiece(to, undoMove.GetCapture(), OppositeSide(m_Side));
    }

    // If the move was a promotion, remove promoted piece and add a pawn
    if (undoMove.GetPromotion() != EPiece::EMPTY) {
        RemovePiece(from);
        AddPiece(from, EPiece::PAWN, m_Side);
    }

    return true;
}

std::list<CMove> CBoard::GenerateMovesForSide() {
    // Go through all pieces and generate its moves
    std::list<CMove> moveList;
    if (m_Side == EColor::WHITE)
        for (const auto & i : m_WhitePieces)
            moveList.splice(moveList.end(), i->MoveList());
    else
        for (const auto & i : m_BlackPieces)
            moveList.splice(moveList.end(), i->MoveList());

    return moveList;
}


std::list<CMove> CBoard::GenerateCaptureMovesForSide() {
    // Go through all pieces and generate all its capturing moves
    std::list<CMove> moveList;
    if (m_Side == EColor::WHITE)
        for (const auto & i : m_WhitePieces)
            moveList.splice(moveList.end(), i->CaptureMoveList());
    else
        for (const auto & i : m_BlackPieces)
            moveList.splice(moveList.end(), i->CaptureMoveList());

    return moveList;
}

void CBoard::Perft(int depth, uint64_t & leafNodes) {
        std::ostringstream os;
        std::list<CMove> moveList = std::move(GenerateMovesForSide());
        if (!depth) {
            leafNodes++;
            return;
        }

        for (const auto & i : moveList) {
//        std::cout << "//////////////////////////////////////////" << std::endl;
//        std::cout << "BEFORE: " << i << std::endl;
//        PrintState();
//        std::cout << std::endl;

            if (!MakeMove(i)) {
//            std::cout << "ILLEGAL MOVE" << std::endl;
//            std::cout << "//////////////////////////////////////////" << std::endl;
                continue;
            }

//        std::cout << "depth: " << depth << ",move: " << i << " --------------------------" << std::endl;
//        PrintState();
//        std::cout << "//////////////////////////////////////////" << std::endl << std::endl << std::endl;
            Perft(depth - 1, leafNodes);
            UndoMove();
        }
        return;
}

uint64_t CBoard::PerftTest(int depth) {
    uint64_t leafNodes = 0;
    Perft(depth, leafNodes);
    return leafNodes;
}

void CBoard::PrintPieceNumTable() const {
    std::cout << "'p, n, b, r, q, k, P, N, B, R, Q, K, ' '" << std::endl;
    for (const auto & i : m_PiecesCount)
        std::cout << " " << i << "|";
    std::cout << std::endl;
}

bool CBoard::IsPossibleMove(const CMove & move) {
    std::list<CMove> moveList = GenerateMovesForSide();
    for (const auto & i : moveList) {
        if (!MakeMove(i))
            continue;
        UndoMove();
        if (move.ExactMatch(i))
            return true;
    }
    return false;
}

void CBoard::InitialScore() {
    m_WhiteScore = 0;
    m_BlackScore = 0;
    for (int i = 7; i >= 0; i--) {
        for (int j = A1; j <= H1; j++) {
            if (m_Board[j + i * 10]->GetColor() == EColor::WHITE)
                m_WhiteScore += PIECE_SCORE[m_Board[j + i * 10]->GetCode()];
            if (m_Board[j + i * 10]->GetColor() == EColor::BLACK)
                m_BlackScore += PIECE_SCORE[m_Board[j + i * 10]->GetCode()];
        }
    }
}

bool CBoard::IsDraw() {
    // source: https://en.wikipedia.org/wiki/Draw_(chess)
    int totalPieces = m_WhitePieces.size() + m_BlackPieces.size();
    int whiteBishops = 0;
    int blackBishops = 0;
    int whiteKnights = 0;
    int blackKnights = 0;

    int king = m_Side == EColor::WHITE ? m_WhiteKing : m_BlackKing;

    for (const auto & i : m_WhitePieces) {
        if (i->GetPiece() == EPiece::BISHOP)
            whiteBishops++;
        if (i->GetPiece() == EPiece::KNIGHT)
            whiteKnights++;
    }

    for (const auto & i : m_BlackPieces) {
        if (i->GetPiece() == EPiece::BISHOP)
            blackBishops++;
        if (i->GetPiece() == EPiece::KNIGHT)
            blackKnights++;
    }

    if (m_Repetitions || m_FiftyTurns >= 50)
        return true;
    // Impossible checkmate
    else if (whiteBishops == 1 && blackBishops == 1 && totalPieces == 4)
        return true;
    else if ((whiteKnights == 1 || whiteBishops == 1 || blackKnights == 1 || blackBishops == 1) && totalPieces == 3)
        return true;
    else if (totalPieces == 2)
        return true;
    // Stalemate
    else if (GenerateMovesForSide().empty() && !TileAttacked(OppositeSide(m_Side), king))
        return true;
    else
        return false;
}

bool CBoard::NoPossibleMoves() {
    std::list<CMove> moveList = GenerateMovesForSide();
    for (const auto & i : moveList) {
        if (MakeMove(i)) {
            UndoMove();
            return false;
        }
    }
    return true;
}

std::ostream & operator<<(std::ostream & os, const CBoard & board) {
    os << board.CreateFEN() << std::endl;
    int pawns = 0;
    int knights = 0;
    int bishops = 0;
    int rooks = 0;
    int queens = 0;

    for (const auto & i : board.m_WhitePieces) {
        switch (i->GetPiece()) {
            case EPiece::PAWN:
                pawns++;
                break;
            case EPiece::KNIGHT:
                knights++;
                break;
            case EPiece::BISHOP:
                bishops++;
                break;
            case EPiece::ROOK:
                rooks++;
                break;
            case EPiece::QUEEN:
                queens++;
                break;
            default:
                break;
        }
    }
    os << pawns << ' ' << knights << ' ' << bishops << ' ' << rooks << ' ' << queens << ' ' << board.m_WhitePieces.size() << std::endl;

    pawns = 0;
    knights = 0;
    bishops = 0;
    rooks = 0;
    queens = 0;

    for (const auto & i : board.m_BlackPieces) {
        switch (i->GetPiece()) {
            case EPiece::PAWN:
                pawns++;
                break;
            case EPiece::KNIGHT:
                knights++;
                break;
            case EPiece::BISHOP:
                bishops++;
                break;
            case EPiece::ROOK:
                rooks++;
                break;
            case EPiece::QUEEN:
                queens++;
                break;
            default:
                break;
        }
    }

    os << pawns << ' ' << knights << ' ' << bishops << ' ' << rooks << ' ' << queens  << ' ' << board.m_BlackPieces.size() << std::endl;

    os << board.m_HashKeys;
    os << board.m_StateKey << std::endl;
    os << board.m_HistoryKeys.size() << std::endl;

    uint64_t key = 0;
    uint64_t sum = 0;

    for (const auto & i : board.m_HistoryKeys) {
        key ^= i.first ^ i.second;
        sum += i.first + i.second;
        os << i.first << ":" << i.second << std::endl;
    }

    // key for checking when loadidng
    os << key << ':' << sum << std::endl;
    return os;
}

std::istream & operator>>(std::istream & is, CBoard & board) {
    std::string line;
    getline(is, line);
    if (is.fail())
        return is;


    if (!board.ReadFEN(line) || board.CreateFEN() != line) {
        is.setstate(std::ios::failbit);
        return is;
    }
    getline(is, line);
    if (is.fail())
        return is;
    int pawns = 0;
    int knights = 0;
    int bishops = 0;
    int rooks = 0;
    int queens = 0;
    size_t total = 0;

    if (sscanf(line.c_str(),"%d %d %d %d %d %lu", &pawns, &knights, &bishops, &rooks, &queens, &total) != 6 ||
        pawns != board.m_PiecesCount[P] ||
        knights != board.m_PiecesCount[N] ||
        bishops != board.m_PiecesCount[B] ||
        rooks != board.m_PiecesCount[R] ||
        queens != board.m_PiecesCount[Q] ||
        total != board.m_WhitePieces.size() ) {
        is.setstate(std::ios::failbit);
        return is;
    }
    getline(is, line);
    if (is.fail())
        return is;

    pawns = 0;
    knights = 0;
    bishops = 0;
    rooks = 0;
    queens = 0;
    total = 0;
    if (sscanf(line.c_str(),"%d %d %d %d %d %lu", &pawns, &knights, &bishops, &rooks, &queens, &total) != 6 ||
        pawns != board.m_PiecesCount[p] ||
        knights != board.m_PiecesCount[n] ||
        bishops != board.m_PiecesCount[b] ||
        rooks != board.m_PiecesCount[r] ||
        queens != board.m_PiecesCount[q] ||
        total != board.m_BlackPieces.size() ) {
        is.setstate(std::ios::failbit);
        return is;
    }
    if (!(is >> board.m_HashKeys))
        return is;
    if (!(is >> board.m_StateKey))
        return is;
    if (board.m_StateKey != board.m_HashKeys.GetStateKey()) {
        std::cout << board.m_StateKey << std::endl;
        std::cout << board.m_HashKeys.GetStateKey() << std::endl;

        is.setstate(std::ios::failbit);
        return is;
    }

    uint64_t cnt;
    if (!(is >> cnt))
        return is;

    uint64_t key = 0;
    uint64_t sum = 0;

    uint64_t tmpFirst;
    char c;
    int tmpSecond;

    for (uint64_t i = 0; i < cnt; i++) {
        if (!(is >> tmpFirst >> c >> tmpSecond))
            return is;

        if (c != ':') {
            is.setstate(std::ios::failbit);
            return is;
        }

        key ^= tmpFirst ^ tmpSecond;
        sum += tmpFirst + tmpSecond;
        board.m_HistoryKeys[tmpFirst] = tmpSecond;
    }

    uint64_t checkKey = 0;
    uint64_t checkSum = 0;

    if (!(is >> checkKey >> c >> checkSum))
        return is;

    // check if the keys match
    if (key != checkKey || c != ':' || sum != checkSum) {
        is.setstate(std::ios::failbit);
        return is;
    }

    return is;
}

void CBoard::Restart() {
    if (!ReadFEN(START_FEN))
        throw std::runtime_error("Error during restarting game.");
}
