#include "bishop.h"
#include "move.h"
#include "position.h"

using namespace std;

Bishop::Bishop(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Bishop::isObeyRule(Move &m) const {
	Position curr_pos{m.from};
	Position next_pos{m.to};

	// assumes:
	// (1) Move consists of valid initial and final positions
	// (2) initial and final positions are not equivalent
	// checks if Move is diagonal for any distance
	return (abs(curr_pos.col - next_pos.col) == abs(curr_pos.row - next_pos.row)); 
}

vector<Move> Bishop::getLegalMoves(Position pos) const {
	vector<Move> moves;
    for (Position p = pos; p.isValid(); p.col += 1, p.row += 1) {
        if (!(p == pos)) moves.push_back(Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.col += 1, p.row -= 1) {
        if (!(p == pos)) moves.push_back(Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.col -= 1, p.row += 1) {
        if (!(p == pos)) moves.push_back(Move(pos, p));
    }
    for (Position p = pos; p.isValid(); p.col -= 1, p.row -= 1) {
        if (!(p == pos)) moves.push_back(Move(pos, p));
    }
	return moves;
}

vector<Position> Bishop::getInBetweenPositions(Move &m) const {
	// initialize variables
	vector<Position> positions;
	Position curr_pos{m.from};
	Position next_pos{m.to};

	int min_row{min(curr_pos.row, next_pos.row)};
	int max_row{max(curr_pos.row, next_pos.row)};
	char min_col{min(curr_pos.col, next_pos.col)};
	char max_col{max(curr_pos.col, next_pos.col)};

	int mid_row;
	char mid_col;

	if (next_pos.row > curr_pos.row) {
		if (next_pos.col > curr_pos.col) { // top right
			for (mid_row = min_row + 1, mid_col = min_col + 1;
					mid_row < max_row; ++mid_row, ++mid_col) {
				Position mid_pos{mid_row, mid_col};
				positions.emplace_back(mid_pos);
			}
		} else { // bottom right
			for (mid_row = min_row + 1, mid_col = max_col - 1;
					mid_row < max_row; ++mid_row, --mid_col) {
				Position mid_pos{mid_row, mid_col};
				positions.emplace_back(mid_pos);
			}
		}
	} else { 
		if (next_pos.col > curr_pos.col) { // top left
			for (mid_row = min_row + 1, mid_col = max_col - 1;
					mid_row < max_row; ++mid_row, --mid_col) {
				Position mid_pos{mid_row, mid_col};
				positions.emplace_back(mid_pos);
			}
		} else { // bottom left
			for (mid_row = min_row + 1, mid_col = min_col + 1;
					mid_row < max_row; ++mid_row, ++mid_col) {
				Position mid_pos{mid_row, mid_col};
				positions.emplace_back(mid_pos);
			}
		}
	}
	return positions;
}
