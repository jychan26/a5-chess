//
//  gameplayer.hpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-11.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#ifndef gameplayer_hpp
#define gameplayer_hpp
#include <string>
#include <stdio.h>
#include "move.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "human.h"

using namespace std;


class GamePlayer {
    ChessPlayer *player;
    Colour colour;
    float score;
public:
    GamePlayer(Colour colour);
    void setPlayer(string playerName, Board *board);
    Move nextMove();
    ~GamePlayer();
    float getScore();
    Colour getColour();
    bool win(Colour colour);
    void stalemate();
    char getPromotion();

};

#endif /* gameplayer_hpp */
