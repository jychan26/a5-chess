#ifndef CELL_H
#define CELL_H
#include "colour.h"
#include "position.h"
#include "move.h"
#include "subject.h"
// #include "piece.h"
#include <vector>

Piece *createPiece(char name);

class Cell : public Subject {
    const Position pos;
    const Colour cellColour;
    Piece *piece = nullptr;
public:
    Cell(Position pos, Colour cellColour);
    ~Cell();
    void setPiece(char name);
    void removePiece();
    Piece *getPiece() const; // can be deleted since we have getInfo
    Info getInfo() const override;
    Piece *moveFrom();
    void moveTo(Piece *&);
    bool isObeyRule(Move m);
    std::vector<Position> getInBetweenPositions(Move m);
    void promote(char name);
};

#endif

