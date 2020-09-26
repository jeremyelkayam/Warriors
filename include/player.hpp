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
  float speed,speed_scale_x,speed_scale_y, field_width, field_height, invis_frames, sword_time;

  const float max_sword_time, max_invis_frames;

  void move(float s_elapsed);

  int health;

public:
  Player(TextLoader &text_loader, sf::Texture &texture, sf::Texture &sword_tex, sf::Color color);

  void update(float s_elapsed);

  void set_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right);

  void heal(int amount){health += amount;}

  void hurt(int amount);

};
