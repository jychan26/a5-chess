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
    Colour colour;
public:
    Computer(Colour colour);
    virtual Move nextMove() = 0;
};


#endif /* computer_hpp */
