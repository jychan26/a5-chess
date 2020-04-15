#include "cell.h"


std::vector<Move*> Cell::getLegalMoves() {
    return piece->getLegalMoves(pos);
}
