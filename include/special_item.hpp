//
// Created by jeremyelkayam on 10/14/20.
//

#pragma once
#include "entity.hpp"
#include <SFML/Audio.hpp>

class SpecialItem : public Entity {

protected:

  bool active, consumed;

  //The amount of time this special item has existed in seconds.
  float age;

  //The amount of time after which this special item will appear.
  const float appear_time;

  sf::Sound used_sound;

public:

  SpecialItem(sf::Texture &texture, sf::SoundBuffer &used_sound_buffer, float a_appear_time);

  bool item_active() {return active;}

  bool effect_active() {return used_sound.getStatus() == sf::Sound::Playing;}

  void update(float s_elapsed);

  void consume();

  virtual void spawn(float xcor, float ycor);

  bool ready_to_spawn(){return age >= appear_time && !consumed && !active; }

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) const override;

};