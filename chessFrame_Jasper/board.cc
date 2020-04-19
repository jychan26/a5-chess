#include "board.h"
#include "cell.h"
#include "subject.h"
#include "errormessage.h"
#include <cctype>
using namespace std;

Board::~Board() {
    delete td;
}

void Board::init() {
    whoseTurn = Colour::White;
    // create the 2D vector: grid
    for (int r = 0; r < size; ++r) {
        vector<Cell> temp;
        for (int c = 0; c < size; ++c) {
            char col = 'a' + c;
            Position pos{r + 1, col};
            if ((r + c) % 2 == 0) {
                temp.emplace_back(Cell(pos, Colour::Black));
            } else {
                temp.emplace_back(Cell(pos, Colour::White));
            }
        }
        grid.emplace_back(temp);
    }
    td = new TextDisplay();
    // attach observers
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            grid[r][c].attach(td);
        }
    }
    // initial configuration
    this->setPiece('R', {1, 'a'});
    this->setPiece('N', {1, 'b'});
    this->setPiece('B', {1, 'c'});
    this->setPiece('Q', {1, 'd'});
    this->setPiece('K', {1, 'e'});
    this->setPiece('B', {1, 'f'});
    this->setPiece('N', {1, 'g'});
    this->setPiece('R', {1, 'h'});
    for (int c = 0; c < size; ++c) {
        char column = 'a' + c;
        this->setPiece('P', {2, column});
    }
    this->setPiece('r', {8, 'a'});
    this->setPiece('n', {8, 'b'});
    this->setPiece('b', {8, 'c'});
    this->setPiece('q', {8, 'd'});
    this->setPiece('k', {8, 'e'});
    this->setPiece('b', {8, 'f'});
    this->setPiece('n', {8, 'g'});
    this->setPiece('r', {8, 'h'});
    for (int c = 0; c < size; ++c) {
        char column = 'a' + c;
        this->setPiece('p', {7, column});
    }
}

bool Board::isValidPos(Position pos) {
    if (pos.row < 1 || pos.row > 8 || pos.col < 'a' || pos.col > 'h') return false;
    return true;
}

bool Board::isValidName(char name) {
    vector<char> nameList {'R','N','B','Q','K','P','r','n','b','q','k','p'};
    for (char &c : nameList) {
        if (name == c) return true;
    }
    return false;
}

void Board::addToMap(char name, Position pos) {
    string pos_str = pos.col + to_string(pos.row);
    Info info = grid[pos.row - 1][pos.col - 'a'].getInfo();
    if (piecesOnBoard.find(pos_str) == piecesOnBoard.end()){
        piecesOnBoard.insert(pair<string, Info>(pos_str, info));
    } else {
        piecesOnBoard[pos_str] = info;
    }
    if (name == 'K' || name == 'k') {
        if (kings.find(pos_str) == kings.end()){
            kings.insert(pair<string, Info>(pos_str, info));
        } else {
            kings[pos_str] = info;
        }
    }
}

void Board::eraseFromMap(Position pos) {
    string pos_str = pos.col + to_string(pos.row);
    if (piecesOnBoard.count(pos_str)) piecesOnBoard.erase(pos_str);
    if (kings.count(pos_str)) kings.erase(pos_str);
}

void Board::setPiece(char name, Position pos) {
    // raise invalid pos and invalid piece name
    if (!isValidPos(pos)) throw ErrorMessage{"Position is not valid."};
    if (!isValidName(name)) throw ErrorMessage{"Name of piece is not valid."};
    grid[pos.row - 1][pos.col - 'a'].setPiece(name);
    this->addToMap(name, pos);
}

bool Board::removePiece(Position pos) {
    // raise invalid pos
    if (!isValidPos(pos)) throw ErrorMessage{"Position is not valid."};
    // return false and do nothing if there is no piece in that cell
    if (grid[pos.row - 1][pos.col - 'a'].getPiece() == nullptr) return false;
    grid[pos.row - 1][pos.col - 'a'].removePiece();
    this->eraseFromMap(pos);
    return true;
}

