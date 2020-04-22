
#include "board.h"
#include "cell.h"
#include "subject.h"
#include <cctype>
using namespace std;

Board::~Board() {
    delete td;
    delete gd;
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
    td = (!td) ? new TextDisplay(): td;
    gd = (!gd) ? new GraphicsDisplay(td): gd;
    // attach observers
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            grid[r][c].attach(td);
	    grid[r][c].attach(gd);
        }
    }
    // remove old pieces first for reinitialization
    for (int row = 6; row >= 3; --row) {
	    for (int c = 0; c < size; ++c) {
	 	   char column = 'a' + c;
		   Position pos{row, column};
		   this->removePiece(pos);
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
    
    // if move a pawn straight forward, then the pawn cannot capture pieces
    char name = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPiece();
    if ((name == 'p' || name == 'P') && this->isPawnForwardStraight(m)) {
        // if there is a piece in the destination cell, throw error message
        if (grid[m.to.row - 1][m.to.col - 'a'].getPiece() != nullptr) {
            throw ErrorMessage{"Pawn cannot capture on straight forward move."};
        }
    }
    
    // if move a pawn one square diagonally but there is no piece in destination cell
    // en passant or throw error message
    bool enPassant = false;
    name = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPiece();
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
        // if there is a piece to capture, we need to erase the captured piece from piecesOnBoard, kings
        // we also need to update the field captured of move m
        if (grid[m.to.row - 1][m.to.col - 'a'].getPiece() != nullptr) {
            this->eraseFromMap(m.to);
            m.captured = grid[m.to.row - 1][m.to.col - 'a'].getPiece()->getPiece();
        }
        grid[m.to.row - 1][m.to.col - 'a'].moveTo(pieceToBeMoved); // Cell::moveTo will notify observers
        // if a pawn makes a two-square move, then set its field isEnPassantValid to true
        if (twoSquaresMove) {
            grid[m.to.row - 1][m.to.col - 'a'].setIsEnPassantValid(true);
        }
        this->addToMap(pieceToBeMoved->getPiece(), m.to);
        history.emplace_back(m);
    } else { // en passant implementation
        // set the enPassant field of the move to true, update the captured field of the move
        m.enPassant = true;
        m.captured = grid[m.from.row - 1][m.to.col - 'a'].getPiece()->getPiece();
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
    
    // cannot make a move that puts your king in check
    if (this->isChecked(whoseTurn)) {
        this->undoMove();
        throw ErrorMessage{"Cannot make a move that puts your king in check."};
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
        name = grid[0]['h' - 'a'].getPiece()->getPiece();
        if (name != 'R' && name != 'r') return false;
        // rook at h1 must not have previously moved
        rookFirstMove = grid[0]['h' - 'a'].getPiece()->getFirstMove();
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
        name = grid[0]['a' - 'a'].getPiece()->getPiece();
        if (name != 'R' && name != 'r') return false;
        // rook at a1 must not have previously moved
        rookFirstMove = grid[0]['a' - 'a'].getPiece()->getFirstMove();
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
        name = grid[7]['h' - 'a'].getPiece()->getPiece();
        if (name != 'R' && name != 'r') return false;
        // rook at h8 must not have previously moved
        rookFirstMove = grid[7]['h' - 'a'].getPiece()->getFirstMove();
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
        name = grid[7]['a' - 'a'].getPiece()->getPiece();
        if (name != 'R' && name != 'r') return false;
        // rook at a8 must not have previously moved
        rookFirstMove = grid[7]['a' - 'a'].getPiece()->getFirstMove();
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
        Piece *kingToBeMoved = grid[0]['e' - 'a'].moveFrom();
        this->eraseFromMap(Position{"e1"});
        grid[0]['g' - 'a'].moveTo(kingToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(kingToBeMoved->getPiece(), Position{"g1"});
        
        // move rook from h1 to f1, and modify piecesOnBoard, kings
        Piece *rookToBeMoved = grid[0]['h' - 'a'].moveFrom();
        this->eraseFromMap(Position{"h1"});
        grid[0]['f' - 'a'].moveTo(rookToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(rookToBeMoved->getPiece(), Position{"f1"});
        
        // modify history
        Move rookMove{Position{"h1"}, Position{"f1"}, false, true};
        history.emplace_back(m);
        history.emplace_back(rookMove);
    } else if (m.from == Position{"e1"} && m.to == Position{"c1"}) {
        // move king from e1 to c1, and modify piecesOnBoard, kings
        Piece *kingToBeMoved = grid[0]['e' - 'a'].moveFrom();
        this->eraseFromMap(Position{"e1"});
        grid[0]['c' - 'a'].moveTo(kingToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(kingToBeMoved->getPiece(), Position{"c1"});
        
        // move rook from a1 to d1, and modify piecesOnBoard, kings
        Piece *rookToBeMoved = grid[0]['a' - 'a'].moveFrom();
        this->eraseFromMap(Position{"a1"});
        grid[0]['d' - 'a'].moveTo(rookToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(rookToBeMoved->getPiece(), Position{"d1"});
        
        // modify history
        Move rookMove{Position{"a1"}, Position{"d1"}, false, true};
        history.emplace_back(m);
        history.emplace_back(rookMove);
    } else if (m.from == Position{"e8"} && m.to == Position{"g8"}) {
        // move king from e8 to g8, and modify piecesOnBoard, kings
        Piece *kingToBeMoved = grid[7]['e' - 'a'].moveFrom();
        this->eraseFromMap(Position{"e8"});
        grid[7]['g' - 'a'].moveTo(kingToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(kingToBeMoved->getPiece(), Position{"g8"});
        
        // move rook from h8 to f8, and modify piecesOnBoard, kings
        Piece *rookToBeMoved = grid[7]['h' - 'a'].moveFrom();
        this->eraseFromMap(Position{"h8"});
        grid[7]['f' - 'a'].moveTo(rookToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(rookToBeMoved->getPiece(), Position{"f8"});
        
        // modify history
        Move rookMove{Position{"h8"}, Position{"f8"}, false, true};
        history.emplace_back(m);
        history.emplace_back(rookMove);
    } else if (m.from == Position{"e8"} && m.to == Position{"c8"}) {
        // move king from e8 to c8, and modify piecesOnBoard, kings
        Piece *kingToBeMoved = grid[7]['e' - 'a'].moveFrom();
        this->eraseFromMap(Position{"e8"});
        grid[7]['c' - 'a'].moveTo(kingToBeMoved); // Cell::moveTo will notify observers
        this->addToMap(kingToBeMoved->getPiece(), Position{"c8"});
        
        // move rook from a8 to d8, and modify piecesOnBoard, kings
        Piece *rookToBeMoved = grid[7]['a' - 'a'].moveFrom();
        this->eraseFromMap(Position{"a8"});
        grid[7]['d' - 'a'].moveTo(rookToBeMoved); // Cell::moveTo will notify observers
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
        out << *(b.gd);
    }
    return out;
}

std::vector<Move> Board::getPossibleMoves(Position &pos) {
    // getPossibleMoves(Position &pos) returns possible moves from Position pos,
    // including moves that put the king in check
    std::vector<Move> moves = grid[pos.row - 1][pos.col - 'a'].getLegalMoves();
    
    for (vector<Move>::iterator it= moves.begin(); it < moves.end(); ++it) {
        Move m = *it;
        bool erase = false;
        Info fromInfo = grid[m.from.row - 1][m.from.col - 'a'].getInfo();
        Info toInfo = grid[m.to.row - 1][m.to.col - 'a'].getInfo();
        char name = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPiece();
        if (this->isBlocked(this->getInBetweenPositions(m))) {
            // if move is blocked by pieces in between, it's not a legal move
            erase = true;
            // if move a pawn one square diagonally but there is no piece in destination cell
            // en passant or throw error message
        } else if ((toInfo.piece != nullptr) && (fromInfo.piece->getPieceColour() == toInfo.piece->getPieceColour())) {
            // if there is a piece in the destination cell and its colour is the same, then it's not a legal move
            erase = true;
        } else if ((name == 'p' || name == 'P') && this->isOneSquareDiagonal(m) && toInfo.piece == nullptr) {
            // if move a pawn one square diagonally but there is no piece in destination cell
            
            // if the cell where the would-be attacked pawn should have sit has no piece, then it's not a legal move
            if (grid[m.from.row - 1][m.to.col - 'a'].getPiece() == nullptr) {
                erase = true;
            } else {
                char besidePieceName = grid[m.from.row - 1][m.to.col - 'a'].getPiece()->getPiece();
                if (besidePieceName != 'p' && besidePieceName != 'P') {
                    // if the cell where the would-be attacked pawn should have sit has a piece that is not a pawn,
                    // then it's not a legal move
                    erase = true;
                }
                
                // if the cell where the would-be attacked pawn sits has the same colour,
                // then it's not a legal move
                if (!isOpponentPawn(besidePieceName)) {
                    erase = true;
                }
                
                // if isEnPassantValid field of the captured pawn is false, i.e. the opposing pawn does not
                // make a two-square move or the attack does not immediately follow, then it's not a legal move
                if (!grid[m.from.row - 1][m.to.col - 'a'].getPiece()->getIsEnPassantValid()) {
                    erase = true;
                }
                
                // The conditions of using en passant are satisfied, set enPassant to true
                if (!erase) {m.enPassant = true;}
            }
        } else if ((name == 'p' || name == 'P') && this->isPawnForwardStraight(m) && toInfo.piece != nullptr) {
            // if move a pawn straight forward and there is a piece in destination cell,
            // then it's not a legal move
            erase = true;
        }
        
        // erase the move not satisfied
        if (erase == true) {
            moves.erase(it);
            it -= 1;
        }
    }
    return moves;
}

std::vector<Move> Board::getAllPossibleMoves(Colour myColour) {
    // getAllPossibleMoves(Colour myColour) returns all possible moves of all pieces whose colour are myColour,
    // including moves that put the king in check
    vector<Move> allPossibleMoves, possibleMoves;
    for (Info &pieceInfo : getPieces()) {
        Position pos = pieceInfo.pos;
        Piece *piece = pieceInfo.piece;
        if (piece != nullptr) {
            if (piece->getPieceColour() == myColour) {
                possibleMoves = getPossibleMoves(pos);
                allPossibleMoves.insert(allPossibleMoves.end(), possibleMoves.begin(), possibleMoves.end());
            }
        }
    }
    return allPossibleMoves;
}


std::vector<Move> Board::getLegalMoves(Position &pos, Colour myColour) {
    // getLegalMoves(Position &pos, Colour myColour) returns the legal moves of pieces of myColour
    // from Position pos, not including moves that put the king in check
    std::vector<Move> possibleMoves = getPossibleMoves(pos);
    
    for (vector<Move>::iterator it= possibleMoves.begin(); it < possibleMoves.end(); ++it) {
        Move pm = *it;
        bool erase = false;
        bool isEnPassantValid = grid[pos.row - 1][pos.col - 'a'].getPiece()->getIsEnPassantValid();
        bool firstMove = grid[pos.row - 1][pos.col - 'a'].getPiece()->getFirstMove();
        
        // do the move first
        if (!pm.enPassant) {
            // move the piece, modify piecesOnBoard, kings and history
            Piece *pieceToBeMoved = grid[pm.from.row - 1][pm.from.col - 'a'].moveFrom();
            this->eraseFromMap(pm.from);
            // if there is a piece to capture, we need to erase the captured piece from piecesOnBoard, kings
            // we also need to update the field captured of move m
            if (grid[pm.to.row - 1][pm.to.col - 'a'].getPiece() != nullptr) {
                this->eraseFromMap(pm.to);
                pm.captured = grid[pm.to.row - 1][pm.to.col - 'a'].getPiece()->getPiece();
            }
            grid[pm.to.row - 1][pm.to.col - 'a'].moveTo(pieceToBeMoved); // Cell::moveTo will notify observers
            this->addToMap(pieceToBeMoved->getPiece(), pm.to);
            history.emplace_back(pm);
        } else { // en passant implementation
            // set the enPassant field of the move to true, update the captured field of the move
            pm.enPassant = true;
            pm.captured = grid[pm.from.row - 1][pm.to.col - 'a'].getPiece()->getPiece();
            // move the attacking pawn one square diagonally
            Piece *pawnToBeMoved = grid[pm.from.row - 1][pm.from.col - 'a'].moveFrom();
            this->eraseFromMap(pm.from);
            grid[pm.to.row - 1][pm.to.col - 'a'].moveTo(pawnToBeMoved);
            this->addToMap(pawnToBeMoved->getPiece(), pm.to);
            history.emplace_back(pm);
            // remove the attacked pawn from the board, modify piecesOnBoard, kings
            grid[pm.from.row - 1][pm.to.col - 'a'].removePiece();
            this->eraseFromMap(Position{pm.from.row, pm.to.col});
        }
        
        Colour oppoColour = (myColour == Colour::White ? Colour::Black : Colour::White);
        vector<Move> allControlledMoves = getAllPossibleMoves(oppoColour);
        
        // check if my king is in check after making a move of my piece
        for (vector<Move>::iterator it = allControlledMoves.begin(); it < allControlledMoves.end(); ++it) {
            Move cm = *it;
            Position myKingPos;
            // find the position of my king
            for (map<std::string, Info>::iterator it = kings.begin(); it != kings.end(); ++it) {
                if (it->second.piece && it->second.piece->getPieceColour() == myColour) {
                    myKingPos = it->second.pos;
                }
            }
            if (cm.to == myKingPos) {
                erase = true;
                break;
            }
        }
        
        // no matter whether the move puts your king in check, we need to undo the move
        this->undoMove();
        
        // if a pawn makes a two-square move, then set its field isEnPassantValid to true
        if (isEnPassantValid) {
            grid[pos.row - 1][pos.col - 'a'].getPiece()->setIsEnPassantValid(true);
        }
        
        // we need to set the value of firstMove to be the same as before moving
        grid[pos.row - 1][pos.col - 'a'].getPiece()->setFirstMove(firstMove);
        
        // erase the move from possibleMoves that puts the king in check after move
        if (erase) {
            possibleMoves.erase(it);
            it -= 1;
        }
    }
    return possibleMoves;
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
    vector<Move> allPossibleMoves = getAllPossibleMoves(oppoColour);
    for (Move move: allPossibleMoves) {
        if (move.to == pos) threatenInfo.push_back(grid[pos.row - 1][pos.col - 'a'].getInfo());
    }
    return threatenInfo;
}
        
std::vector<Info> Board::protectedBy(Position pos, Colour myColour) {
    std::vector<Info> protectInfo;
    Colour oppoColour = Colour::White;
    if (myColour == oppoColour) oppoColour = Colour::Black;
    grid[pos.row - 1][pos.col - 'a'].changeColour();
    protectInfo = threatenedBy(pos, oppoColour);
    grid[pos.row - 1][pos.col - 'a'].changeColour();
    return protectInfo;
}
        
bool Board::isCheckmate(Colour colour) {
    //    map<std::string, Info>::iterator it;
    //    bool noLegalMoves = false;
    //    vector<Move> moves;
    
    //    for (it = kings.begin(); it != kings.end(); it++) {
    //        Info kingInfo = it->second;
    //        noLegalMoves = false;
    //        moves = getLegalMoves(kingInfo.pos, oppoColour);
    //        if (moves.size() == 0) noLegalMoves = true;
    //        for (auto &move: moves) delete move;
    //        if (kingInfo.piece && kingInfo.piece->getPieceColour() == oppoColour && threatenedBy(kingInfo.pos, oppoColour).size() > 0 && noLegalMoves) return true;
    //    }
    Colour oppoColour = Colour::White;
    if (colour == oppoColour) oppoColour = Colour::Black;
    vector<Move> allLegalMoves = getAllLegalMoves(oppoColour);
    unsigned long nofMoves = allLegalMoves.size();
    if (nofMoves == 0 && isChecked(oppoColour)) return true;
    return false;
}

bool Board::isChecked(Colour kingColour) {
    map<std::string, Info>::iterator it;
    Colour oppoColour = Colour::White;
    if (kingColour == oppoColour) oppoColour = Colour::Black;
    for (it = kings.begin(); it != kings.end(); it++) {
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

std::vector<Move> Board::getAllLegalMoves(Colour myColour) {
    // getAllLegalMoves(Colour myColour) returns all legal moves of all pieces whose colour are myColour,
    // not including moves that put the king in check
    vector<Move> allLegalMoves, moves;
    Position pos;
    Piece* piece;
    
    for (Info &pieceInfo: getPieces()) {
        pos = pieceInfo.pos;
        piece = pieceInfo.piece;
        if (piece != nullptr) {
            if (piece->getPieceColour() == myColour) {
                moves = getLegalMoves(pos, myColour);
                allLegalMoves.insert(allLegalMoves.end(),moves.begin(),moves.end());
            }
        }
    }
    return allLegalMoves;
}

Info Board::getInfo(Position pos) {return grid[pos.row - 1][pos.col - 'a'].getInfo();}


bool Board::isStalemate() {
    vector<Move> movesWhite, movesBlack;
    size_t sizeWhite;
    movesWhite = getAllLegalMoves(Colour::White);
    sizeWhite = movesWhite.size();
    if (sizeWhite == 0 && !this->isChecked(Colour::White)) {
        return true;
    }
    movesBlack = getAllLegalMoves(Colour::Black);
    if (this->getAllLegalMoves(Colour::Black).size() == 0 && !this->isChecked(Colour::Black)) {
        return true;
    }
    return false;
}


bool Board::isOpponentPawn(char name) {
    if (whoseTurn == Colour::White) {
        return name == 'p';
    } else {
        return name == 'P';
    }
}

bool Board::isOneSquareDiagonal(Move m) {
    if (grid[m.from.row - 1][m.from.col - 'a'].getPiece() == nullptr) return false;
    Colour pieceColour = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPieceColour();
    if (pieceColour == Colour::White) {
        if (m.to.row - m.from.row == 1 &&
            (m.to.col - m.from.col == 1 || m.to.col - m.from.col == -1)) {
            return true;
        }
        return false;
    } else {
        if (m.to.row - m.from.row == -1 &&
            (m.to.col - m.from.col == 1 || m.to.col - m.from.col == -1)) {
            return true;
        }
        return false;
    }
}

bool Board::isPawnMoveTwoSquares(Move m) {
    if (grid[m.from.row - 1][m.from.col - 'a'].getPiece() == nullptr) return false;
    char name = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPiece();
    Colour pieceColour = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPieceColour();
    if (name != 'p' && name != 'P') {
        return false;
    }
    if (pieceColour == Colour::White) {
        return m.to.row - m.from.row == 2;
    } else {
        return m.to.row - m.from.row == -2;
    }
}

bool Board::isPawnForwardStraight(Move m) {
    if (grid[m.from.row - 1][m.from.col - 'a'].getPiece() == nullptr) return false;
    char name = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPiece();
    Colour pieceColour = grid[m.from.row - 1][m.from.col - 'a'].getPiece()->getPieceColour();
    if (name != 'p' && name != 'P') {
        return false;
    }
    if (pieceColour == Colour::White) {
        return ((m.to.row - m.from.row == 1 && m.to.col == m.from.col)
                || m.to.row - m.from.row == 2);
    } else {
        return ((m.to.row - m.from.row == -1 && m.to.col == m.from.col)
                || m.to.row - m.from.row == -2);
    }
}

bool Board::undoMove() {
    if (history.size() == 0) return false;
    char piece;
    int offset;
    Cell *from, *to;
    Colour myColour;
    Move lastMove = history.back();
    history.pop_back();
    lastMove.reverse();
    
    from = &grid[lastMove.from.row - 1][lastMove.from.col - 'a'];
    to = &grid[lastMove.to.row - 1][lastMove.to.col - 'a'];
    myColour = from->getInfo().piece->getPieceColour();
    if (lastMove.promotion) {
        if (myColour == Colour::White) {
            piece = 'P';
        } else piece = 'p';
        from->removePiece();
        this->eraseFromMap(lastMove.from);
        to->setPiece(piece);
        to->getPiece()->setFirstMove(false);
        this->addToMap(piece, lastMove.to);
        // if the pawn captured a piece before promotion,
        // then we need to place back the captured piece onto the board
        if (lastMove.captured != '/') {
            from->setPiece(lastMove.captured);
            this->addToMap(lastMove.captured, lastMove.from);
        }
    } else if (lastMove.enPassant) {
        if (myColour == Colour::White) {
            offset = -1;
        } else offset = 1;
        moveNoCapture(lastMove);
        grid[lastMove.from.row - 1 + offset][lastMove.from.col - 'a'].setPiece(lastMove.captured);
        grid[lastMove.from.row - 1 + offset][lastMove.from.col - 'a'].setIsEnPassantValid(true);
        this->addToMap(lastMove.captured, Position{lastMove.from.row + offset, lastMove.from.col});
    } else if (lastMove.castling) {
        char name = from->getInfo().piece->getPiece();
        moveNoCapture(lastMove);
        // if the pice we move back is a rook, then we still need to call undoMove to move back the king
        if (name == 'r' || name == 'R') {
            undoMove();
        }
    } else if (!(lastMove.captured == '/')) {
        moveNoCapture(lastMove);
        from->setPiece(lastMove.captured);
        this->addToMap(lastMove.captured, lastMove.from);
    } else{
        moveNoCapture(lastMove);
    }
    
    return true;
}

void Board::moveNoCapture(Move m) {
    // assume move is valid, and move does not capture pieces
    Cell *fromCell = &grid[m.from.row - 1][m.from.col - 'a'];
    Cell *toCell = &grid[m.to.row - 1][m.to.col - 'a'];
    char piece = fromCell->getInfo().piece->getPiece();
    // move the piece, and modify piecesOnBoard, kings
    fromCell->removePiece();
    this->eraseFromMap(m.from);
    toCell->setPiece(piece);
    this->addToMap(piece, m.to);
}

void Board::displayErrorMessage(ErrorMessage &e) {
	cout << e.getErrorMessage() << endl;
	gd->displayErrorMessage(e);
}

void Board::clearErrorMessage() {
	gd->clearErrorMessage();

}

void Board::displayMessage(string s) {
	string delim = "\n";
	unsigned long pos = 0;
	string token;
	int count = 0;
	while ((pos = s.find(delim)) != string::npos) {
		token = s.substr(0, pos);
		cout << token << endl;
		gd->displayMessage(token, count);
		s.erase(0, pos + delim.length());
		++count;
	}
}
