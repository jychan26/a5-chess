#ifndef _PIECE_H_
#define _PIECE_H_
#include "colour.h"
#include "vector.h"

// forward declaration
class Move;
class Position;

class Piece { // abstract class
	char name;
	Colour pieceColour;
	int force;

	public:
		char getPiece(); // get name field
		Colour getPieceColour(); // get pieceColour fielid
		int getForce(); // get force field

		virtual bool isObeyRule(Move) = 0; // does Move agree with Piece's movement (in terms of direction and distance)?
		virtual vector<Position> getInBetweenPositions(Move); // get positions between Move that Piece could otherwise have validly landed on
		virtual vector<Move> getLegalMoves(Position) = 0;
};

#endif
