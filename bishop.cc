#include "bishop.h"
#include "move.h"
#include "position.h"

using namespace std;

Bishop::Bishop(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Bishop::isObeyRule(Move &m) const { //TODO
	return true;
}

vector<Move*> Bishop::getLegalMoves(Position pos) const { //TODO
	vector<Move*> moves;
    for (Position p = pos; p.isValid(); p.col += 1, p.row += 1) {
        if (!(p == pos)) moves.push_back(new Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.col += 1, p.row -= 1) {
        if (!(p == pos)) moves.push_back(new Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.col -= 1, p.row += 1) {
        if (!(p == pos)) moves.push_back(new Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.col -= 1, p.row -= 1) {
        if (!(p == pos)) moves.push_back(new Move(pos, p));
    }
	return moves;
}

vector<Position> Bishop::getInBetweenPositions(Move &m) const { //TODO
	vector<Position> positions;
	return positions;
}
