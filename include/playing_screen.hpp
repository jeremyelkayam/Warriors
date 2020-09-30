/*
  playing_screen.hpp
  Purpose: Handle all the logic of the main gameplay (e.g. collisions,
           enemies, items, etc).

  @author Jeremy Elkayam
 */

#pragma once
#include <memory>
#include <iostream>
#include <list>
#include <random>
#include <chrono>
#include "player.hpp"
#include "enemy.hpp"
#include "potion.hpp"
#include "screen.hpp"
#include "end_screen.hpp"
#include "resource_manager.hpp"

using std::cout;
using std::endl;
using std::list;
using std::shared_ptr;
using std::mt19937;
using std::uniform_real_distribution;

class PlayingScreen : public Screen
{
private:

  Player player;
  list<Enemy> enemies;

  //A list of the potions.
  //Currently we only have one potion on the game board at a time.
  //But if I add multiplayer or something, it might be nice to put out a few potions at once.
  list<Potion> potions;

  const float base_speed;

  float time_since_last_enemy_spawn,time_since_last_potion_spawn,total_time_elapsed;
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

  mt19937 randy;

  float field_width,field_height;

  uniform_real_distribution<float>width_dist,height_dist;

  void draw_gameplay(sf::RenderWindow &window, ColorGrid &color_grid);

  void draw_hud(sf::RenderWindow &window, ColorGrid &color_grid);

  void keyboard_movement();

public:
  /*
    Constructor for the PlayingScreen class.
    Sets up the initial values for PlayingScreen.
   */
  PlayingScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager);

  void update(float s_elapsed) override;

  void set_player_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right){
    player.set_movement(moving_up,moving_down,moving_left,moving_right);}

  void set_player_sword(bool active){player.set_sword(active);}

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

  bool go_to_next() override {return player.get_health() == 0;}

  unique_ptr<Screen> next_screen() override;

};
