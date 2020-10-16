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

private:
  //The amount of time this potion can exist in seconds.
  float lifespan;

  //The amount of time this potion has existed in seconds.
  float age;

  unsigned int health_recovery;

public:
  /*
    Constructor for the Potion class. Sets initial values.

    @param xcor initial x-coordinate of the potion.
    @param ycor initial y-coordinate of the potion.
    @param texture the texture to be used by the potion's sprite.
   */
  Potion(float xcor, float ycor, sf::Texture &texture, float lifespan,int health_recovery);

  void update(float s_elapsed);

  bool can_despawn();

  unsigned int get_health_recovery(){return health_recovery;}


};

