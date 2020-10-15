//
// Created by jeremyelkayam on 10/14/20.
//

#pragma once
#include "entity.hpp"

class SpecialItem : public Entity {

private:

  bool active, consumed;

  //The amount of time this special item has existed in seconds.
  float age;

  //The amount of time after which this special item will appear.
  const float appear_time;

public:

  SpecialItem(float xcor, float ycor, sf::Texture &texture, float a_appear_time);

  bool is_active() {return active;}

  void update(float s_elapsed);

  void consume();

};