#ifndef INFO_H
#define INFO_H
#include "position.h"
#include "colour.h"
#include "piece.h"

struct Info {
    Position pos;
    Colour cellColour;
    Piece *piece;
    // ctor, dtor, copy ctor
    Info(Position pos, Colour cellColour, Piece *piece): pos(pos), cellColour(cellColour), piece(piece) {}
    Info(const Info &other): pos(other.pos), cellColour(other.cellColour), piece(other.piece) {}
};

#endif
