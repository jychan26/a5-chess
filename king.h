#ifndef _KING_H_
#define _KING_H_
#include "piece.h"

class King: public Piece {
	bool firstMove;
	
	public:
	King(char name, const Colour pieceColour, const int force = 900, bool firstMove = true);
	bool isObeyRule(Move) override;
	vector<Move> getLegalMoves(Position) override;
}

#endif
