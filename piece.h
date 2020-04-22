#ifndef _PIECE_H_
#define _PIECE_H_
#include "colour.h"
#include <vector>

// forward declaration
class Move;
class Position;

class Piece { // abstract class
	char name;
	Colour pieceColour;
	int force;
	bool firstMove = true;
	bool isEnPassantValid = false;

	public:
	Piece(char name, const Colour pieceColour, const int force); // ctor

	char getPiece() const; // get name field
	Colour getPieceColour() const; // get pieceColour field
	int getForce() const; // get force field
	bool getFirstMove() const; // get firstMove field
	void setFirstMove(bool); // set firstMove field
	bool getIsEnPassantValid() const; // get isEnPassantValid field
	void setIsEnPassantValid(bool); // set isEnPassantValid field

	virtual bool isObeyRule(Move &) const = 0; // does Move agree with Piece's movement (in terms of direction and distance)?
	virtual std::vector<Position> getInBetweenPositions(Move &) const; // get positions between Move that Piece could otherwise have validly landed on
	virtual std::vector<Move> getLegalMoves(Position) const = 0;
    void changeColour();
	virtual ~Piece();
};

#endif
