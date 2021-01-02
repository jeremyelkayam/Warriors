//
// Created by jeremyelkayam on 9/27/20.
//

#include "logic.hpp"

Logic::Logic(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
    InputManager &an_input_manager) :
text_loader(a_text_loader), resource_manager(a_resource_manager), input_manager(an_input_manager){

  current_screen = unique_ptr<TitleScreen>(new TitleScreen(text_loader, resource_manager,
      input_manager));



  //Initialize the textures containing our placeholder warrior texture. This will likely be changed eventually
  //to support animations.

}

void Logic::draw(sf::RenderWindow &window, ColorGrid &color_grid){
  current_screen->draw(window, color_grid);
}

void Logic::update(float s_elapsed) {
  current_screen->update(s_elapsed);

  if(current_screen->go_to_next()){

    current_screen = current_screen->next_screen();
  }
}
