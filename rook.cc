#include "rook.h"

#include "move.h"
#include "position.h"

using namespace std;

Rook::Rook(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Rook::isObeyRule(Move &m) const {
	Position curr_pos{m.from};
	Position next_pos{m.to};

	// assumes:
	// (1) Move consists of valid positions
	// (2) initial and final positions are not equivalent
	// checks if Move is horizontal/vertical for any distance
	return ((curr_pos.col == next_pos.col) or (curr_pos.row == next_pos.row));
}

vector<Move> Rook::getLegalMoves(Position pos) const {
	vector<Move> moves;
    for (Position p = pos; p.isValid(); p.col += 1) {
        if (!(p == pos)) moves.push_back(Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.col -= 1) {
        if (!(p == pos)) moves.push_back(Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.row -= 1) {
        if (!(p == pos)) moves.push_back(Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.row += 1) {
        if (!(p == pos)) moves.push_back(Move(pos, p));
    }
	return moves;
}

vector<Position> Rook::getInBetweenPositions(Move &m) const {
	vector<Position> positions;
	Position curr_pos{m.from};
	Position next_pos{m.to};

	int min_row{min(curr_pos.row, next_pos.row)};
	int max_row{max(curr_pos.row, next_pos.row)};
	char min_col{min(curr_pos.col, next_pos.col)};
	char max_col{max(curr_pos.col, next_pos.col)};

	int mid_row;
	char mid_col;

	if (curr_pos.col == next_pos.col) { // vertical
		for (mid_row = min_row + 1, mid_col = curr_pos.col; 
				mid_row < max_row; ++mid_row) {
			Position mid_pos{mid_row, mid_col};
			positions.emplace_back(mid_pos);
		}
	} else if (curr_pos.row == next_pos.row) { // horizontal
		for (mid_row = curr_pos.row, mid_col = min_col + 1;
				mid_col < max_col; ++mid_col) {
			Position mid_pos{mid_row, mid_col};
			positions.emplace_back(mid_pos);
		}
	}	
	return positions;
}
