//
//  level1.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#include "level1.h"
#include <vector>
using namespace std;

Level1::Level1(Colour colour, Board *board): Computer(colour, board) {}
Move Level1::nextMove() {
    Move randMove;
    vector<Move *> allLegalMoves = board->getAllLegalMoves(colour);
    
    // get legal moves
    randMove = *allLegalMoves[rand() % allLegalMoves.size() - 1];
    for (Move *move: allLegalMoves) {delete move;}
    return randMove;
}
