/*
 * enemy.hpp
 * Purpose: an enemy warrior
 *
 */

#pragma once
#include "entity.hpp"

class Enemy : public Entity {
private:

  float angle;

public:
  Enemy(float xcor,float ycor, sf::Texture &texture);

  void point_at_player(float player_x,float player_y);

  void move(float s_elapsed,float speed);
};