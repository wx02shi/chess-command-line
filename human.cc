#include "human.h"

#include <utility>
using namespace std;

Human::Human(char color): Player{color, 'h'} {}

/**
 * This function isn't actually used. 
 * We wrote an implementation to override the pure virtual function
 */
pair<pair<int, int>, pair<int, int>> Human::autoMove(Board &board, Game &game) {
  auto result = make_pair(make_pair(0,0), make_pair(0,0));
  return result;
}

Human::~Human() {}
