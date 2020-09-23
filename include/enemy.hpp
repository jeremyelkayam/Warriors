/*
 * enemy.hpp
 * Purpose: an enemy warrior
 *
 */

#pragma once
#include "warrior.hpp"

class Enemy : public Warrior {
private:

  //this is kinda dumb and bad but fuck it
  static float speed;

public:
  Enemy(float xcor,float ycor, sf::Texture &texture);
  ~Enemy();

  void point_at_player(float player_x,float player_y);

  void move(float s_elapsed);
};