//
// Created by jeremyelkayam on 9/29/20.
//

#include "title_screen.hpp"

TitleScreen::TitleScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager) :
Screen(a_text_loader, a_resource_manager) {

  title_background.setTexture(resource_manager.get_texture("IDS_PATH_TITLE_TEX"));

}

void TitleScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid) {

  window.draw(title_background);
}

void TitleScreen::update(float s_elapsed) {

  return;
}


bool TitleScreen::go_to_next() {
  return false;
}