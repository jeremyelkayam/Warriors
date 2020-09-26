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

class Entity
{
protected:

  sf::Sprite sprite;

  sf::Color color = sf::Color::White;

  /*
    Constructor for the Entity class. Sets initial values.

    @param xcor initial x-coordinate of the entity.
    @param ycor initial y-coordinate of the entity.
   */
  Entity(float xcor, float ycor, sf::Texture &texture);

  void set_origin_to_center();

public:
  
  /*
    Returns the x-coordinate of the entity.

    @return the entity's x-coordinate
  */
  float get_xcor(){return sprite.getPosition().x;}

  
  /*
    Returns the y-coordinate of the warrior.

    @return the warrior's y-coordinate
  */
  float get_ycor(){return sprite.getPosition().y;}

  /*
     Sets the coordinates of the warrior to what they would be after the
          specified time had elapsed, based on the velocity of the warrior.
          @param micros_elapsed The time elapsed in microseconds.
  */

  void draw(sf::RenderWindow &window, ColorGrid &color_grid);

  bool intersects(Entity &entity){return sprite.getGlobalBounds().intersects(entity.get_global_bounds());}

  sf::FloatRect get_global_bounds(){return sprite.getGlobalBounds();}

};
