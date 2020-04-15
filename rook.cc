#include "rook.h"
#include "move.h"
#include "position.h"

using namespace std;

Rook::Rook(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Rook::isObeyRule(Move &m) const { //TODO
	return true;
}

vector<Move*> Rook::getLegalMoves(Position pos) const { //TODO
	vector<Move*> moves;
    for (Position p = pos; p.isValid(); p.col += 1) {
        if (!(p == pos)) moves.push_back(new Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.col -= 1) {
        if (!(p == pos)) moves.push_back(new Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.row -= 1) {
        if (!(p == pos)) moves.push_back(new Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.row += 1) {
        if (!(p == pos)) moves.push_back(new Move(pos, p));
    }
	return moves;
}

vector<Position> Rook::getInBetweenPositions(Move &m) const { //TODO
	vector<Position> positions;
	return positions;
}
