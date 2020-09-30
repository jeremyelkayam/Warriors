//
// Created by jeremyelkayam on 9/27/20.
//

#include "logic.hpp"

Logic::Logic(TextLoader &a_text_loader, ResourceManager &a_resource_manager) :
text_loader(a_text_loader), resource_manager(a_resource_manager){

  current_screen = unique_ptr<TitleScreen>(new TitleScreen(text_loader, resource_manager));

  //Let's set up our random number generator with a commonly used seed: the current time.
  unsigned long my_seed = (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count();
  cout << "my seed: " << my_seed << endl;
  randy.seed(my_seed);


  //Initialize the textures containing our placeholder warrior texture. This will likely be changed eventually
  //to support animations.

}

void Logic::draw(sf::RenderWindow &window, ColorGrid &color_grid){
  current_screen->draw(window, color_grid);
}

void Logic::update(float s_elapsed) {
  current_screen->update(s_elapsed);

  if(current_screen->go_to_next()){

    //current_screen = unique_ptr<PlayingScreen>(new PlayingScreen(randy, text_loader, resource_manager));
  }
}
