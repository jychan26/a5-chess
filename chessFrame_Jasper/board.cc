#include "board.h"


std::vector<Move*> Board::getLegalMoves(Position &pos) {
    std::vector<Move*> moves = grid[pos.col - 'a'][pos.row - 1].getLegalMoves();
    for (vector<Move*>::iterator it= moves.begin(); it < moves.end(); ++it) {
        // if (isBlocked(getInBetweenPositions(**it))) moves.erase(it);
    }
    return moves;
}
