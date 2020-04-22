#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"

class Pawn: public Piece {
	int nofMove = 0;

	public:
	Pawn(char name, const Colour pieceColour, const int force = 10);
	int getNofMove() const;
	void setNofMove(int);

	bool isObeyRule(Move &) const override;
	std::vector<Move> getLegalMoves(Position) const override;
	std::vector<Position> getInBetweenPositions(Move &) const override;
};

#endif
