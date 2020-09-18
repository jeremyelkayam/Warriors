/*
  human_view.hpp
  Purpose: Consolidate all rendering operations into a single class, with one
           function that executes with each iteration of the main loop.
  @author Jeremy Elkayam
 */


#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "logic.hpp"

class HumanView
{
private:
  //A reference to the class that handles game logic.
  std::shared_ptr<Logic>logic;
  
  //A reference to the window that we're rendering to.
  std::shared_ptr<sf::RenderWindow> window;

  //The view containing the main gameplay.
  sf::View view;

 /* Conveniently, all 8 "bright mode" Speccy colors are included by default in
  * SFML. However, the 7 other "nonbright" (or dim) colors are not included by 
  * default, so I'm going to declare them here.
  */
  sf::Color d_blue, d_red, d_magenta, d_green, d_cyan, d_yellow, d_gray, d_white;

  //Are sfml's default colors the same as these?

  
  void draw_warrior(std::shared_ptr<Warrior>warrior);

  void draw_background(sf::Color bgcolor);

  void handle_size();

public:
  /*
    Constructor for the HumanView class. Initializes the class's objects.
    @param logic A reference to the class handling game logic.
    @param window
   */
  HumanView(std::shared_ptr<Logic>logic,std::shared_ptr<sf::RenderWindow>window);

  /*
    Should be called once every loop. Observes the properties of the game,
    and renders objects accordingly.
   */
  void update();
};
