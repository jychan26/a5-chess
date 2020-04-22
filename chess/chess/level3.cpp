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
    vector<Move*> sortedMoves, allLegalMoves, moves;
    Position pos, from, to;
    Move bestMove;
    vector<Info> threatenedPieces;
    int nofBestMoves = 1;
    int advantage1, advantage2, threaten1, threaten2;
    // get legal moves
    allLegalMoves = board->getAllLegalMoves(colour);
    sortedMoves.push_back(allLegalMoves[0]);
    
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
    
    // sort the sortedMoves
    for (int i = 1; i < allLegalMoves.size(); i++) {
        for (vector<Move*>::iterator it= sortedMoves.begin(); it != sortedMoves.end(); it += 1) {
            Move currentMove = **it;
            advantage1 = forceAdvantage(board, *allLegalMoves[i]);
            advantage2 = forceAdvantage(board, currentMove);
            threaten1 = forceThreaten(board, *allLegalMoves[i], colour);
            threaten2 = forceThreaten(board, currentMove, colour);
            if (advantage1 - threaten1 >= advantage2 - threaten2) {
                sortedMoves.insert(it, allLegalMoves[i]);
                break;
            }
            if (it == sortedMoves.end() - 1) {
                sortedMoves.push_back(allLegalMoves[i]);
                break;
            }
        }
    }

// count best moves
    for (int i = 1; i < sortedMoves.size(); i++) {
        if (sortedMoves[i - 1]->advantage(board, colour) - sortedMoves[i - 1]->threat(board, colour) == sortedMoves[i]->advantage(board, colour) - sortedMoves[i]->threat(board, colour)) {
            nofBestMoves += 1;
        } else { break; }
    }
    
// debug
//        for (Move *randMove: sortedMoves) {
//            cout << randMove->from.col << randMove->from.row << "|" << randMove->to.col << randMove->to.row << ":" << randMove->advantage(board, colour) << "," << randMove->threat(board, Colour::White) << "     ";
//        }
//        cout << endl;
//    cout << nofBestMoves << endl;
    
//    for (vector<Info>::iterator it = threatenedPieces.begin(); it < threatenedPieces.end(); ++it) {
//        Info currentPiece = *it;
//        for (int i = 1; i < allLegalMoves.size(); i++) {
//            if (currentPiece.pos == allLegalMoves[i]->from) {sortedMoves.push_back(allLegalMoves[i]);}
//        }
//    }
//
//    if (sortedMoves.size() == 0)  {
//
//    }

    
    int random = 0;
    if (sortedMoves.size() >= 1) random = rand() % nofBestMoves;
    bestMove = *sortedMoves[random];
    for (Move *move: allLegalMoves) {delete move;}
    
    // set promotion
    promotion = NULL;
    if (board->getInfo(bestMove.from).piece && toupper(board->getInfo(bestMove.from).piece->getPiece()) == 'P' && (bestMove.to.row == 1 || bestMove.to.row == 8)) {
        if (colour == Colour::White) promotion = 'Q';
        if (colour == Colour::Black) promotion = 'q';
    }
    
    return bestMove;
}
