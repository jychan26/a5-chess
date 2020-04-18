#ifndef INFO_H
#define INFO_H
#include "position.h"
#include "colour.h"
#include "piece.h"

// Piece *createPiece(char name);

struct Info {
    Position pos;
    Colour cellColour;
    Piece *piece;
    Info(Position pos = {1, 'a'}, Colour cellColour = Colour::White, Piece *piece = nullptr);
};

#endif
