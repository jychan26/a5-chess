#include "board.h"


std::vector<Move*> Board::getLegalMoves(Position &pos) {
    std::vector<Move*> moves = grid[pos.col - 'a'][pos.row - 1].getLegalMoves();
    for (vector<Move*>::iterator it= moves.begin(); it < moves.end(); ++it) {
        // if (isBlocked(getInBetweenPositions(**it))) moves.erase(it);
    }
    return moves;
}

std::vector<Info> Board::getPieces() {return piecesOnBoard;}

std::vector<Info> Board::threatenedBy(Position pos, Colour myColour) {
    std::vector<Info> threatenInfo;
    Colour oppoColour = Colour::White;
    if (myColour == oppoColour) oppoColour = Colour::Black;
    vector<Move *> allLegalMoves = getAllLegalMoves(oppoColour);
    for (Move *move: allLegalMoves) {
        if (move->to == pos) threatenInfo.push_back(grid[pos.col - 'a'][pos.row - 1].getInfo());
    }
    for (Move *move: allLegalMoves) {delete move;}
    return threatenInfo;
}

bool Board::isCheckmate(Colour colour) {
    for (int i = 0; i < kings.size(); i++) {
        // if (kings[i].piece && kings[i].piece->getPieceColour() == colour) return false;
    }
    return true;
}

bool Board::isChecked(Colour kingColour) {
    Colour oppoColour = Colour::White;
    if (kingColour == oppoColour) oppoColour = Colour::Black;
    for (int i = 0; i < kings.size(); i++) {
        if (kings[i].piece && kings[i].piece->getPieceColour() == kingColour) {
            if (threatenedBy(kings[i].pos, kingColour).size()) return true;
        }
    }
    return false;
}

bool Board::setWhoseTurn(Colour colour) {
    whoseTurn = colour;
    return true;
}

std::vector<Move*> Board::getAllLegalMoves(Colour myColour) {
    vector<Move*> allLegalMoves, moves;
    Position pos;
    Piece* piece;
    
    for (Info &pieceInfo: getPieces()) {
        pos = pieceInfo.pos;
        piece = pieceInfo.piece;
        if (piece->getPieceColour() == myColour) {
            moves = getLegalMoves(pos);
            allLegalMoves.insert(allLegalMoves.end(),moves.begin(),moves.end());
        }
    }
    return allLegalMoves;
}
