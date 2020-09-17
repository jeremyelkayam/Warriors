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

using namespace std;


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,
				     600,
				     24),
		       "Warriors",
		       sf::Style::Resize | sf::Style::Close);
  //enable titlebar & close options
  sf::Clock clock;

  //set up game components
  std::shared_ptr<Logic>logic = std::make_shared<Logic>();
  std::shared_ptr<HumanView>human_view = std::make_shared<HumanView>(logic, &App);

  cout<<"hey i did it"<<endl;

  
  // start main loop
  while(App.isOpen())
    {
      //Reset clock and track elapsed time since last loop.
      int micros_elapsed=clock.restart().asMicroseconds();
      if(App.hasFocus())
	{
           
	  // process events
	  sf::Event Event;
	  while(App.pollEvent(Event))
	    {
	      //logic->handle_event(Event,&App);
	    }
	  //update renderer and logic
          cout<<"loop"<<endl;
	  logic->update(micros_elapsed);
	  human_view->update();
  	}
    }

  return 0;
}
