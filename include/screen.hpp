//
// Created by jeremyelkayam on 9/28/20.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "color_grid.hpp"
#include "resource_manager.hpp"

using std::unique_ptr;

class Screen {

protected:

  TextLoader &text_loader;
  ResourceManager &resource_manager;



public:

  Screen(TextLoader &a_text_loader, ResourceManager &a_resource_manager);


  virtual ~Screen();

  virtual void draw(sf::RenderWindow &window, ColorGrid &color_grid) = 0;

  virtual void update(float s_elapsed){};

  virtual bool go_to_next() = 0;

  virtual unique_ptr<Screen> next_screen() = 0;

  virtual void handle_event(sf::Event &evt){};

};