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

using std::cout;
using std::endl;
using std::list;
using std::shared_ptr;
using std::mt19937;

class Logic
{
private:
  Player player;
  list<Enemy> enemies;

  float time_since_last_spawn;

  float spawn_interval;

  sf::Texture &m_warrior_tex;

  void spawn_enemy();

  void update_enemies(float s_elapsed);

  mt19937 &randy;



public:
  /*
    Constructor for the Logic class.
    Sets up the initial values for Logic.
   */
  Logic(sf::Texture &warrior_tex, mt19937 &rand);

  void update(float s_elapsed);

  void set_player_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right){
    player.set_movement(moving_up,moving_down,moving_left,moving_right);}

  void draw_components(sf::RenderWindow &window,ColorGrid &color_grid);



};
