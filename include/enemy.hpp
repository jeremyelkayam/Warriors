/*
 * enemy.hpp
 * Purpose: an enemy warrior
 *
 */

#pragma once
#include "entity.hpp"
#include "warrior.hpp"

class Enemy : public Warrior {
private:

  float angle;

  void point_at_player(float player_x,float player_y);

  void move(float s_elapsed,float speed);

public:
  Enemy(float xcor,float ycor, sf::Texture &texture, sf::Texture &sword_tex);

  void update(float s_elapsed, float speed, float player_x, float player_y);

};