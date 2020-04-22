#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "colour.h"
#include "position.h"
#include "move.h"
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "errormessage.h"

class Board {
    std::vector<std::vector<Cell>> grid;
    const int size = 8;
    TextDisplay *td = nullptr;
    GraphicsDisplay *gd = nullptr;
    std::vector<Move> history;
    std::map<std::string, Info> piecesOnBoard;
    std::map<std::string, Info> kings;
    Colour whoseTurn;
public:
    ~Board();
    void init();
    bool isValidPos(Position pos);
    bool isValidName(char name);
    void addToMap(char name, Position pos);
    void eraseFromMap(Position pos);
    void setPiece(char name, Position pos);
    bool removePiece(Position pos);
    void move(Move m);
    bool isObeyRule(Move m);
    std::vector<Position> getInBetweenPositions(Move m);
    bool isBlocked(std::vector<Position>);
    bool isChecked(Colour kingColour);
    void promote(char name, Move m);
    bool isCastlingValid(Move m);
    void castle(Move m);
    std::vector<Move> getLegalMoves(Position &pos, Colour myColour);
    std::vector<Move> getAllLegalMoves(Colour myColour);
    std::vector<Move> getPossibleMoves(Position &pos);
    std::vector<Move> getAllPossibleMoves(Colour myColour);
    bool isCheckmate(Colour colour);
    bool isStalemate();
    Colour getWhoseTurn();
    bool isSetupComplete();
    Info getInfo(Position pos);
    std::vector<Info> getPieces();
    std::vector<Info> threatenedBy(Position pos, Colour myColour);
    std::vector<Info> protectedBy(Position pos, Colour myColour);
    bool setWhoseTurn(Colour colour);
    bool isOpponentPawn(char name);
    bool isOneSquareDiagonal(Move m);
    bool isPawnMoveTwoSquares(Move m);
    bool isPawnForwardStraight(Move m);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
    bool undoMove();
    void moveNoCapture(Move m);
    void displayErrorMessage(ErrorMessage &e);
    void clearErrorMessage();
    void displayMessage(std::string s);
};


#endif

