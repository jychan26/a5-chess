//
//  level3.hpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#ifndef level3_hpp
#define level3_hpp

#include <stdio.h>
#include "computer.h"
class Level3: public Computer{
  
public:
    Level3(Colour colour, Board *board);
    Move nextMove() override;
};
#endif /* level3_hpp */
