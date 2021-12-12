#include "human.h"

#include <utility>
using namespace std;

Human::Human(char color): Player{color, 'h'} {}

pair<pair<int, int>, pair<int, int>> Human::autoMove(Board &board, Game &game) {
  auto result = make_pair(make_pair(0,0), make_pair(0,0));
  return result;
}

Human::~Human() {}
