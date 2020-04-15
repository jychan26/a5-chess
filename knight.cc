#include "knight.h"
#include "move.h"
#include "position.h"

using namespace std;

Knight::Knight(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Knight::isObeyRule(Move &m) const { // TODO
	return true;
}

vector<Move*> Knight::getLegalMoves(Position pos) const { //TODO
	vector<Move*> moves;
    Position dest;
    for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
            for (int x = 1, y = 2; x <= 2; x++) {
                dest = pos;
                y = 3 - x;
                dest.col += x * i;
                dest.row += y * j;
                if (dest.isValid()) moves.push_back(new Move(pos, dest));
            }
        }
    }
	return moves;
}
