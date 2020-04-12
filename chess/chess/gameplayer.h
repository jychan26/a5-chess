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
#include "chessplayer.h"
using namespace std;

class GamePlayer {
    ChessPlayer *player;
    Colour colour;
    int score;
public:
    GamePlayer(Colour colour);
    void setPlayer(string player);
    Move nextMove();
    ~GamePlayer();
    int getScore();
    Colour getColour();
    bool win(Colour colour);
    void stalemate();

};

#endif /* gameplayer_hpp */
