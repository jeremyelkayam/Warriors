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

using std::shared_ptr;
using std::make_shared;

int main(int argc, char** argv)
{

  shared_ptr<TextLoader>text_loader = make_shared<TextLoader>();

  //The texture containing our placeholder warrior texture. This will likely be changed eventually
  //to support animations.
  sf::Texture warrior_tex;
  warrior_tex.loadFromFile(text_loader->get_string("IDS_PATH_WARRIOR_TEX"));


  //set up game components
  shared_ptr<Logic>logic = make_shared<Logic>(warrior_tex);

  // create main window
  sf::RenderWindow window(
          sf::VideoMode((unsigned int)text_loader->get_integer("IDS_WINDOW_X"),
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
      int micros_elapsed=clock.restart().asMicroseconds();
      if(window.hasFocus())
	      {
          sf::Event event;
          while(window.pollEvent(event))
            {
              human_view->handle_event(window, event);
            }
          //update renderer and logic
                //cout<<"loop"<<endl;
          logic->update(micros_elapsed);
          human_view->update(window);
          }
    }

  return 0;
}
