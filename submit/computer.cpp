//
//  computer.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#include "computer.h"
Computer::Computer(Colour colour, Board *board): colour(colour), board(board) {}

Move Computer::nextMove() {
    Move move;
    return move;
}

char Computer::getPromotion() {
    return promotion;
}



