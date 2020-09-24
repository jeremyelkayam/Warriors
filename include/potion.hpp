/*
 * potion.hpp
 * Purpose:
 *
 * @author Jeremy Elkayam
 */

#include <SFML/Graphics.hpp>
#include "entity.hpp"

#pragma once

class Potion : public Entity {

public:
  /*
    Constructor for the Potion class. Sets initial values.

    @param xcor initial x-coordinate of the potion.
    @param ycor initial y-coordinate of the potion.
    @param texture the texture to be used by the potion's sprite.
   */
  Potion(float xcor, float ycor, sf::Texture &texture);

};

