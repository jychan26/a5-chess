//
//  level1.hpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#ifndef level1_hpp
#define level1_hpp

#include <stdio.h>
#include "computer.h"
class Level1: public Computer{
  
public:
    Level1(Colour colour, Board *board);
    Move nextMove() override;
};
#endif /* level1_hpp */
