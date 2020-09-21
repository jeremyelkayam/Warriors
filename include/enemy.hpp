/*
 * enemy.hpp
 * Purpose: an enemy warrior
 *
 */

#pragma once
#include "warrior.hpp"

class Enemy : public Warrior {
private:

public:
  Enemy(float xcor,float ycor)
          : Warrior(xcor,ycor){};

  void point_at_player(float player_x,float player_y);
};