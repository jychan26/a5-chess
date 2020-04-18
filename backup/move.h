#ifndef MOVE_H
#define MOVE_H
#include "position.h"

struct Move {
    Position from;
    Position to;
    bool promotion;
    bool castling;
    char captured;
    Move(): promotion(false), castling(false) {}
    Move(Position from, Position to, char captured): from(from), to(to), captured(captured), promotion(false), castling(false) {}
    Move(Position from, Position to, bool promotion = false, bool castling= false) : from(from), to(to), promotion(promotion), castling(castling) {};
    void reverse() {
        Position tmp = from;
        from = to;
        to = tmp;
    }
};

#endif
