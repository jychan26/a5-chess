#include "knight.h"
#include "move.h"
#include "position.h"

using namespace std;

Knight::Knight(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Knight::isObeyRule(Move &m) const { // TODO
	return true;
}

vector<Move> Knight::getLegalMoves(Position &pos) const { //TODO
	vector<Move> moves;
	return moves;
}
