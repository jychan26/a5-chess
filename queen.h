#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "piece.h"

class Queen: public Piece {
	public:
	Queen(char name, const pieceColour colour, const int force = 70);
	bool isObeyRule(Move) override;
	vector<Move> getLegalMoves(Position) override;
	vector(Position) getInBetweenPositions() override;
}

#endif