void Board::move(Move m) {
    // raise invalid position
    if (!isValidPos(m.from) || !isValidPos(m.to)) throw ErrorMessage{"Position is not valid."};
    
    // there is no piece in the starting cell to move
    if (grid[m.from.row - 1][m.from.col - 'a'].getPiece() == nullptr) {
        throw ErrorMessage{"There is no piece in starting cell."};
    }
    
    // cannot move your opponent's pieces
    Colour pieceColour = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPieceColour();
    if (whoseTurn != pieceColour) {
        string s;
        if (whoseTurn == Colour::White) s = "White's turn. Cannot move black pieces.";
        else if (whoseTurn == Colour::Black) s = "Black's turn. Cannot move white pieces.";
        throw ErrorMessage{s};
    }
    
    // there is a piece in the destination cell
    if (grid[m.to.row - 1][m.to.col - 'a'].getPiece() != nullptr) {
        // cannot capture your own's piece
        pieceColour = grid[m.to.row - 1][m.to.col - 'a'].getPiece()->getPieceColour();
        if (whoseTurn == pieceColour) {
            string s;
            if (whoseTurn == Colour::White) s = "White's turn. Cannot capture white pieces.";
            else if (whoseTurn == Colour::Black) s = "Black's turn. Cannot capture black pieces.";
            throw ErrorMessage{s};
        }
    }
    
    // move does not obey the rule of piece's movement
    if (!isObeyRule(m)) throw ErrorMessage{"Move does not obey the rule of piece's movement."};
    
    // move is blocked by pieces in between
    if (this->isBlocked(this->getInBetweenPositions(m))) {
        throw ErrorMessage{"Cannot move past a piece that blocks the path."};
    }
    
    //
    //
    // cannot make a move that puts your king in check
    //
    //
    
    // if move a pawn one square diagonally but there is no piece in destination cell
    // en passant or throw error message
    bool enPassant = false;
    char name = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPiece();
    if ((name == 'p' || name == 'P') && this->isOneSquareDiagonal(m) &&
        grid[m.to.row - 1][m.to.col - 'a'].getPiece() == nullptr) {
        // if the cell where the would-be attacked pawn should have sit has no piece,
        // then throw error message
        if (grid[m.from.row - 1][m.to.col - 'a'].getPiece() == nullptr) {
            throw ErrorMessage{"Pawn cannot move diagonally without capturing."};
        }
        
        // if the cell where the would-be attacked pawn should have sit has a piece that is not a pawn,
        // then throw error message
        char besidePieceName = grid[m.from.row-1][m.to.col-'a'].getPiece()->getPiece();
        if (besidePieceName != 'p' && besidePieceName != 'P') {
            throw ErrorMessage{"Pawn cannot move diagonally without capturing."};
        }
        
        // en passant must be used to capture the opposing pawn, cannot capture my own pawn
        if (!isOpponentPawn(besidePieceName)) {
            throw ErrorMessage{"En Passant cannot capture your own pawn."};
        }
        
        // if isEnPassantValid field of the captured pawn is false, i.e. the opposing pawn does not
        // make a two-square move or the attack does not immediately follow, then throw error message
        if (!grid[m.from.row - 1][m.to.col - 'a'].getPiece()->getIsEnPassantValid()) {
            throw ErrorMessage{"This move does not obey the rule of En Passant."};
        }
        
        // The conditions of using en passant are satisfied, set enPassant to true
        enPassant = true;
    }
    
    // set the field isEnPassantValid of all pawns on the board to false
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (grid[r][c].getPiece() != nullptr &&
                (grid[r][c].getPiece()->getPiece() == 'p' || grid[r][c].getPiece()->getPiece() == 'P')) {
                grid[r][c].setIsEnPassantValid(false);
            }
        }
    }
    
    // if move a pawn to the other end of the board, then have to promote
    // Otherwise, throw error message
    name = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPiece();
    Position destination = grid[m.to.row - 1][m.to.col - 'a'].getInfo().pos;
    if ((name == 'P' && destination.row == 8 && whoseTurn == Colour::White) ||
        (name == 'p' && destination.row == 1 && whoseTurn == Colour::Black)) {
        if (m.promotion == false) {
            throw ErrorMessage{"Have to specify a piece type to replace the pawn."};
        }
    }
    
    if (!enPassant) {
        bool twoSquaresMove = isPawnMoveTwoSquares(m);
        // move the piece, modify piecesOnBoard, kings and history
        Piece *pieceToBeMoved = grid[m.from.row - 1][m.from.col - 'a'].moveFrom();
        this->eraseFromMap(m.from);
        // if there is a piece to capture, we need to earse the captured piece from piecesOnBoard, kings
        if (grid[m.to.row - 1][m.to.col - 'a'].getPiece() != nullptr) {
            this->eraseFromMap(m.to);
        }
        grid[m.to.row - 1][m.to.col - 'a'].moveTo(pieceToBeMoved); // Cell::moveTo will notify observers
        // if a pawn makes a two-square move, then set its field isEnPassantValid to true
        if (twoSquaresMove) {
            grid[m.to.row - 1][m.to.col - 'a'].setIsEnPassantValid(true);
        }
        this->addToMap(pieceToBeMoved->getPiece(), m.to);
        history.emplace_back(m);
    } else { // en passant implementation
        // move the attacking pawn one square diagonally
        Piece *pawnToBeMoved = grid[m.from.row - 1][m.from.col - 'a'].moveFrom();
        this->eraseFromMap(m.from);
        grid[m.to.row - 1][m.to.col - 'a'].moveTo(pawnToBeMoved);
        this->addToMap(pawnToBeMoved->getPiece(), m.to);
        history.emplace_back(m);
        // remove the attacked pawn from the board, modify piecesOnBoard, kings
        grid[m.from.row - 1][m.to.col - 'a'].removePiece();
        this->eraseFromMap(Position{m.from.row, m.to.col});
    }
    
    // reset whoseTurn after moving the piece
    if (whoseTurn == Colour::Black) this->setWhoseTurn(Colour::White);
    else if (whoseTurn == Colour::White) this->setWhoseTurn(Colour::Black);
}

