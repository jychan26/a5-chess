//
//  level3.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#include "level3.h"
static int forceAdvantage(Board *board, Move m) {
    if (board->getInfo(m.to).piece == nullptr) return 0;
    return board->getInfo(m.to).piece->getForce();
}

static int forceThreaten(Board *board, Move m, Colour myColour) {
    if (board->threatenedBy(m.from, myColour).size() != 0) {
        if (board->threatenedBy(m.to, myColour).size() != 0) {return 0;}
        return -1 * board->getInfo(m.from).piece->getForce();
    }
    if (board->threatenedBy(m.to, myColour).size() != 0) return board->getInfo(m.from).piece->getForce();
    return 0;
}

Level3::Level3(Colour colour, Board *board): Computer(colour, board) {}
Move Level3::nextMove() {
    vector<Move*> bestMoves, allLegalMoves, moves;
    Position pos, from, to;
    Move bestMove;
    vector<Info> threatenedPieces;
    int idx = 0;
    int advantage1, advantage2, threaten1, threaten2;
    // get legal moves
    allLegalMoves = board->getAllLegalMoves(colour);
    bestMoves.push_back(allLegalMoves[idx]);
    
    // get threatenedPieces
//    for (Info &pieceInfo: board->getPieces()) {
//        if (board->threatenedBy(pieceInfo.pos, colour).size() != 0) {
//            if (threatenedPieces.size() == 0) {
//                threatenedPieces.push_back(pieceInfo);
//            } else {
//                for (vector<Info>::iterator it= threatenedPieces.begin(); it < threatenedPieces.end(); ++it) {
//                    Info currentPiece = *it;
//                    if (currentPiece.piece->getForce() < pieceInfo.piece->getForce()) {
//                        threatenedPieces.insert(it, pieceInfo);
//                        break;
//                    }
//                }
//            }
//        }
//    }
    
    // sort the bestMoves
    for (int i = 1; i < allLegalMoves.size(); i++) {
        for (vector<Move*>::iterator it= bestMoves.begin(); it != bestMoves.end(); it += 1) {
            Move currentMove = **it;
            if (it == bestMoves.end() - 1) {
                bestMoves.push_back(allLegalMoves[i]);
                break;
            }
            advantage1 = forceAdvantage(board, *allLegalMoves[i]);
            advantage2 = forceAdvantage(board, currentMove);
            threaten1 = forceThreaten(board, *allLegalMoves[i], colour);
            threaten2 = forceThreaten(board, currentMove, colour);
            if (advantage1 - threaten1 >= advantage2 - threaten2) {
                bestMoves.insert(it, allLegalMoves[i]);
                break;
            }
        }
    }
    

    
//    for (vector<Info>::iterator it = threatenedPieces.begin(); it < threatenedPieces.end(); ++it) {
//        Info currentPiece = *it;
//        for (int i = 1; i < allLegalMoves.size(); i++) {
//            if (currentPiece.pos == allLegalMoves[i]->from) {bestMoves.push_back(allLegalMoves[i]);}
//        }
//    }
//
//    if (bestMoves.size() == 0)  {
//
//    }

    
//    int random = 0;
//    if (bestMoves.size() >= 1) random = rand() % bestMoves.size();
    bestMove = *bestMoves[0];
    for (Move *move: allLegalMoves) {delete move;}
    return bestMove;
}
