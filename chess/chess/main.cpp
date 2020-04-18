//
//  main.cpp
//  chess
//
//  Created by Jingtong Hu on 2020-04-08.
//  Copyright © 2020 CS246Team. All rights reserved.
//

#include <iostream>
#include <sstream>
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
    Colour whoseTurn;
    Position pos1, pos2;
    Move move;
    istringstream iss;
    board.init();
    try {
        while (true) {
            cin >> cmd;
            if (cmd == "game") {
                string p1, p2;
                cout << board;
                cin >> p1 >> p2;
                white.setPlayer(p1);
                black.setPlayer(p2);
                
                while (true) {
                    cin >> cmd;
                    whoseTurn = board.getWhoseTurn();
                    if (cmd == "move") {
                        string m1, m2;
                        cin >> m1 >> m2;
                        pos1.col = m1.front();
                        pos2.col = m2.front();
                        m1 = m1.back();
                        m2 = m2.back();
                        iss.str(m1);
                        iss >> pos1.row;
                        iss.clear();
                        iss.str(m2);
                        iss >> pos2.row;
                        iss.clear();
                        move.from = pos1;
                        move.to = pos2;
                        board.move(move);
                        cout << board;
                        if (board.isCheckmate(whoseTurn)) {
                            cout << "Checkmate! ";
                            if (white.win(whoseTurn)) cout << "White wins!";
                            if (black.win(whoseTurn)) cout << "Black wins!";
                            board.init();
                            break;
                        } else if (board.isStalemate(whoseTurn)) {
                            white.stalemate();
                            black.stalemate();
                            cout << "Stalemate! ";
                            board.init();
                            break;
                        }
                     else if (cmd == "resign") {
                        whoseTurn = board.getWhoseTurn();
                        if (white.win(whoseTurn)) cout << "White wins!";
                        if (black.win(whoseTurn)) cout << "Black wins!";
                        board.init();
                        break;
                    }
                }
            } else if (cmd == "setup") {
                cin >> cmd;
                if (cmd == "+") {
                    
                } else if (cmd == "-") {
                    
                } else if (cmd == "=") {
                    
                } else if (cmd == "done") {
                    if (board.isSetupComplete()) break;
                    cout << "Please make sure that: \n1. the board contains exactly one white king and exactly one black king\n2.no pawns are on the first or last row of the board\n3. neither king is in check";
                }
            }
        }
    }
    catch (ios::failure &) {}
}
