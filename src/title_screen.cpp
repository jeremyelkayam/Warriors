//
// Created by jeremyelkayam on 9/29/20.
//

#include "title_screen.hpp"

TitleScreen::TitleScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager) :
Screen(a_text_loader, a_resource_manager) {

  title_background.setTexture(resource_manager.get_texture("IDS_PATH_TITLE_TEX"));

  screen_over = false;

}

void TitleScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid) {

  window.draw(title_background);
}

bool TitleScreen::go_to_next() {
  return screen_over;
}

unique_ptr<Screen> TitleScreen::next_screen(){
  assert(go_to_next());
  return unique_ptr<PlayingScreen>(new PlayingScreen(text_loader, resource_manager));
}

void TitleScreen::handle_event(sf::Event &evt) {
  //if the mouse was clicked or a key was pressed, we can move on.
  screen_over = (evt.type == sf::Event::EventType::MouseButtonPressed ||
          evt.type == sf::Event::EventType::KeyPressed);
}
