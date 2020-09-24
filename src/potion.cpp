/*
 * potion.hpp
 *
 *
 * @author Jeremy Elkayam
 */

#include "potion.hpp"

Potion::Potion(float xcor, float ycor, sf::Texture &texture,float lifespan, int health_recovery) : Entity(xcor,ycor,texture) {
  this->lifespan = lifespan;
  this->health_recovery = health_recovery;
  age = 0;
}

bool Potion::can_despawn(){
  //If the age of this potion is longer than its lifespan, it should be destroyed.
  return age > lifespan;
}

void Potion::update(float s_elapsed) {
  age += s_elapsed;
}