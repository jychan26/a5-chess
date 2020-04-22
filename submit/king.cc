#include "king.h"
#include "move.h"
#include "position.h"

using namespace std;

King::King(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool King::isObeyRule(Move &m) const {
	Position curr_pos = m.from;
	Position next_pos = m.to;

	// movement check - if Move consists of one square in any direction
	// assumes that initial and final positions are not equivalent
	return ((abs(curr_pos.col - next_pos.col) <= 1) and (abs(curr_pos.row - next_pos.row) <= 1));
}

vector<Move> King::getLegalMoves(Position pos) const {
    vector<Move> moves;
    Position dest;
    for (int i = -1; i < 2; i += 1) {
        for (int j = -1; j < 2; j += 1) {
                dest = pos;
                dest.col += i;
                dest.row += j;
                if (dest.isValid() && dest != pos) moves.push_back(Move(pos, dest));
        }
    }
    return moves;
}
