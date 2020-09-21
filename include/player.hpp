/*
  player.hpp
  Purpose: Represent the player's character. 
  Potential Improvement: add more than one player.
*/

#pragma once
#include "warrior.hpp"
#include <iostream>

using std::cout;
using std::endl;

class Player : public Warrior {
private:
  bool moving_left,moving_right,moving_up,moving_down=false;

public:
  Player(float xcor,float ycor,float speed, sf::Texture &texture)
    : Warrior(xcor,ycor,speed,texture){color = sf::Color::Cyan;}

  enum class Direction { Left, Right, Up, Down};

  void set_moving(Direction direction, bool moving);

  void move(int micros_elapsed);

};
