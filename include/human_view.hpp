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
  std::shared_ptr<sf::RenderWindow> window;
  sf::View view;

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
