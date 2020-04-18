#ifndef CELL_H
#define CELL_H
#include "colour.h"
#include "position.h"
#include "move.h"
#include "subject.h"
#include "piece.h"
#include <vector>


class Cell : public Subject {
    const Position pos;
    const Colour cellColour;
    Piece *piece = nullptr;
public:
    Cell(Position pos, Colour cellColour);
    ~Cell();
    void setPiece(char name);
    void removePiece();
    Piece *&moveFrom();
    void moveTo(Piece *&);
    Info getInfo() const override;
    bool isObeyRule(Move &m);
    std::vector<Position> getInBetweenPositions(Move &m);
    void promote(char name);
    bool isFirstMove();
    std::vector<Move*> getLegalMoves();
};

#endif