bool Board::isObeyRule(Move m) {
    Position from = m.from;
    return grid[from.row - 1][from.col - 'a'].isObeyRule(m);
}

vector<Position> Board::getInBetweenPositions(Move m) {
    Position from = m.from;
    return grid[from.row - 1][from.col - 'a'].getInBetweenPositions(m);
}



bool Board::isBlocked(vector<Position> inBetweens) {
    for (auto pos : inBetweens) {
        Piece *p = grid[pos.row - 1][pos.col - 'a'].getPiece();
        if (p != nullptr) {
            return true;
        }
    }
    return false;
}

void Board::promote(char name, Move m) {
    if (grid[m.from.row - 1][m.from.col - 'a'].getPiece() != nullptr) { // ensure Piece::getPiece() can be called
        // cannot promote a piece that is not a pawn
        char pieceToPromote = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPiece();
        if (pieceToPromote != 'P' && pieceToPromote != 'p') {
            throw ErrorMessage{"Cannot promote a piece that is not a pawn."};
        }
    }
    
    // invalid piece type to promote
    bool validPiece = false;
    vector<char> nameList {'R','N','B','Q','r','n','b','q'};
    for (char &c : nameList) {
        if (name == c) validPiece = true;
    }
    if (!validPiece) throw ErrorMessage{"Pawn cannot be promoted to the piece type specified."};
    
    // cannot promote pawn until it reaches the other end of the board
    Position destination = grid[m.to.row - 1][m.to.col - 'a'].getInfo().pos;
    Colour pieceColour = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPieceColour();
    if ((destination.row != 8 && whoseTurn == Colour::White && whoseTurn == pieceColour) ||
        (destination.row != 1 && whoseTurn == Colour::Black && whoseTurn == pieceColour)) {
        throw ErrorMessage{"Pawn cannot be promoted until it reaches the other end of the board."};
    }
    
    // cannot promote a pawn to a piece with different colour
    if ((islower(name) && whoseTurn == Colour::White && whoseTurn == pieceColour) ||
        (isupper(name) && whoseTurn == Colour::Black && whoseTurn == pieceColour)) {
        throw ErrorMessage{"Cannot promote a pawn to a piece with different colour."};
    }
    
    // promotion conditions satisfied, but move conditions may not, call Board::move and Cell::promote
    // Board::move will modify piecesOnBoard, kings, history and reset whoseTurn
    this->move(m);
    this->eraseFromMap(m.to);
    grid[m.to.row - 1][m.to.col - 'a'].promote(name); // Cell::promote will notify observers
    this->addToMap(name, m.to);
}


