//
// Created by jeremyelkayam on 9/29/20.
//

#pragma once

#include "screen.hpp"
#include "menu_screen.hpp"

class TitleScreen : public Screen {

private:

  sf::Sprite title_background;

  sf::Sound title_theme;

  bool screen_over;


public:
  TitleScreen(TextLoader &text_loader, ResourceManager &resource_manager,
      InputManager &an_input_manager);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

  bool go_to_next() override;

  void handle_event(sf::Event &evt) override;

  unique_ptr<Screen> next_screen() override;

};

