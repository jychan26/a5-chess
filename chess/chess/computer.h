//
//  computer.hpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#ifndef computer_hpp
#define computer_hpp

#include <stdio.h>
#include "chessplayer.h"
class Computer: public ChessPlayer{
protected:
    char promotion;
    Colour colour;
    Board *board;
public:
    Computer(Colour colour, Board *board);
    virtual Move nextMove() override;
    char getPromotion() override;
};


#endif /* computer_hpp */
