//
//  main.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-08.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#include <iostream>
#include <string>
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "gameplayer.h"
#include "cell.h"
#include "board.h"
using namespace std;

int main(int argc, const char * argv[]) {
     //cin.exceptions(ios::eofbit|ios::failbit);
     Board board;
     string cmd;
     GamePlayer white{Colour::White}, black{Colour::Black};
     try {
         while (true) {
             cin >> cmd;
            if (cmd == "game") {
               string p1, p2;
               cin >> p1 >> p2;
               white.setPlayer(p1);
               black.setPlayer(p2);
               board.init();
                while (true) {
                    cin >> cmd;
                    if (cmd == "move") {
                        string m1, m2;
                       cin >> m1 >> m2;
                       board.move(m1, m2);
                    }
                }
            } else if (cmd == "setup") {
                
            }
        }
     }
     catch (ios::failure &) {}
}
