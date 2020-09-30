//
// Created by jeremyelkayam on 9/27/20.
//

#include "logic.hpp"

Logic::Logic(TextLoader &a_text_loader, sf::Texture &a_warrior_tex, sf::Texture &a_sword_tex) :
text_loader(a_text_loader), warrior_tex(a_warrior_tex), sword_tex(a_sword_tex){

  current_screen = unique_ptr<PlayingScreen>(new PlayingScreen(warrior_tex, sword_tex, randy, a_text_loader));

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

    cout << "you lose. restarting game" << endl;

    current_screen = unique_ptr<PlayingScreen>(new PlayingScreen(warrior_tex, sword_tex, randy, text_loader));
  }
}
