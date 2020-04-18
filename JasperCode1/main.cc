#include <iostream>
#include <sstream>
#include <string>
#include "cell.h"
#include "board.h"
#include "errormessage.h"
using namespace std;

int main(int argc, const char * argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    Board board;
    string cmd;
//    GamePlayer white{Colour::White}, black{Colour::Black};
    Colour whoseTurn;
    Position pos1, pos2;
    Move move;
    istringstream iss;
    board.init();
    cout << board;
    try {
        while (true) {
            cin >> cmd;
            if (cmd == "game") {
//                string p1, p2;
//                cout << board;
//                cin >> p1 >> p2;
//                white.setPlayer(p1);
//                black.setPlayer(p2);
                
                while (true) {
                    cin >> cmd;
//                    whoseTurn = board.getWhoseTurn();
                    if (cmd == "move") {
                        string line;
                        getline(cin, line);
                        istringstream iss_line{line};
                        string m1, m2;
                        iss_line >> m1 >> m2;
//                        pos1.col = m1.front();
//                        pos2.col = m2.front();
//                        m1 = m1.back();
//                        m2 = m2.back();
//                        iss.str(m1);
//                        iss >> pos1.row;
//                        iss.clear();
//                        iss.str(m2);
//                        iss >> pos2.row;
//                        iss.clear();
                        pos1.convert(m1);
                        pos2.convert(m2);
                        move.from = pos1;
                        move.to = pos2;
                        move.promotion = false;
                        move.castling = false;
                        char type;
                        if (iss_line >> type) {
                            try {
                                move.promotion = true;
                                board.promote(type, move);
                                cout << board;
                            } catch (ErrorMessage &e) {
                                cout << e.getErrorMessage() << endl;
                            }
                        } else if (board.isCastlingValid(move)) {
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
    } catch (ios::failure &) {}
}
