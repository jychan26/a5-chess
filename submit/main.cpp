#include <iostream>
#include <sstream>
#include <string>
#include "cell.h"
#include "move.h"
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
    cin.exceptions(ios::eofbit|ios::failbit);
    Board board;
    string cmd;
    GamePlayer white{Colour::White}, black{Colour::Black};
    GamePlayer *currentPlayer;
    Colour whoseTurn, oppoColour;
    Position pos1, pos2;
    Move move;
    istringstream iss;
    board.init();
    cout << board;
    
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
                    board.displayErrorMessage(e);
                    continue;
                }
                board.clearErrorMessage();
                while (true) {
                    cin >> cmd;
                    whoseTurn = board.getWhoseTurn();
                    oppoColour = Colour::White;
                    if (whoseTurn == oppoColour) oppoColour = Colour::Black;
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
                                board.displayErrorMessage(e);
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
                                board.displayErrorMessage(e);
                            }
                        }
                        try {
                            if (board.isCheckmate(whoseTurn)) {
                                string s{"Checkmate! "};
                                if (white.win(whoseTurn)) board.displayMessage(s + "White wins!\n");
                                if (black.win(whoseTurn)) board.displayMessage(s + "Black wins!\n");
                                board.displayMessage(s);
                                board.init();
                                break;
                            } else if (board.isStalemate()) {
                                white.stalemate();
                                black.stalemate();
                                board.displayMessage( "Stalemate! \n");
                                board.init();
                                break;
                            } else if (board.isChecked(oppoColour)) {
                                if (oppoColour == Colour::White) board.displayMessage("White is in check.\n");
                                if (oppoColour == Colour::Black) board.displayMessage("Black is in check.\n");
                            }
                        } catch (ErrorMessage &e) {
                            board.displayErrorMessage(e);
                        }
                    } else if (cmd == "resign") {
                        whoseTurn = board.getWhoseTurn();
                        if (white.win(whoseTurn)) board.displayMessage("White wins!\n");
                        if (black.win(whoseTurn)) board.displayMessage("Black wins!\n");
                        board.init();
                        break;
                    } else if (cmd == "undo") {
                        if (board.undoMove()) {
                            cout << board;
                            if (board.getWhoseTurn() == Colour::Black) { board.setWhoseTurn(Colour::White);
                            } else if (board.getWhoseTurn() == Colour::White) board.setWhoseTurn(Colour::Black);
                        }
                    }
                } // end of while loop inside game
                ostringstream ss;
                ss << "Current score:" << endl;
                ss << "White: " << white.getScore() << endl;
                ss << "Black: " << black.getScore() << endl;
                board.displayMessage(ss.str());
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
                            board.displayErrorMessage(e);
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
                        board.displayMessage("Please make sure that: \n1. the board contains exactly one white king and exactly one black king\n2. no pawns are on the first or last row of the board\n3. neither king is in check");
                    }
                    cin >> cmd;
                }
            } // end of setup
        }
    } catch (ios::failure &e) {
        ostringstream ss;
        ss << "Final score:" << endl;
        ss << "White: " << white.getScore() << endl;
        ss << "Black: " << black.getScore() << endl;
        board.displayMessage(ss.str());
    }
    
}
