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
#include "text_loader.hpp"

using std::shared_ptr;

class HumanView
{
private:
  //A reference to the class that handles game logic.
  shared_ptr<Logic>logic;
  
  //A reference to the window that we're rendering to.
  shared_ptr<sf::RenderWindow> window;

  //A reference to the text loader.
  shared_ptr<TextLoader>text_loader;

  //The view containing the main gameplay.
  sf::View view;

 /* Conveniently, all 8 "bright mode" Speccy colors are included by default in
  * SFML. However, the 7 other "nonbright" (or dim) colors are not included by 
  * default, so I'm going to declare them here.
  */
  sf::Color d_blue, d_red, d_magenta, d_green, d_cyan, d_yellow, d_gray, d_white;

  //Are sfml's default colors the same as these?

  
  void draw_warrior(shared_ptr<Warrior>warrior);

  void draw_background(sf::Color bgcolor);

  void handle_size();

public:
  /*
    Constructor for the HumanView class. Initializes the class's objects.
    @param logic A reference to the class handling game logic.
    @param window
   */
  HumanView(shared_ptr<Logic>logic,
          shared_ptr<sf::RenderWindow>window,
          shared_ptr<TextLoader>text_loader);

  /*
    Should be called once every loop. Observes the properties of the game,
    and renders objects accordingly.
   */
  void update();
};
