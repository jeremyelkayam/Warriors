//
// Created by jeremyelkayam on 9/27/20.
//

#pragma once

#include <chrono>
#include <random>
#include <memory>
#include "playing_screen.hpp"
#include "title_screen.hpp"
#include "resource_manager.hpp"

using std::unique_ptr;

class Logic {

private:


  TextLoader &text_loader;

  ResourceManager &resource_manager;

  InputManager &input_manager;

  unique_ptr<Screen> current_screen;

public:
  Logic(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
      InputManager &an_input_manager);

  void update(float s_elapsed);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid);

//  void set_player_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right){
//    current_screen->set_player_movement(moving_up,moving_down,moving_left,moving_right);}

//  void set_player_sword(bool active){current_screen->set_player_sword(active);}

  void handle_event(sf::Event &evt){current_screen->handle_event(evt);}

};

