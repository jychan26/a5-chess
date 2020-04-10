#include "king.h"

using namespace std;

King::King(char name, const Colour pieceColour, const int force, bool firstMove) :
	Piece{name, pieceColour, force}, firstMove{firstMove} {}

bool King::isObeyRule(Move) {
	Position curr_pos = Move.from;
	Position next_pos = Move.to;

	// movement check - if Move consists of one square in any direction
	return ((abs(curr_pos.col - next_pos.col) <= 1) and (abs(curr_pos.row - next_pos.row) <= 1));
}

vector<Move> King::getLegalMoves(Position) { // TODO
	vector<Move> moves;
	return moves;
}
