/*
  logic.cpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#include "logic.hpp"

Logic::Logic(sf::Texture &warriorTex) : player(0,0,0.0001,warriorTex){

}

void Logic::update(int micros_elapsed){
  player.move(micros_elapsed);
}

void Logic::draw_components(sf::RenderWindow &window,ColorGrid &color_grid){

  player.draw(window,color_grid);
}