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

Level1::Level1(Colour colour): Computer(colour) {}
Move Level1::nextMove() {
    Move randMove;
//    vector<Move *> allLegalMoves;
//    
//    // get legal moves
//    allLegalMoves = board->getAllLegalMoves(colour);
//    randMove = *allLegalMoves[int(rand() * allLegalMoves.size())];
//    for (Move *move: allLegalMoves) {delete move;}
    return randMove;
}
