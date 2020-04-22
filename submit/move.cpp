//
//  move.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-21.
//  Copyright © 2020 CS246Team. All rights reserved.
//
#include "move.h"
#include "board.h"
Move::Move(): promotion(false), castling(false), enPassant(false), captured('/') {}
Move::Move(Position from, Position to, char captured): from(from), to(to), captured(captured), promotion(false), castling(false), enPassant(false) {}
Move::Move(Position from, Position to, bool promotion, bool castling, bool enPassant) : from(from), to(to), promotion(promotion), castling(castling), enPassant(enPassant), captured('/') {};

void Move::reverse() {
    Position tmp = from;
    from = to;
    to = tmp;
}

int Move::advantage(Board *board, Colour myColour) {
    int adv = 0;

    if (board->getInfo(from).piece && toupper(board->getInfo(from).piece->getPiece()) == 'P') {
        if(to.row == 1 || to.row == 8) adv += 70 - 10;
        if (board->protectedBy(to, myColour).size() > 1) {
            adv += 5;
        }
        // adv += to.row;
    } else if (board->getInfo(from).piece && toupper(board->getInfo(from).piece->getPiece()) == 'N') {
        adv += 4 - abs(to.row - 5);
    }
    if (board->getInfo(to).piece == nullptr) return adv;
    adv += board->getInfo(to).piece->getForce();
    return adv;
}

int Move::threat(Board *board, Colour myColour) {
    int threaten = 0, protection = 0, force = 0;
    if (board->getInfo(from).piece) force = board->getInfo(from).piece->getForce();
    if (board->threatenedBy(from, myColour).size() != 0) {
        threaten -= force;
        if (board->protectedBy(from, myColour).size() != 0) protection -= force;
    }
    try {
        board->move(*this);
    } catch (ErrorMessage &e) {}
    if (board->threatenedBy(to, myColour).size() != 0) {
        threaten += force;
        if (board->protectedBy(to, myColour).size() > 1) protection += force;
    }
    
    board->undoMove();
    
    if (board->getWhoseTurn() == Colour::Black) { board->setWhoseTurn(Colour::White);
    } else if (board->getWhoseTurn() == Colour::White) board->setWhoseTurn(Colour::Black);
    
    return (threaten - protection);
}
