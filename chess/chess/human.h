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
class Human: public ChessPlayer{
  
public:
    Move nextMove() override;
};

#endif /* human_hpp */
