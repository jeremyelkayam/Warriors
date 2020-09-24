/*
  warriors.cpp
  Purpose: Main executable for whatever this Warriors thing is. Controls setup
  /teardown of game as well as game loop.
  
  @author Jeremy Elkayam
 */
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <random>
#include <chrono>
#include "human_view.hpp"
#include "logic.hpp"
#include "text_loader.hpp"

using std::shared_ptr;
using std::make_shared;
using std::mt19937;
using std::chrono::high_resolution_clock;

int main(int argc, char** argv)
{

  shared_ptr<TextLoader>text_loader = make_shared<TextLoader>();

  mt19937 randy;
  unsigned long my_seed = (unsigned)high_resolution_clock::now().time_since_epoch().count();
  cout << "my seed: " << my_seed << endl;
  randy.seed(my_seed);
  //The texture containing our placeholder warrior texture. This will likely be changed eventually
  //to support animations.
  sf::Texture warrior_tex;
  warrior_tex.loadFromFile(text_loader->get_string("IDS_PATH_WARRIOR_TEX"));

  //set up game components
  shared_ptr<Logic>logic = make_shared<Logic>(warrior_tex,randy,
          (float)text_loader->get_double("IDS_VIEW_X"),
          (float)text_loader->get_double("IDS_VIEW_Y"));

  // create main window
  sf::RenderWindow window(
          sf::VideoMode(
                  (unsigned int)text_loader->get_integer("IDS_WINDOW_X"),
                  (unsigned int)text_loader->get_integer("IDS_WINDOW_Y"),
                  (unsigned int)text_loader->get_integer("IDS_WINDOW_PDEPTH")),
          text_loader->get_string("IDS_W_NAME"),
          sf::Style::Resize | sf::Style::Close);
  //set up rendering
  shared_ptr<HumanView>human_view = make_shared<HumanView>(logic, text_loader);

  //enable titlebar & close options
  sf::Clock clock;

  
  // start main loop
  while(window.isOpen())
    {
      //Reset clock and track elapsed time since last loop.
      float s_elapsed=clock.restart().asSeconds();
      //cout << s_elapsed << endl;
      if(window.hasFocus())
	      {
          sf::Event event;
          while(window.pollEvent(event))
            {
              human_view->handle_event(window, event);
            }
          //update renderer and logic
                //cout<<"loop"<<endl;
          logic->update(s_elapsed);
          human_view->update(window);
          }
    }

  return 0;
}
