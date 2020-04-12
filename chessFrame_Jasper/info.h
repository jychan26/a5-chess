#ifndef INFO_H
#define INFO_H
#include "position.h"
#include "colour.h"
#include "piece.h"

struct Info {
    Position pos;
    Colour cellColour;
    Piece *piece;
};

#endif
