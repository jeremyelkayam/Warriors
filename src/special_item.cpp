//
// Created by jeremyelkayam on 10/14/20.
//

#include "special_item.hpp"

SpecialItem::SpecialItem(sf::Texture &texture, sf::SoundBuffer &used_sound_buffer, float a_appear_time) :
Entity(0.f,0.f,texture), appear_time(a_appear_time) {
  consumed = false;
  active = false;
  age = 0;
  color = sf::Color::Yellow;
  used_sound.setBuffer(used_sound_buffer);
}

void SpecialItem::update(float s_elapsed) {
  age += s_elapsed;
}

void SpecialItem::consume(){
  assert(active);
  active = false;
  consumed = true;
  used_sound.play();
}

void SpecialItem::spawn(float xcor, float ycor) {
  assert(ready_to_spawn());

  this->sprite.setPosition(xcor,ycor);
  active = true;
}

void SpecialItem::draw(sf::RenderWindow &window, ColorGrid &color_grid) const {
  if(active) Entity::draw(window, color_grid);
}
