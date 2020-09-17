/*
  player.hpp
  Purpose: Represent the player's character. 
  Potential Improvement: add more than one player.
*/

#pragma once
#include "warrior.hpp"
class Player : public Warrior {
private:
  
public:
  Player(double xcor,double ycor)
    : Warrior(xcor,ycor){};
};
