/*
 * entity.hpp
 *
 * @author Jeremy Elkayam
 */

#pragma once

#include "entity.hpp"

class Sword : public Entity {
private:

  bool active;

public:

  Sword(float xcor, float ycor, sf::Texture &texture, float warrior_width, sf::Color color);

  void unsheath(){active = true;}

  void sheath(){active = false;}

  //todo: fix this warning
  void draw(sf::RenderWindow &window, ColorGrid &grid){if(active) Entity::draw(window,grid);}

  void update(float xcor, float ycor, float angle);

};
