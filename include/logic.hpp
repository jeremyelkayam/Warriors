/*
  logic.hpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. collison detection, movement, etc).
  @author Jeremy Elkayam
 */

#pragma once
#include <memory>
#include <iostream>
#include <list>
#include <random>
#include "player.hpp"
#include "enemy.hpp"
#include "potion.hpp"

using std::cout;
using std::endl;
using std::list;
using std::shared_ptr;
using std::mt19937;
using std::uniform_real_distribution;

class Logic
{
private:
  Player player;
  list<Enemy> enemies;

  //A list of the potions.
  //Currently we only have one potion on the game board at a time.
  //But if I add multiplayer or something, it might be nice to put out a few potions at once.
  list<Potion> potions;

  float time_since_last_enemy_spawn;

  float time_since_last_potion_spawn;

  float total_time_elapsed;

  sf::Texture &m_warrior_tex;

  /*
   * Generate a random location that is within the confines of the game board and is
   * also at least threshold units away from the player.
   *
   * @param threshold the minimum number of units away that the coordinates can be generated.
   */
  sf::Vector2f random_distant_location(float threshold);

  float spawn_interval(float min, float max, float time_limit, bool countingUp);

  bool can_spawn_enemy();

  void spawn_enemy();

/*
 * Update every enemy stored in the class, including movement, hit detection, and
 * steering.
 *
 * @param s_elapsed The time in seconds elapsed since the last loop.
 */
  void update_enemies(float s_elapsed);

  bool can_spawn_potion();

  void spawn_potion();
/*
 * Update every potion stored in the class, including despawning if necessary.
 *
 * @param s_elapsed The time in seconds elapsed since the last loop.
 */
  void update_potions(float s_elapsed);

  mt19937 &randy;

  float field_width,field_height;

  uniform_real_distribution<float>width_dist,height_dist;

  TextLoader &text_loader;

public:
  /*
    Constructor for the Logic class.
    Sets up the initial values for Logic.
   */
  Logic(sf::Texture &warrior_tex, mt19937 &rand, float field_width, float field_height, int default_health,
          TextLoader &a_text_loader);

  void update(float s_elapsed);

  void set_player_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right){
    player.set_movement(moving_up,moving_down,moving_left,moving_right);}

  void draw_components(sf::RenderWindow &window,ColorGrid &color_grid);


};
