/*
  pong.cpp
  Purpose: Main executable for whatever this Warriors thing is. Controls setup
  /teardown of game as well as game loop.
  
  @author Jeremy Elkayam
 */
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;


int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,
				     600,
				     24),
		       "Warriors",
		       sf::Style::Titlebar | sf::Style::Close);
  //enable titlebar & close options
  sf::Clock clock;
  
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
	  //logic->update(micros_elapsed);
	  //human_view->update();
  //	}
//  }

  return 0;
}
