/*
  logic.cpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#include "logic.hpp"

Logic::Logic(){
  player = std::make_shared<Player>(0,0);
}

void Logic::update(int micros_elapsed){
  return;
}
