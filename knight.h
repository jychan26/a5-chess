#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "piece.h"

class Knight: public Piece {
	public:
	Knight(char name, const Colour pieceColour, const int force = 30);

	bool isObeyRule(Move &) const override;
	std::vector<Move> getLegalMoves(Position) const override;
};

#endif
