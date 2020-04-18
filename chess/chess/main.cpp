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
//    Board board;
//    string cmd, p1, p2, m1, m2;
//    char pieceName;
//    GamePlayer white{Colour::White}, black{Colour::Black};
//    Colour whoseTurn;
//    Position pos1, pos2;
//    Move move;
//    istringstream iss;
//    board.init();
//    try {
//        while (true) {
//            cin >> cmd;
//            if (cmd == "game") {
//                cout << board;
//                cin >> p1 >> p2;
//                white.setPlayer(p1);
//                black.setPlayer(p2);
//
//                while (true) {
//                    cin >> cmd;
//                    whoseTurn = board.getWhoseTurn();
//                    if (cmd == "move") {
//                        cin >> m1 >> m2;
//                        pos1.convert(m1);
//                        pos2.convert(m2);
//                        move.from = pos1;
//                        move.to = pos2;
//                        board.move(move);
//                        cout << board;
//                        if (board.isCheckmate(whoseTurn)) {
//                            cout << "Checkmate! ";
//                            if (white.win(whoseTurn)) cout << "White wins!";
//                            if (black.win(whoseTurn)) cout << "Black wins!";
//                            board.init();
//                            break;
//                        } else if (board.isStalemate(whoseTurn)) {
//                            white.stalemate();
//                            black.stalemate();
//                            cout << "Stalemate! ";
//                            board.init();
//                            break;
//                        }
//                    } else if (cmd == "resign") {
//                        whoseTurn = board.getWhoseTurn();
//                        if (white.win(whoseTurn)) cout << "White wins!";
//                        if (black.win(whoseTurn)) cout << "Black wins!";
//                        board.init();
//                        break;
//                    }
//                }
//            } else if (cmd == "setup") {
//                cin >> cmd;
//                if (cmd == "+") {
//                    cin >> m1 >> m2;
//                    pieceName = *m1.begin();
//                    pos1.convert(m2);
//                    board.setPiece(pieceName, pos1);
//                } else if (cmd == "-") {
//                    cin >> m1;
//                    pos1.convert(m1);
//                    board.removePiece(m1);
//                } else if (cmd == "=") {
//                    cin >> m1;
//                    whoseTurn = Colour::Black;
//                    if (m1 == "white") whoseTurn = Colour::White;
//                    if (board.setWhoseTurn(whoseTurn)) cout << m1 <<"'s turn to go next.";
//                } else if (cmd == "done") {
//                    if (board.isSetupComplete()) break;
//                    cout << board;
//                    cout << "Please make sure that: \n1. the board contains exactly one white king and exactly one black king\n2.no pawns are on the first or last row of the board\n3. neither king is in check";
//                }
//            }
//        }
//    }
//    catch (ios::failure &) {}
}
