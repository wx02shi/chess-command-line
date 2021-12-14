#include "empty.h"

#include <memory>
#include <utility>
#include <vector>

using namespace std;

Empty::Empty(): Piece{0} {
    type = 0;
}

vector<pair<int, int>> Empty::getValidMoves(pair<int, int> position, Board &board) {
    vector<pair<int, int>> results;
    return results;
}

int Empty::getValue() { return 0; }

void Empty::accept(PieceVisitor &pv, std::pair<int, int> pos) {
    pv.visit(*this, pos);
}

Empty::~Empty() {}

