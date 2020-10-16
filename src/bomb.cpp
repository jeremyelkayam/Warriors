//
// Created by jeremyelkayam on 10/16/20.
//

#include "bomb.hpp"

Bomb::Bomb(sf::Texture &body_tex, sf::Texture &fuse_tex, sf::SoundBuffer &fuse_sound, float appear_time) :
SpecialItem(body_tex, fuse_sound, appear_time){
  color = sf::Color::White;
  fuse_sprite.setTexture(fuse_tex);

  //Set fuse_sprite's origin to its bottom left corner. This will allow us to give it the same location as the main
  //sprite while placing it on top.
  sf::FloatRect sprite_rect=fuse_sprite.getLocalBounds();
  fuse_sprite.setOrigin(sprite_rect.left,
          sprite_rect.top + sprite_rect.height);
}

void Bomb::spawn(float xcor, float ycor) {
  SpecialItem::spawn(xcor,ycor);
  fuse_sprite.setPosition(xcor,ycor);
}

void Bomb::draw(sf::RenderWindow &window, ColorGrid &color_grid) const {
  if(active){
    Entity::draw(window,color_grid);

    window.draw(fuse_sprite);
    color_grid.update(fuse_sprite.getGlobalBounds(),sf::Color::Yellow);
  }
}
