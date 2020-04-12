#include "queen.h"
#include "move.h"
#include "position.h"

using namespace std;

Queen::Queen(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Queen::isObeyRule(Move m) const { //TODO
	Position curr_pos = m.from;
	Position next_pos = m.to;

	// movement check (if direction from Move is valid regardless of being blocked)
	// TODO
	
	return true;
}

vector<Move> Queen::getLegalMoves(Position pos) const { //TODO
	vector<Move> moves;
	return moves;
}

vector<Position> Queen::getInBetweenPositions(Move m) const { //TODO
	vector<Position> positions;
	return positions;
}
