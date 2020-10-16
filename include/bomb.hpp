//
// Created by jeremyelkayam on 10/16/20.
//

#pragma once

#include "special_item.hpp"

class Bomb : public SpecialItem {

private:
  sf::Sprite fuse_sprite;

public:
  Bomb(sf::Texture &body_tex, sf::Texture &fuse_tex, sf::SoundBuffer &fuse_sound, float appear_time);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) const override;

  void spawn(float xcor, float ycor) override;
};
