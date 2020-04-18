//
//  level2.hpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#ifndef level2_hpp
#define level2_hpp

#include <stdio.h>
#include "computer.h"
class Level2: public Computer{
  
public:
    Level2(Colour colour, Board *board);
    Move nextMove() override;
};
#endif /* level2_hpp */
