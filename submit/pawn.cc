#include "pawn.h"
#include "move.h"
#include "position.h"

using namespace std;

Pawn::Pawn(char name, const Colour pieceColour, const int force) :
	Piece{name, pieceColour, force} {}

int Pawn::getNofMove() const {
	return nofMove;
}

void Pawn::setNofMove(int n) {
	nofMove = n;
}

bool Pawn::isObeyRule(Move &m) const {
	// assumes:
	// Move consists of valid initial and final positions
	// initial and final positions are not equal
	Position curr_pos{m.from};
	Position next_pos{m.to};

	// row_diff is based on pieceColour to determine its "forward" motion
	int row_diff = ((getPieceColour() == Colour::White) ? 
			(next_pos.row - curr_pos.row) : (curr_pos.row - next_pos.row));
	int col_diff = (next_pos.col - curr_pos.col);

	// Booleans for regular move
	bool is_forward_motion = ((col_diff == 0) and (row_diff > 0));
	bool is_valid_first_distance = (this->getFirstMove() and (row_diff == 2));
	bool is_valid_reg_distance = row_diff == 1;
	bool is_valid_reg_move = (is_forward_motion and 
				 (is_valid_first_distance or is_valid_reg_distance));
	
	// Booleans for capturing pieces
	bool is_valid_capture_move = ((row_diff == 1) and (abs(col_diff) == 1));

	return (is_valid_reg_move or is_valid_capture_move);
}

vector<Move> Pawn::getLegalMoves(Position pos) const {
	vector<Move> moves;
    Position dest = pos;
    int forward = 1;
    if (getPieceColour() == Colour::Black) forward *= -1;

    dest.row += forward;
    if (getFirstMove()) {
        dest.row += forward;
         if (dest.isValid()) moves.push_back(Move(pos, dest));
        dest.row -= forward;
    }
    if (dest.isValid()) moves.push_back(Move(pos, dest));
    dest.col += 1;
    if (dest.isValid()) moves.push_back(Move(pos, dest));
    dest.col -= 2;
    if (dest.isValid()) moves.push_back(Move(pos, dest));
	return moves;
}

vector<Position> Pawn::getInBetweenPositions(Move &m) const {
	vector<Position> positions;
	Position curr_pos{m.from};
	Position next_pos{m.to};

	// assumes that Pawn::isObeyRule returns True already 
	int row_diff = abs(next_pos.row - curr_pos.row);
	if (this->getFirstMove() and (row_diff == 2)) {
		if (getPieceColour() == Colour::White) {
			Position mid_pos{curr_pos.row + 1, curr_pos.col};
			positions.emplace_back(mid_pos);
		} else {
			Position mid_pos{curr_pos.row - 1, curr_pos.col};
			positions.emplace_back(mid_pos);
		}
	}
	return positions;
}
