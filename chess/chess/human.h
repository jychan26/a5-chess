//
//  human.hpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#ifndef human_hpp
#define human_hpp

#include <stdio.h>
#include "chessplayer.h"
#include <sstream>
#include <string>
#include <iostream>
class Human: public ChessPlayer{
    char promotion;
public:
    Move nextMove() override;
    char getPromotion() override;
};

#endif /* human_hpp */
