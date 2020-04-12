#include "king.h"
#include "move.h"
#include "position.h"

using namespace std;

King::King(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool King::isObeyRule(Move &m) const { // TODO
	/*
	Position curr_pos = m.from;
	Position next_pos = m.to;

	// movement check - if Move consists of one square in any direction
	return ((abs(curr_pos.col - next_pos.col) <= 1) and (abs(curr_pos.row - next_pos.row) <= 1));*/
	return true;
}

vector<Move> King::getLegalMoves(Position &pos) const { // TODO
	vector<Move> moves;
	return moves;
}
