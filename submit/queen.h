#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "piece.h"

class Queen: public Piece {
	public:
	Queen(char name, const Colour pieceColour, const int force = 70);

	bool isObeyRule(Move &) const override;
	std::vector<Move> getLegalMoves(Position) const override;
	std::vector<Position> getInBetweenPositions(Move &) const override;
};

#endif
