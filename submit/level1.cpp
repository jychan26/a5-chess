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
    vector<Move> allLegalMoves = board->getAllLegalMoves(colour);
    int random = rand() % allLegalMoves.size();
    
    // get legal moves
    randMove = allLegalMoves[random];
    
    // set promotion
    promotion = NULL;
    if (toupper(board->getInfo(randMove.from).piece->getPiece()) == 'P' && (randMove.to.row == 1 || randMove.to.row == 8)) {
        if (colour == Colour::White) promotion = 'Q';
        if (colour == Colour::Black) promotion = 'q';
    }
    
    return randMove;
}
