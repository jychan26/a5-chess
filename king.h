#ifndef _KING_H_
#define _KING_H_
#include "piece.h"

class King: public Piece {
	bool firstMove;
	const int force;
	
	public:
	bool isObeyRule(Move) override;
	vector<Move> getLegalMoves(Position) override;
}

#endif
