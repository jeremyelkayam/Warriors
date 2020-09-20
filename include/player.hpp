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
  Player(float xcor,float ycor)
    : Warrior(xcor,ycor){};


  void set_moving(bool moving);
};
