/*
  human_view.cpp
  Purpose: Consolidate all rendering operations into a single class, with one
           function that executes with each iteration of the main loop.
  @author Jeremy Elkayam
 */
#include "human_view.hpp"
#include <iostream>

HumanView::HumanView(Logic &a_logic,
        TextLoader &text_loader) :
        color_grid(text_loader.get_integer("IDS_COLORGRID_SIZE"),
                text_loader.get_float("IDS_VIEW_X"),
                text_loader.get_float("IDS_VIEW_Y")),
                m_text_loader(text_loader),
                logic(a_logic){




  //Initialize our colors.
  d_blue=sf::Color(0,0,215);
  d_red=sf::Color(215,0,0);
  d_magenta=sf::Color(215,0,215);
  d_green=sf::Color(0,215,0);
  d_cyan=sf::Color(0,215,215);
  d_yellow=sf::Color(215,215,0);
  d_white=sf::Color(215,215,215);

}




void HumanView::update(sf::RenderWindow &window){

  //handle inputs

  keyboard_movement();
  color_grid.reset();
  window.clear(d_white);
  //std::cout<<"drawing"<<std::endl;

  //todo: fix this terribleness

  logic.draw(window, color_grid);

  color_grid.draw(window);
  window.setView(window.getDefaultView());
  window.display();
}

void HumanView::handle_event(sf::RenderWindow &window, sf::Event &evt){
  switch(evt.type){
    case sf::Event::Closed :
      window.close();
      break;
  }
}


//todo: this is getting out of hand. Maybe throw this into a "controls" class.
void HumanView::keyboard_movement(){
  logic.set_player_movement(

          sf::Keyboard::isKeyPressed(sf::Keyboard::Up),
          sf::Keyboard::isKeyPressed(sf::Keyboard::Down),
          sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
          sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

  logic.set_player_sword(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
}