bool Board::isCastlingValid(Move m) {
    // 2 possible starting and ending coordinates for white castling
    if (whoseTurn == Colour::White) {
        if (!((m.from == Position{"e1"} && m.to == Position{"g1"}) ||
              (m.from == Position{"e1"} && m.to == Position{"c1"}))) {
            return false;
        }
    }
    // 2 possible starting and ending coordinates for black castling
    if (whoseTurn == Colour::Black) {
        if (!((m.from == Position{"e8"} && m.to == Position{"g8"}) ||
              (m.from == Position{"e8"} && m.to == Position{"c8"}))) {
            return false;
        }
    }
    
    if (grid[m.from.row - 1][m.from.col - 'a'].getPiece() == nullptr) return false;
    
    // there is a piece in starting cell, but is not a king
    char pieceCastling = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPiece();
    if (pieceCastling != 'K' && pieceCastling != 'k') return false;
    
    // the king must not have previously moved
    bool firstMove = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getFirstMove();
    if (!firstMove) return false;
    
    char name;
    bool rookFirstMove;
    // there must be no pieces between king and rook, rook must not have previously moved,
    // and king is not in check on starting, final, in between position
    if (m.from == Position{"e1"} && m.to == Position{"g1"}) {
        name = grid[0]['h'].getPiece()->getPiece();
        if (name != 'R' && name != 'r') return false;
        // rook at h1 must not have previously moved
        rookFirstMove = grid[0]['h'].getPiece()->getFirstMove();
        if (!rookFirstMove) return false;
        // check if there is any piece between e1 and h1
        vector<Position> inBetweens {Position{"f1"}, Position{"g1"}};
        if (this->isBlocked(inBetweens)) return false;
        // king is not in check at e1, f1, g1
        if (this->threatenedBy(Position{"e1"}, whoseTurn).size() != 0 ||
            this->threatenedBy(Position{"f1"}, whoseTurn).size() != 0 ||
            this->threatenedBy(Position{"g1"}, whoseTurn).size() != 0) {
            return false;
        }
    } else if (m.from == Position{"e1"} && m.to == Position{"c1"}) {
        name = grid[0]['a'].getPiece()->getPiece();
        if (name != 'R' && name != 'r') return false;
        // rook at a1 must not have previously moved
        rookFirstMove = grid[0]['a'].getPiece()->getFirstMove();
        if (!rookFirstMove) return false;
        // check if there is no piece between e1 and a1
        vector<Position> inBetweens {Position{"b1"}, Position{"c1"}, Position{"d1"}};
        if (this->isBlocked(inBetweens)) return false;
        // king is not in check at c1, d1, e1
        if (this->threatenedBy(Position{"c1"}, whoseTurn).size() != 0 ||
            this->threatenedBy(Position{"d1"}, whoseTurn).size() != 0 ||
            this->threatenedBy(Position{"e1"}, whoseTurn).size() != 0) {
            return false;
        }
    } else if (m.from == Position{"e8"} && m.to == Position{"g8"}) {
        name = grid[7]['h'].getPiece()->getPiece();
        if (name != 'R' && name != 'r') return false;
        // rook at h8 must not have previously moved
        rookFirstMove = grid[7]['h'].getPiece()->getFirstMove();
        if (!rookFirstMove) return false;
        // check if there is no piece between e8 and h8
        vector<Position> inBetweens {Position{"f8"}, Position{"g8"}};
        if (this->isBlocked(inBetweens)) return false;
        // king is not in check at e8, f8, g8
        if (this->threatenedBy(Position{"e8"}, whoseTurn).size() != 0 ||
            this->threatenedBy(Position{"f8"}, whoseTurn).size() != 0 ||
            this->threatenedBy(Position{"g8"}, whoseTurn).size() != 0) {
            return false;
        }
    } else if (m.from == Position{"e8"} && m.to == Position{"c8"}) {
        name = grid[7]['a'].getPiece()->getPiece();
        if (name != 'R' && name != 'r') return false;
        // rook at a8 must not have previously moved
        rookFirstMove = grid[7]['a'].getPiece()->getFirstMove();
        if (!rookFirstMove) return false;
        // check if there is no piece between e8 and a8
        vector<Position> inBetweens {Position{"b8"}, Position{"c8"}, Position{"d8"}};
        if (this->isBlocked(inBetweens)) return false;
        // king is not in check at c8, d8, e8
        if (this->threatenedBy(Position{"c8"}, whoseTurn).size() != 0 ||
            this->threatenedBy(Position{"d8"}, whoseTurn).size() != 0 ||
            this->threatenedBy(Position{"e8"}, whoseTurn).size() != 0) {
            return false;
        }
    }
    return true;
}

