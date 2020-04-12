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
    vector<Move> moves = board->getLegalMoves();
    return moves[rand() * moves.size()];
}
