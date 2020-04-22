#ifndef _ROOK_H_
#define _ROOK_H_
#include "piece.h"

class Rook: public Piece {
	public:
	Rook(char name, const Colour pieceColour, const int force = 50);

	bool isObeyRule(Move &) const override;
	std::vector<Move> getLegalMoves(Position) const override;
	std::vector<Position> getInBetweenPositions(Move &) const override;
};

#endif
