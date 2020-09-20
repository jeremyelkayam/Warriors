/*
  warrior.cpp
  Purpose: Represent a warrior. A warrior is any of the characters in the game. This class is abstract, and should therefore never be instantiated. Instead instantiate a subclass-- Player or Enemy.
  @author Jeremy Elkayam
 */

#include "warrior.hpp"

void Warrior::move(int micros_elapsed){
  this->xcor+=(current_speed*cos(angle)*micros_elapsed);
  this->ycor+=(current_speed*sin(angle)*micros_elapsed);

}