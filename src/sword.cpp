//
// Created by jeremyelkayam on 9/26/20.
//

#include "sword.hpp"


Sword::Sword(float xcor, float ycor, sf::Texture &texture, float warrior_width, sf::Color warrior_color)
: Entity(xcor,ycor,texture) {

  color = warrior_color;

  active = false;

  //Set our sprite's coordinates to the center of the warrior to which it belongs.
  sf::FloatRect sprite_rect=sprite.getLocalBounds();
  sprite.setOrigin(sprite_rect.left - warrior_width,
                   sprite_rect.top + sprite_rect.height/2);
}

void Sword::update(float xcor, float ycor, float angle){
  sprite.setPosition(xcor,ycor);

  //convert the sword's angle into degrees because SFML likes degrees for some reason
  angle *= 180 / M_PI;
  sprite.setRotation(angle);
}