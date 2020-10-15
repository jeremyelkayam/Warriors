//
// Created by jeremyelkayam on 10/14/20.
//

#include "special_item.hpp"

SpecialItem::SpecialItem(float xcor, float ycor, sf::Texture &texture, float a_appear_time) :
Entity(xcor,ycor,texture), appear_time(a_appear_time) {
  active = false;
  consumed = false;
  age = 0;
  color = sf::Color::Yellow;
}

void SpecialItem::update(float s_elapsed) {
  age += s_elapsed;
  if(age >= appear_time && !consumed ) {
    active = true;
  }
}

void SpecialItem::consume(){
  assert(active);
  consumed = true;
  active = false;
}