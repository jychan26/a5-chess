#include "pawn.h"
#include "move.h"
#include "position.h"

using namespace std;

Pawn::Pawn(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

int Pawn::getNofMove() const {
	return nofMove;
}

void Pawn::setNofMove(int n) {
	nofMove = n;
}

bool Pawn::isObeyRule(Move m) const { //TODO
	return true;
}

vector<Move> Pawn::getLegalMoves(Position pos) const { //TODO
	vector<Move> moves;
	return moves;
}
