//
// Created by jeremyelkayam on 9/26/20.
//

#pragma once

#include "entity.hpp"
#include "sword.hpp"

class Warrior : public Entity {
protected:
  Sword sword;

public:
  Warrior(float xcor,float ycor, sf::Texture &texture, sf::Texture &sword_tex, sf::Color color);

  virtual void draw(sf::RenderWindow &window, ColorGrid &color_grid);

  //You can only slice if your sword is drawn.
  bool slicing(Entity &entity){return sword.is_active() && entity.intersects(sword);}
};

