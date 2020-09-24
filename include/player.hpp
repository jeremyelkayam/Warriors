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
  float speed,speed_scale_x,speed_scale_y, field_width, field_height;

  void move(float s_elapsed);

public:
  Player(float xcor,float ycor,float speed, sf::Texture &texture, float field_width, float field_height);


  void update(float s_elapsed);

  void set_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right);

};
