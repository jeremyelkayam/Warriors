/*
  player.hpp
  Purpose: Represent the player's character. 
  Potential Improvement: add more than one player.
*/

#pragma once
#include "warrior.hpp"
#include "resource_manager.hpp"
#include <iostream>
#include <stdexcept>
#include <SFML/Audio.hpp>

using std::cout;
using std::endl;
using std::logic_error;

/*
 * struct postmortem_info
 * Contains information on a player's actions during its lifetime. Obtained from a player after death using the
 * postmortem() method.
 *
 * num_kills: the number of enemies this player killed while it was alive.
 * age:       the amount of time in seconds that this player was alive for.
 */
struct postmortem_info {
  unsigned int num_kills;
  float age;
};

class Player : public Warrior {
private:
  float speed,speed_scale_x,speed_scale_y, field_width, field_height, invis_frames, sword_time;

  const float max_sword_time, max_invis_frames;

  const unsigned int player_number;

  unsigned int health;

  void move(float s_elapsed);

  void update_sword(float s_elapsed);

  sf::Sound hurt_sound, heal_sound, slash_sound, sheath_sound;

  postmortem_info info;

public:
  Player(unsigned int &a_player_number, TextLoader &text_loader, ResourceManager &resource_manager, sf::Color color);

  void update(float s_elapsed);

  void set_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right);

  void heal(unsigned int amount);

  void hurt(unsigned int amount);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) const override;

  void set_sword(bool active);

  unsigned int get_health() const {return health;}

  float get_sword_time() const {return sword_time;}

  float get_max_sword_time() const { return max_sword_time; }

  bool is_dead() const { return health <= 0; }

  void add_kills(unsigned int num_kills) {this->info.num_kills += num_kills; }

  unsigned int get_player_number() { return player_number; }

  /*
   * Only callable when the player is dead. Provides information on what the player did during its lifetime.
   *
   * @return a struct postmortem_info populated with information on the player's actions. For more information, see
   *         struct postmortem_info above.
   */
  postmortem_info postmortem();

};
