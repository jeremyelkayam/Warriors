//
// Created by jeremyelkayam on 9/28/20.
//

#pragma once

#include "SFML/Graphics.hpp"
#include "color_grid.hpp"

using std::unique_ptr;

class Screen {

private:

public:

  virtual ~Screen();

  virtual void draw(sf::RenderWindow &window, ColorGrid &color_grid) = 0;

  virtual void update(float s_elapsed) = 0;

  virtual bool go_to_next() = 0;

  virtual unique_ptr<Screen> next_screen(){return unique_ptr<Screen> (nullptr);}

};