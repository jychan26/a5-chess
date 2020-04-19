//
//  player.hpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include "move.h"
#include "colour.h"
#include <stdio.h>
#include "board.h"
class ChessPlayer {
public:
    virtual Move nextMove() = 0;
    virtual char getPromotion() = 0;
};
#endif
