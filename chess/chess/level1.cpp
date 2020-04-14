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

//Level1::Level1(Colour colour): Computer(colour) {}
//Move Level1::nextMove() {
//    vector<Move> legalMoves, moves;
//    Position pos;
//    Piece* piece;
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
//    return legalMoves[int(rand() * legalMoves.size())];
//}
