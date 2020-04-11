//
//  level4.hpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#ifndef level4_hpp
#define level4_hpp

#include <stdio.h>
#include "computer.h"
class Level4: public Computer{
  
public:
    Level4(Colour colour);
    Move nextMove() override;
};
#endif /* level4_hpp */
