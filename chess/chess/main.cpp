#include <iostream>
#include <sstream>
#include <string>
#include "cell.h"
#include "board.h"
#include "errormessage.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "human.h"
#include "gameplayer.h"
using namespace std;

int main(int argc, const char * argv[]) {
    //cin.exceptions(ios::eofbit|ios::failbit);
    Board board;
    string cmd;
    GamePlayer white{Colour::White}, black{Colour::Black};
    GamePlayer *currentPlayer;
    Colour whoseTurn;
    Position pos1, pos2;
    Move move;
    istringstream iss;
    board.init();
    cout << board;
    
//    for (Move *randMove: board.getAllLegalMoves(Colour::White)) {
//        cout << randMove->from.col << randMove->from.row << "|" << randMove->to.col << randMove->to.row << " ";
//    }
//    cout << endl;
    
    try {
        while (true) {
            cin >> cmd;
            if (cmd == "game") {
                string p1, p2;
                cout << board;
                try {
                    cin >> p1 >> p2;
                    white.setPlayer(p1, &board);
                    black.setPlayer(p2, &board);
                    if (!white.isValid() || !black.isValid()) {
                        throw ErrorMessage{"Invalid player name."};
                    }
                } catch (ErrorMessage &e) {
                    cout << e.getErrorMessage() << endl;
                }
                while (true) {
                    cin >> cmd;
                    whoseTurn = board.getWhoseTurn();
                    if (cmd == "move") {
                        if (whoseTurn == white.getColour()) {
                            currentPlayer = &white;
                        } else {
                            currentPlayer = &black;
                        }
                        move = currentPlayer->nextMove();
                        char type = currentPlayer->getPromotion();
                        if (type) {
                            try {
                                move.promotion = true;
                                board.promote(type, move);
                                cout << board;
                            } catch (ErrorMessage &e) {
                                cout << e.getErrorMessage() << endl;
                            }
                        }
                        if (board.isCastlingValid(move)) {
                            move.castling = true;
                            board.castle(move);
                            cout << board;
                        } else {
                            try {
                                board.move(move);
                                cout << board;
                            } catch (ErrorMessage &e) {
                                cout << e.getErrorMessage() << endl;
                            }
                        }
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
                    } else if (cmd == "resign") {
                        whoseTurn = board.getWhoseTurn();
                        if (white.win(whoseTurn)) cout << "White wins!";
                        if (black.win(whoseTurn)) cout << "Black wins!";
                        board.init();
                        break;
                    }
                } // end of while loop inside game
            } else if (cmd == "setup") {
                cin >> cmd;
                while (true) {
                    Position pos;
                    string s;
                    istringstream iss;
                    if (cmd == "+") {
                        char name;
                        cin >> name;
                        cin >> s;
                        pos.col = s.front();
                        s = s.back();
                        iss.str(s);
                        iss >> pos.row;
                        try {
                            board.setPiece(name, pos);
                            cout << board;
                        } catch (ErrorMessage &e) {
                            cout << e.getErrorMessage() << endl;
                        }
                    } else if (cmd == "-") {
                        cin >> s;
                        pos.col = s.front();
                        s = s.back();
                        iss.str(s);
                        iss >> pos.row;
                        try {
                            bool havePiece = board.removePiece(pos);
                            if (havePiece) cout << board;
                        } catch (ErrorMessage &e) {
                            cout << e.getErrorMessage() << endl;
                        }
                    } else if (cmd == "=") {
                        cin >> s;
                        if (s[0] == 'B' || s[0] == 'b') {
                            board.setWhoseTurn(Colour::Black);
                        } else if (s[0] == 'W' || s[0] == 'w') {
                            board.setWhoseTurn(Colour::White);
                        }
                    } else if (cmd == "done") {
                        if (board.isSetupComplete()) break;
                        cout << "Please make sure that: \n1. the board contains exactly one white king and exactly one black king\n2. no pawns are on the first or last row of the board\n3. neither king is in check" << endl;
                    }
                    cin >> cmd;
                }
            } // end of setup
        }
    } catch (ios::failure &e) {}
}
