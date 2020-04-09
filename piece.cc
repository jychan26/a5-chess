#include "piece.h"
#include "move.h"
#include "position.h"

using namespace std;

Piece::Piece(char name, Colour pieceColour, int force) :
	name{name}, pieceColour{pieceColour}, force{force} {}

Piece::getPiece() {
	return name;
}

Piece::getPieceColour() {
	return pieceColour;
}

Piece::getForce() {
	return force;
}|

vector<Position> getInBetweenPositions(Move) {
	vector<Position> positions;
	return positions;
}
