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
  

  //set up game components
  shared_ptr<Logic>logic = make_shared<Logic>();
  shared_ptr<TextLoader>text_loader = make_shared<TextLoader>();
  
  // create main window
  shared_ptr<sf::RenderWindow>App = make_shared<sf::RenderWindow>(
          sf::VideoMode((unsigned int)text_loader->get_integer("IDS_WINDOW_X"),
                        (unsigned int)text_loader->get_integer("IDS_WINDOW_Y"),
                        (unsigned int)text_loader->get_integer("IDS_WINDOW_PDEPTH")),
		       text_loader->get_string("IDS_W_NAME"),
		       sf::Style::Resize | sf::Style::Close);

  //set up rendering
  shared_ptr<HumanView>human_view = make_shared<HumanView>(logic, App,text_loader);

  
  //enable titlebar & close options
  sf::Clock clock;

  
  // start main loop
  while(App->isOpen())
    {
      //Reset clock and track elapsed time since last loop.
      int micros_elapsed=clock.restart().asMicroseconds();
      if(App->hasFocus())
	{
           
	  // process events
	  sf::Event Event;
	  while(App->pollEvent(Event))
	    {
	      //logic->handle_event(Event,&App);
	    }
	  //update renderer and logic
          //cout<<"loop"<<endl;
	  logic->update(micros_elapsed);
	  human_view->update();
  	}
    }

  return 0;
}
