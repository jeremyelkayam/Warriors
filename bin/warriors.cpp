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
#include "human_view.hpp"
#include "logic.hpp"
#include "text_loader.hpp"
#include "resource_manager.hpp"
#include "input_manager.hpp"

using std::shared_ptr;
using std::make_shared;
using std::mt19937;
using std::chrono::high_resolution_clock;

int main(int argc, char** argv)
{

  TextLoader text_loader;

  ResourceManager resource_manager(text_loader);

  InputManager input_manager((unsigned)text_loader.get_integer("IDS_MAX_PLAYERS"));

  //set up game componentss

  Logic logic(text_loader, resource_manager);

  // create main window
  sf::RenderWindow window(
          sf::VideoMode(
                  (unsigned int)text_loader.get_integer("IDS_WINDOW_X"),
                  (unsigned int)text_loader.get_integer("IDS_WINDOW_Y"),
                  (unsigned int)text_loader.get_integer("IDS_WINDOW_PDEPTH")),
          text_loader.get_string("IDS_W_NAME"),
          sf::Style::Resize | sf::Style::Close);
  //set up rendering
  HumanView human_view(logic, text_loader);

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
              human_view.handle_event(window, event);
            }
          //update renderer and logic
                //cout<<"loop"<<endl;
          logic.update(s_elapsed);
          human_view.update(window);
          }
    }

  return 0;
}
