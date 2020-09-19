/*
  warrior.hpp
  Purpose: Represent a warrior. A warrior is any of the characters in the game. This class is abstract, and should therefore never be instantiated. Instead instantiate a subclass-- Player or Enemy.
  @author Jeremy Elkayam
 */

#pragma once

#include <cmath>

class Warrior
{
protected:
  /*
   * xcor: x-coordinate of the warrior
   * ycor: y-coordinate of the warrior
   * angle: angle of the warrior's velocity in radians
   * speed: magnitude of the warrior's velocity in pixels per microsecond
   */
  double xcor,ycor,angle,speed;


  /*
    Constructor for the Warrior class. Sets initial values.

    @param xcor initial x-coordinate of the warrior.
    @param ycor initial y-coordinate of the warrior.
   */
  Warrior(double xcor,double ycor)
  {this->xcor=xcor;this->ycor=ycor;this->angle=M_PI/4;this->speed=0.0001;}
public:
  
  /*
    Returns the x-coordinate of the warrior.

    @return the warrior's x-coordinate
  */
  double get_xcor(){return xcor;}

  
  /*
    Returns the y-coordinate of the warrior.

    @return the warrior's y-coordinate
  */
  double get_ycor(){return ycor;}

  /*
     Sets the coordinates of the warrior to what they would be after the
          specified time had elapsed, based on the velocity of the warrior.
          @param micros_elapsed The time elapsed in microseconds.
  */
  void move(int micros_elapsed);


};
