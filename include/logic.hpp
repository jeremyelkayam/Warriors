//
// Created by jeremyelkayam on 9/27/20.
//

#pragma once

#include <chrono>
#include <random>
#include <memory>
#include "playing_screen.hpp"

using std::unique_ptr;

class Logic {

private:

  sf::Texture & warrior_tex, sword_tex;

  TextLoader &text_loader;

  std::mt19937 randy;

  //todo: change to a screen superclass
  unique_ptr<Screen> current_screen;

public:
  Logic(TextLoader &a_text_loader, sf::Texture &warrior_tex, sf::Texture &sword_tex);

  void update(float s_elapsed);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid);

  //todo: this multilevel wrapper function is fucking garbage. fix it
//  void set_player_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right){
//    current_screen->set_player_movement(moving_up,moving_down,moving_left,moving_right);}

//  void set_player_sword(bool active){current_screen->set_player_sword(active);}

};

