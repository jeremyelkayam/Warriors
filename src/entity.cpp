/*

  float healthRecovery
  warrior.cpp
  Purpose: Represent a warrior. A warrior is any of the characters in the game. This class is abstract,
  and should therefore never be instantiated. Instead instantiate a subclass-- Player or Enemy.
  @author Jeremy Elkayam
 */

#include "entity.hpp"

Entity::Entity(float xcor, float ycor, sf::Texture &texture) {
  this->sprite.setPosition(xcor,ycor);
  this->sprite.setTexture(texture);
}

void Entity::draw(sf::RenderWindow &window, ColorGrid &color_grid) const {
  window.draw(sprite);
  color_grid.update(sprite.getGlobalBounds(),color);
}

void Entity::set_origin_to_center() {
  //Set our sprite's coordinates to the center of the sprite. It'll Just Make Things A Bit Easier
  sf::FloatRect sprite_rect=sprite.getLocalBounds();
  sprite.setOrigin(sprite_rect.left + sprite_rect.width/2,
                   sprite_rect.top + sprite_rect.height/2);
}