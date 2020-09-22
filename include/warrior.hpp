/*
  warrior.hpp
  Purpose: Represent a warrior. A warrior is any of the characters in the game. This class is abstract, and should therefore never be instantiated. Instead instantiate a subclass-- Player or Enemy.
  @author Jeremy Elkayam
 */

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "color_grid.hpp"
using std::cout;
using std::endl;

class Warrior
{
protected:
  /*
   * angle: angle of the warrior's velocity in radians
   */
  float angle;

  sf::Sprite sprite;

  sf::Color color;

  /*
    Constructor for the Warrior class. Sets initial values.

    @param xcor initial x-coordinate of the warrior.
    @param ycor initial y-coordinate of the warrior.
   */
  Warrior(float xcor, float ycor, sf::Texture &texture);
public:
  
  /*
    Returns the x-coordinate of the warrior.

    @return the warrior's x-coordinate
  */
  float get_xcor(){return sprite.getPosition().x;}

  
  /*
    Returns the y-coordinate of the warrior.

    @return the warrior's y-coordinate
  */
  float get_ycor(){return sprite.getPosition().y;}

  float get_angle(){return angle;}

  /*
     Sets the coordinates of the warrior to what they would be after the
          specified time had elapsed, based on the velocity of the warrior.
          @param micros_elapsed The time elapsed in microseconds.
  */
  virtual void move(int micros_elapsed) = 0;


  void set_angle(float angle){this->angle = angle;}

  void draw(sf::RenderWindow &window, ColorGrid &color_grid);

};
