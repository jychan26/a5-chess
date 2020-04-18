#include "cell.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
using namespace std;
#include <iostream>

Cell::Cell(Position pos, Colour cellColour) : pos{pos}, cellColour{cellColour} {}

Cell::~Cell() {
    delete piece;
}

Piece *createPiece(char name) {
    Piece *p = nullptr;
    if (name == 'R') {
        p = new Rook('R', Colour::White);
    }  else if (name == 'N') {
        p = new Knight('N', Colour::White);
    } else if (name == 'B') {
        p = new Bishop('B', Colour::White);
    } else if (name == 'Q') {
        p = new Queen('Q', Colour::White);
    } else if (name == 'K') {
        p = new King('K', Colour::White);
    } else if (name == 'P') {
        p = new Pawn('P', Colour::White);
    } else if (name == 'r') {
        p = new Rook('r', Colour::Black);
    } else if (name == 'n') {
        p = new Knight('n', Colour::Black);
    } else if (name == 'b') {
        p = new Bishop('b', Colour::Black);
    } else if (name == 'q') {
        p = new Queen('q', Colour::Black);
    } else if (name == 'k') {
        p = new King('k', Colour::Black);
    } else if (name == 'p') {
        p = new Pawn('p', Colour::Black);
    }
    return p;
}

void Cell::setPiece(char name) {
    delete piece;
    piece = nullptr;
    piece = createPiece(name);
    // update the observers
    this->notifyObservers();
}


void Cell::removePiece() {
    delete piece;
    piece = nullptr;
    // update the observers
    this->notifyObservers();
}

Piece *Cell::getPiece() const {
    return this->piece;
}

Info Cell::getInfo() const {
    Info i{pos, cellColour, piece};
    return i;
}

Piece *Cell::moveFrom() {
    char name = piece->getPiece();
    bool firstMove = piece->getFirstMove();
    this->removePiece(); // also updates the observers when removePiece is called
    Piece *pieceToBeMoved = createPiece(name);
    // we should not change the firstMove field of the piece we move
    pieceToBeMoved->setFirstMove(firstMove);
    return pieceToBeMoved;
}

void Cell::moveTo(Piece *&pieceToBeMoved) {
    delete piece;
    piece = nullptr;
    piece = pieceToBeMoved;
    // set firstMove to false
    piece->setFirstMove(false);
    // update the observers
    this->notifyObservers();
}

bool Cell::isObeyRule(Move m) {
    return piece->isObeyRule(m);
}

vector<Position> Cell::getInBetweenPositions(Move m) {
    return piece->getInBetweenPositions(m);
}

void Cell::promote(char name) {
    // remove pawn and promote with new piece
    delete piece;
    piece = nullptr;
    piece = createPiece(name);
    this->notifyObservers();
}
