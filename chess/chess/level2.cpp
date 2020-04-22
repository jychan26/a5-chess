//
//  level2.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#include "level2.h"
#include <vector>
using namespace std;

static int forceAdvantage(Board *board, Move m) {
    if (board->getInfo(m.to).piece == nullptr) return 0;
    return board->getInfo(m.to).piece->getForce();
    
}

Level2::Level2(Colour colour, Board *board): Computer(colour, board) {}
Move Level2::nextMove() {
    vector<Move> bestMoves, allLegalMoves, moves;
    Position pos, from, to;
    Move bestMove;
    int advantage1, advantage2;
    int idx = 0;
    
    // get legal moves
    allLegalMoves = board->getAllLegalMoves(colour);
    bestMoves.push_back(allLegalMoves[idx]);
    // choose the best legal move
    for (int i = 1; i < allLegalMoves.size(); i++) {
        advantage1 = forceAdvantage(board, allLegalMoves[i]);
        advantage2 = forceAdvantage(board, allLegalMoves[idx]);
        if (advantage1 > advantage2) {
            idx = i;
            bestMoves.clear();
            bestMoves.push_back(allLegalMoves[i]);
        } else if (advantage1 == advantage2) {
            bestMoves.push_back(allLegalMoves[i]);
        }
    }
    int random = 0;
    if (bestMoves.size() >= 1) random = rand() % bestMoves.size();
    bestMove = bestMoves[random];
    
    // set promotion
    promotion = NULL;
    if (toupper(board->getInfo(bestMove.from).piece->getPiece()) == 'P' && (bestMove.to.row == 1 || bestMove.to.row == 8)) {
        if (colour == Colour::White) promotion = 'Q';
        if (colour == Colour::Black) promotion = 'q';
    }
    
    return bestMove;
}
