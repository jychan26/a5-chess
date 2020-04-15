#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "colour.h"
#include "position.h"
#include "move.h"
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class Board {
    std::vector<std::vector<Cell>> grid;
    const int size = 8;
    TextDisplay *td = nullptr;
    GraphicsDisplay *gd = nullptr;
    std::vector<Move> history;
    std::vector<Cell *> piecesOnBoard;
    std::vector<Cell *> kings;
    Colour whoseTurn;
public:
    ~Board();
    void init();
    void setPiece(char name, Position pos);
    void removePiece(Position pos);
    void move(Move m);
    bool isObeyRule(Move &m);
    std::vector<Position> getInBetweenPositions(Move &m);
    bool isBlocked(std::vector<Position>);
    bool isChecked(Colour kingColour);
    void promote(char name, Move m);
    bool isCastlingValid(Move m);
    void castle(Move m);
    std::vector<Move> getLegalMoves(Position &pos);
    bool isCheckmate(Colour colour);
    bool isStalemate(Colour colour);
    Colour getWhoseTurn();
    bool isSetupComplete();
    Info getInfo(Position pos);
    std::vector<Info> getPieces();
    std::vector<Position> threatenedBy(Position pos);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};


#endif

