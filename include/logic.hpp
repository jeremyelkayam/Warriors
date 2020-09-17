/*
  logic.hpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#pragma once
#include <memory>
#include "player.hpp"

class Logic
{
private:
  std::shared_ptr<Player>player;
public:
  /*
    Constructor for the Logic class.
    Sets up the initial values for Logic.
   */
  Logic();

  std::shared_ptr<Player> getPlayer(){return player;}

  void update(int micros_elapsed);

};
