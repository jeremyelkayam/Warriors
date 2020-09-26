//
// Created by jeremyelkayam on 9/26/20.
//

#include <SFML/Graphics/Texture.hpp>
#include "warrior.hpp"

Warrior::Warrior(float xcor,float ycor, sf::Texture &texture, sf::Texture &sword_tex, sf::Color color) :
Entity(xcor,ycor,texture), sword(xcor,ycor,sword_tex,sprite.getLocalBounds().width/2, color){
  set_origin_to_center();
  this->color = color;
}

void Warrior::draw(sf::RenderWindow &window, ColorGrid &color_grid) {
  sword.draw(window, color_grid);
  Entity::draw(window, color_grid);
}