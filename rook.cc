#include "rook.h"
#include "move.h"
#include "position.h"

using namespace std;

Rook::Rook(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Rook::isObeyRule(Move &m) const { //TODO
	return true;
}

vector<Move> Rook::getLegalMoves(Position &pos) const { //TODO
	vector<Move> moves;
	return moves;
}

vector<Position> Rook::getInBetweenPositions(Move &m) const { //TODO
	vector<Position> positions;
	return positions;
}
