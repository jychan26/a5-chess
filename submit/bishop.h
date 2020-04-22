#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "piece.h"

class Bishop: public Piece {
	public:
	Bishop(char name, const Colour pieceColour, const int force = 30);

	bool isObeyRule(Move &) const override;
	std::vector<Move> getLegalMoves(Position) const override;
	std::vector<Position> getInBetweenPositions(Move &) const override;
};

#endif
