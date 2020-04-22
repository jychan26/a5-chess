//
//  human.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#include "human.h"

Move Human::nextMove() {
    Move move;
    string line, m1, m2;
    Position pos1, pos2;
    try {
        getline(cin, line);
        istringstream iss_line{line};
        iss_line >> m1 >> m2;
        pos1.convert(m1);
        pos2.convert(m2);
        move.from = pos1;
        move.to = pos2;
        move.promotion = false;
        move.castling = false;
        promotion = NULL;
        iss_line >> promotion;
    } catch (ios::failure &e) {}
        return move;
}

char Human::getPromotion() {
    return promotion;
}
