/*
 * entity.hpp
 *
 * @author Jeremy Elkayam
 */

#pragma once

#include "entity.hpp"
#include <iostream>


class Sword : public Entity {
private:

  bool active;

public:

  Sword(float xcor, float ycor, sf::Texture &texture, float warrior_width, sf::Color color);

  //void set_active(bool active){this->active = active;}

  void unsheath(){this->active = true; }
  void sheath(){this->active = false; }

  void draw(sf::RenderWindow &window, ColorGrid &grid) const{if(active) Entity::draw(window,grid);}

  void update(float xcor, float ycor, float angle);

  void update(float xcor, float ycor){sprite.setPosition(xcor,ycor);};

  bool is_active() const {return active;}

};
