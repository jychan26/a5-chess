#ifndef MOVE_H
#define MOVE_H
#include "position.h"

struct Move {
    Position from;
    Position to;
    bool promotion;
    bool castling;
    bool enPassant;
    char captured;
    Move(): promotion(false), castling(false) {}
    Move(Position from, Position to, char captured): from(from), to(to), captured(captured), promotion(false), castling(false), enPassant(false) {}
    Move(Position from, Position to, bool promotion = false, bool castling = false, bool enPassant = false) : from(from), to(to), promotion(promotion), castling(castling), enPassant(enPassant) {};
    void reverse() {
        Position tmp = from;
        from = to;
        to = tmp;
    }
};

#endif
