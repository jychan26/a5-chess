#ifndef MOVE_H
#define MOVE_H
#include "position.h"
#include "colour.h"
class Board;

struct Move {
    Position from;
    Position to;
    bool promotion;
    bool castling;
    bool enPassant;
    char captured;
    Move();
    Move(Position from, Position to, char captured);
    Move(Position from, Position to, bool promotion = false, bool castling = false, bool enPassant = false);
    
    void reverse();
    int advantage(Board *board, Colour myColour);
    int threat(Board *board, Colour myColour);
};

#endif
