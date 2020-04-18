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

bool Pawn::isObeyRule(Move &m) const {
	Position curr_pos{m.from};
	Position next_pos{m.to};

	int row_diff{next_pos.row - curr_pos.row};
	int col_diff{next_pos.col - curr_pos.col};

	// assumes:
	// Move consists of valid initial and final positions
	// initial and final positions are not equal
	return ((col_diff == 0) and // vertical
			(this->getFirstMove() and (row_diff <= 2)) or
			(not(this->getFirstMove()) and (row_diff == 1))
		);
}

vector<Move*> Pawn::getLegalMoves(Position pos) const {
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
