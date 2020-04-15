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

bool Pawn::isObeyRule(Move &m) const { //TODO
	return true;
}

vector<Move*> Pawn::getLegalMoves(Position pos) const { //TODO
	vector<Move*> moves;
    Position dest = pos;
    int forward = 1;
    if (getPieceColour() == Colour::Black) forward *= -1;

    dest.row += forward;
    if (dest.isValid()) moves.push_back(new Move(pos, dest));
    dest.col += 1;
    if (dest.isValid()) moves.push_back(new Move(pos, dest));
    dest.col -= 2;
    if (dest.isValid()) moves.push_back(new Move(pos, dest));
	return moves;
}
