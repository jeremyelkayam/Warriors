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
  Enemy(float xcor,float ycor,float speed, sf::Texture &texture)
          : Warrior(xcor,ycor,speed,texture){color = sf::Color::Red;}

  void point_at_player(float player_x,float player_y);
};