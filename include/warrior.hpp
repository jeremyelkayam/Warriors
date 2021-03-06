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

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) const override;

  //You can only slice if your sword is drawn.
  bool slicing(Entity &entity) const {return sword.is_active() && entity.intersects(sword);}
};

