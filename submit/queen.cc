#include "queen.h"
#include "move.h"
#include "position.h"

using namespace std;

Queen::Queen(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

bool Queen::isObeyRule(Move &m) const {
	Position curr_pos{m.from};
	Position next_pos{m.to};

	int col_diff_abs{abs(curr_pos.col - next_pos.col)};
	int row_diff_abs{abs(curr_pos.row - next_pos.row)};

	// movement check (if direction from Move is valid regardless of being blocked)
	// assumes that initial and final positions are not equivalent
	return ((col_diff_abs == 0) or 
		(row_diff_abs == 0) or 
		(col_diff_abs == row_diff_abs));
}

vector<Move> Queen::getLegalMoves(Position pos) const {
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

vector<Position> Queen::getInBetweenPositions(Move &m) const {
	vector<Position> positions;
	Position curr_pos{m.from};
	Position next_pos{m.to};

	int min_row{min(curr_pos.row, next_pos.row)};
	int max_row{max(curr_pos.row, next_pos.row)};
	char min_col{min(curr_pos.col, next_pos.col)};
	char max_col{max(curr_pos.col, next_pos.col)};

	int mid_row;
	char mid_col;

	// assumption: Queen's Move passes its direction and distance check
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
	
	} else if (next_pos.row > curr_pos.row) { // diagonal: top right or bottom right
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
	} else { // diagonal: top left or bottom left
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









