#include "player.h"
#include "game.h"
#include <memory>
#include <utility>
#include <vector>

using namespace std;

Player::Player(char color, char type) : color{color}, type{type} {}

char Player::getColor() { return color; }
char Player::getType() {
    return type;
}

/*
void Player::movePiece(vector<pair<int, int>> start, vector<pair<int, int>> end) {
  return;    
}
*/

Player::~Player() {}
