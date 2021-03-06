/*
  human_view.hpp
  Purpose: Consolidate rendering operations and

  @author Jeremy Elkayam
 */


#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "logic.hpp"
#include "text_loader.hpp"
#include "color_grid.hpp"

using std::shared_ptr;
using std::vector;

class HumanView
{
private:
  //A reference to the class that handles game logic.
  Logic &logic;


  sf::View view;

  //A reference to the text loader.
  TextLoader &m_text_loader;


  //The color grid for our image.
  ColorGrid color_grid;

 /* Conveniently, all 8 "bright mode" Speccy colors are included by default in
  * SFML. However, the 7 other "nonbright" (or dim) colors are not included by 
  * default, so I'm going to declare them here.
  */
  sf::Color d_blue, d_red, d_magenta, d_green, d_cyan, d_yellow, d_white;

  void handle_size(sf::RenderWindow &window, float top_padding);

  void draw_background(sf::RenderWindow &window, sf::Color bgcolor);


public:
  /*
    Constructor for the HumanView class. Initializes the class's objects.
    @param logic A reference to the class handling game logic.
    @param window
   */
  HumanView(Logic &a_logic,
          TextLoader &text_loader);

  /*
    Should be called once every loop. Observes the properties of the game,
    and renders objects accordingly.
   */
  void update(sf::RenderWindow& window);

  void handle_event(sf::RenderWindow& window, sf::Event& evt);

};
