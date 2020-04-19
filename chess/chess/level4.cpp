//
//  level4.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#include "level4.h"
static int forceAdvantage(Board *board, Move m) {
    if (board->getInfo(m.to).piece == nullptr) return 0;
    return board->getInfo(m.to).piece->getForce();
    
}

Level4::Level4(Colour colour, Board *board): Computer(colour, board) {}
Move Level4::nextMove() {
    vector<Move*> km, allLegalMoves, moves;
    Position pos, from, to;
    Move bestMove;
    int idx = 0;
    
    // get legal moves
    allLegalMoves = board->getAllLegalMoves(colour);
    
    // choose the best legal move
    for (int i = 1; i < allLegalMoves.size(); i++) {
        if (forceAdvantage(board, *allLegalMoves[i]) > forceAdvantage(board, *allLegalMoves[idx])) idx = i;
    }
    bestMove = *allLegalMoves[idx];
    for (Move *move: allLegalMoves) {delete move;}
    return *allLegalMoves[idx];
}
