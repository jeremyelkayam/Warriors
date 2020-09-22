/*
 * enemy.cpp
 * Purpose: an enemy warrior
 *
 */

#include "enemy.hpp"

void Enemy::point_at_player(float player_x, float player_y){
  float delta_x = player_x - get_xcor();
  float delta_y = get_ycor() - player_y;

  angle = atan2(delta_y,delta_x);
}