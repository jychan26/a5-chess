#ifndef _KING_H_
#define _KING_H_
#include "piece.h"

class King: public Piece {
	public:
	King(char name, const Colour pieceColour, const int force = 9000);
	bool isObeyRule(Move &) const override;
	std::vector<Move> getLegalMoves(Position) const override;
};

#endif
