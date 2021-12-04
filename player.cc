#include "player.h"
#include "game.h"
#include <memory>
#include <utility>
#include <vector>

using namespace std;

Player::Player(char color) : color{color} {}

char Player::getColor() { return color; }

/*
void Player::movePiece(vector<pair<int, int>> start, vector<pair<int, int>> end) {
  return;    
}
*/

Player::~Player() {}
