/*
  player.hpp
  Purpose: Represent the player's character. 
  Potential Improvement: add more than one player.
*/

#pragma once
#include "warrior.hpp"
#include "resource_manager.hpp"
#include <iostream>
#include <SFML/Audio.hpp>

using std::cout;
using std::endl;

class Player : public Warrior {
private:
  float speed,speed_scale_x,speed_scale_y, field_width, field_height, invis_frames, sword_time;

  const float max_sword_time, max_invis_frames;

  unsigned int health;

  void move(float s_elapsed);

  void update_sword(float s_elapsed);

  sf::Sound hurt_sound, heal_sound, slash_sound;

public:
  Player(TextLoader &text_loader, ResourceManager &resource_manager, sf::Color color);

  void update(float s_elapsed);

  void set_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right);

  void heal(int amount);

  void hurt(int amount);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) const override;

  void set_sword(bool active);

  unsigned int get_health() const {return health;}

  float get_sword_time() const {return sword_time;}

  float get_max_sword_time() const { return max_sword_time; }

  bool is_dead() const { return health <= 0; }

};
