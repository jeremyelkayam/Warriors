/*
  warrior.hpp
  Purpose: Represent a warrior. A warrior is any of the characters in the game. This class is abstract, and should therefore never be instantiated. Instead instantiate a subclass-- Player or Enemy.
  @author Jeremy Elkayam
 */

#pragma once

class Warrior
{
protected:
  /*
   * xcor: x-coordinate of the warrior
   * ycor: y-coordinate of the warrior
   */
  double xcor,ycor;
  /*
    Constructor for the Warrior class. Sets initial values.

    @param xcor initial x-coordinate of the warrior.
    @param ycor initial y-coordinate of the warrior.
   */
  Warrior(double xcor,double ycor){this->xcor=xcor;this->ycor=ycor;}
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
};
