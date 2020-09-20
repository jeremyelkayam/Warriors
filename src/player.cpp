/*
  player.cpp
  Purpose: Represent the player's character.
  Potential Improvement: add more than one player.
*/

#include "player.hpp"

void Player::set_moving(bool moving){
  if(moving) current_speed=max_speed; else current_speed=0;
};