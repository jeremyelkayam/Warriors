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
#include "player.hpp"
#include "enemy.hpp"

using std::cout;
using std::endl;
using std::list;
using std::shared_ptr;

class Logic
{
private:
  Player player;
  list<Enemy> enemies;

  int time_since_last_spawn;

  int spawn_interval;

  sf::Texture &m_warrior_tex;

  void spawn_enemy();

  void update_enemies(int micros_elapsed);

public:
  /*
    Constructor for the Logic class.
    Sets up the initial values for Logic.
   */
  Logic(sf::Texture &warrior_tex);

  void update(int micros_elapsed);

  void set_player_moving(Player::Direction direction, bool moving){player.set_moving(direction,moving);}

  void draw_components(sf::RenderWindow &window,ColorGrid &color_grid);



};
