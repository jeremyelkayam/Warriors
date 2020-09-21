/*
  logic.hpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#pragma once
#include <memory>
#include <iostream>
#include "player.hpp"

using std::cout;
using std::endl;

class Logic
{
private:
  Player player;



public:
  /*
    Constructor for the Logic class.
    Sets up the initial values for Logic.
   */
  Logic();

  void update(int micros_elapsed);

  float get_player_x(){return player.get_xcor();}

  float get_player_y(){return player.get_ycor();}

  void set_player_moving(Player::Direction direction, bool moving){player.set_moving(direction,moving);}

};
