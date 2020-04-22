#include "knight.h"
#include "move.h"
#include "position.h"

using namespace std;

Knight::Knight(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Knight::isObeyRule(Move &m) const {
	Position curr_pos{m.from};
	Position next_pos{m.to};

	int row_diff_abs{abs(curr_pos.row - next_pos.row)};
	int col_diff_abs{abs(curr_pos.col - next_pos.col)};

	// assumes Move consists of valid intiial and final positions
	return (((row_diff_abs == 2) and (col_diff_abs == 1)) or
		((row_diff_abs == 1) and (col_diff_abs == 2)));
}

vector<Move> Knight::getLegalMoves(Position pos) const {
	vector<Move> moves;
    Position dest;
    for (int i = -1; i < 2; i += 2) {
        for (int j = -1; j < 2; j += 2) {
            for (int x = 1, y = 2; x <= 2; x++) {
                dest = pos;
                y = 3 - x;
                dest.col += x * i;
                dest.row += y * j;
                if (dest.isValid()) moves.push_back(Move(pos, dest));
            }
        }
    }
	return moves;

}
