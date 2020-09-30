//
// Created by jeremyelkayam on 9/29/20.
//

#pragma once

#include "screen.hpp"

class TitleScreen : public Screen {

private:

  sf::Sprite title_background;


public:
  TitleScreen(TextLoader &text_loader, ResourceManager &resource_manager);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

  void update(float s_elapsed) override;

  bool go_to_next() override;

};

