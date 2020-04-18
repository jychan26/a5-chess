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

//int forceAdvantage(Board *board, Move m) {
//    if (board->getInfo(m.to).piece == nullptr) return 0;
//    return board->getInfo(m.to).piece->getForce();
//    
//}
//
//Level2::Level2(Colour colour): Computer(colour) {}
//Move Level2::nextMove() {
//    vector<Move> km, legalMoves, moves;
//    Position pos, from, to;
//    Piece* piece;
//    int idx = 0;
//    
//    // get legal moves
//    for (Info &pieceInfo: board->getPieces()) {
//        pos = pieceInfo.pos;
//        piece = pieceInfo.piece;
//        if (piece->getPieceColour() == colour) {
//            moves = board->getLegalMoves(pos);
//            legalMoves.insert(legalMoves.end(),moves.begin(),moves.end());
//        }
//    }
//    
//    // choose the best legal move
//    for (int i = 1; i < legalMoves.size(); i++) {
//        if (forceAdvantage(board, legalMoves[i]) > forceAdvantage(board, legalMoves[idx])) idx = i;
//    }
//    
//    return legalMoves[idx];
//}