void Board::castle(Move m) {
    if (m.from == Position{"e1"} && m.to == Position{"g1"}) {
        // move king from e1 to g1, and modify piecesOnBoard, kings
        Piece *kingToBeMoved = grid[0]['e'].moveFrom();
        this->eraseFromMap(Position{"e1"});
        grid[0]['g'].moveTo(kingToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(kingToBeMoved->getPiece(), Position{"g1"});
        
        // move rook from h1 to f1, and modify piecesOnBoard, kings
        Piece *rookToBeMoved = grid[0]['h'].moveFrom();
        this->eraseFromMap(Position{"h1"});
        grid[0]['f'].moveTo(rookToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(rookToBeMoved->getPiece(), Position{"f1"});
        
        // modify history
        Move rookMove{Position{"h1"}, Position{"f1"}, false, true};
        history.emplace_back(m);
        history.emplace_back(rookMove);
    } else if (m.from == Position{"e1"} && m.to == Position{"c1"}) {
        // move king from e1 to c1, and modify piecesOnBoard, kings
        Piece *kingToBeMoved = grid[0]['e'].moveFrom();
        this->eraseFromMap(Position{"e1"});
        grid[0]['c'].moveTo(kingToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(kingToBeMoved->getPiece(), Position{"c1"});
        
        // move rook from a1 to d1, and modify piecesOnBoard, kings
        Piece *rookToBeMoved = grid[0]['a'].moveFrom();
        this->eraseFromMap(Position{"a1"});
        grid[0]['d'].moveTo(rookToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(rookToBeMoved->getPiece(), Position{"d1"});
        
        // modify history
        Move rookMove{Position{"a1"}, Position{"d1"}, false, true};
        history.emplace_back(m);
        history.emplace_back(rookMove);
    } else if (m.from == Position{"e8"} && m.to == Position{"g8"}) {
        // move king from e8 to g8, and modify piecesOnBoard, kings
        Piece *kingToBeMoved = grid[7]['e'].moveFrom();
        this->eraseFromMap(Position{"e8"});
        grid[7]['g'].moveTo(kingToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(kingToBeMoved->getPiece(), Position{"g8"});
        
        // move rook from h8 to f8, and modify piecesOnBoard, kings
        Piece *rookToBeMoved = grid[7]['h'].moveFrom();
        this->eraseFromMap(Position{"h8"});
        grid[7]['f'].moveTo(rookToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(rookToBeMoved->getPiece(), Position{"f8"});
        
        // modify history
        Move rookMove{Position{"h8"}, Position{"f8"}, false, true};
        history.emplace_back(m);
        history.emplace_back(rookMove);
    } else if (m.from == Position{"e8"} && m.to == Position{"c8"}) {
        // move king from e8 to c8, and modify piecesOnBoard, kings
        Piece *kingToBeMoved = grid[7]['e'].moveFrom();
        this->eraseFromMap(Position{"e8"});
        grid[7]['c'].moveTo(kingToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(kingToBeMoved->getPiece(), Position{"c8"});
        
        // move rook from a8 to d8, and modify piecesOnBoard, kings
        Piece *rookToBeMoved = grid[7]['a'].moveFrom();
        this->eraseFromMap(Position{"a8"});
        grid[7]['d'].moveTo(rookToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(rookToBeMoved->getPiece(), Position{"d8"});
        
        // modify history
        Move rookMove{Position{"a8"}, Position{"d8"}, false, true};
        history.emplace_back(m);
        history.emplace_back(rookMove);
    }
    
    // reset whoseTurn after castling
    if (whoseTurn == Colour::Black) this->setWhoseTurn(Colour::White);
    else if (whoseTurn == Colour::White) this->setWhoseTurn(Colour::Black);
}

Colour Board::getWhoseTurn() {
    return whoseTurn;
}


bool Board::isSetupComplete() {
    int whiteKingCount = 0;
    int blackKingCount = 0;
    int pawnCount = 0;
    for (auto p : piecesOnBoard) {
        Info i = p.second;
        if ((i.piece)->getPiece() == 'K') whiteKingCount += 1;
        if ((i.piece)->getPiece() == 'k') blackKingCount += 1;
        if (i.pos.row == 1 || i.pos.row == 8) {
            if ((i.piece)->getPiece() == 'P' || (i.piece)->getPiece() == 'p') pawnCount += 1;
        }
    }
    // not exactly one white king and one black king
    if (whiteKingCount != 1 || blackKingCount != 1) return false;
    
    // there is at least one pawn on the first or last row
    if (pawnCount != 0) return false;
    
    // neither king is in check
    if (this->isChecked(Colour::White) || this->isChecked(Colour::Black)) return false;
    return true;
}



ostream &operator<<(ostream &out, const Board &b) {
    if (b.td != nullptr) {
        out << *(b.td);
    }
    return out;
}




std::vector<Move*> Board::getLegalMoves(Position &pos) {
    std::vector<Move*> moves = grid[pos.row - 1][pos.col - 'a'].getLegalMoves();
    Move m;
    for (vector<Move*>::iterator it= moves.begin(); it < moves.end(); ++it) {
        m = **it;
        Info fromInfo = grid[m.from.row - 1][m.from.col - 'a'].getInfo(), toInfo = grid[m.to.row - 1][m.to.col - 'a'].getInfo();
        if (isBlocked(getInBetweenPositions(m))) {
            moves.erase(it);
            it -= 1;
        } else if ((toInfo.piece != nullptr) && (fromInfo.piece->getPieceColour() == toInfo.piece->getPieceColour())) {
            moves.erase(it);
            it -= 1;
        }
    }
    return moves;
}

std::vector<Info> Board::getPieces() {
    vector<Info> pieces;
    for (map<std::string, Info>::iterator it = piecesOnBoard.begin(); it != piecesOnBoard.end(); it++) {
        pieces.push_back(it->second);
    }
    return pieces;
}

std::vector<Info> Board::threatenedBy(Position pos, Colour myColour) {
    std::vector<Info> threatenInfo;
    Colour oppoColour = Colour::White;
    if (myColour == oppoColour) oppoColour = Colour::Black;
    vector<Move *> allLegalMoves = getAllLegalMoves(oppoColour);
    for (Move *move: allLegalMoves) {
        if (move->to == pos) threatenInfo.push_back(grid[pos.row - 1][pos.col - 'a'].getInfo());
    }
    for (Move *move: allLegalMoves) {delete move;}
    return threatenInfo;
}

bool Board::isCheckmate(Colour colour) {
    for (map<std::string, Info>::iterator it = kings.begin(); it != kings.end(); it++) {
        if (it->second.piece && it->second.piece->getPieceColour() == colour) return false;
    }
    return true;
}

bool Board::isChecked(Colour kingColour) {
    Colour oppoColour = Colour::White;
    if (kingColour == oppoColour) oppoColour = Colour::Black;
    for (map<std::string, Info>::iterator it = kings.begin(); it != kings.end(); it++) {
        if (it->second.piece && it->second.piece->getPieceColour() == kingColour) {
            if (threatenedBy(it->second.pos, kingColour).size()) return true;
        }
    }
    return false;
}

bool Board::setWhoseTurn(Colour colour) {
    whoseTurn = colour;
    return true;
}

std::vector<Move*> Board::getAllLegalMoves(Colour myColour) {
    vector<Move*> allLegalMoves, moves;
    Position pos;
    Piece* piece;
    
    for (Info &pieceInfo: getPieces()) {
        pos = pieceInfo.pos;
        piece = pieceInfo.piece;
        if (piece->getPieceColour() == myColour) {
            moves = getLegalMoves(pos);
            allLegalMoves.insert(allLegalMoves.end(),moves.begin(),moves.end());
        }
    }
    return allLegalMoves;
}

Info Board::getInfo(Position pos) {return grid[pos.row - 1][pos.col - 'a'].getInfo();}


bool Board::isStalemate(Colour colour) {return false;}
