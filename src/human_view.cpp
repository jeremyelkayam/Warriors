/*
  human_view.cpp
  Purpose: Consolidate all rendering operations into a single class, with one
           function that executes with each iteration of the main loop.
  @author Jeremy Elkayam
 */
#include "human_view.hpp"
#include <iostream>

HumanView::HumanView(Logic &logic,
        TextLoader &text_loader) :
        color_grid(text_loader.get_integer("IDS_COLORGRID_SIZE"),
                text_loader.get_float("IDS_VIEW_X"),
                text_loader.get_float("IDS_VIEW_Y")),
                m_text_loader(text_loader),
                m_logic(logic){
  this->view=sf::View(sf::FloatRect(0.f,0.f,
          text_loader.get_float("IDS_VIEW_X"),
          text_loader.get_float("IDS_VIEW_Y")));



  //Initialize our colors.
  d_blue=sf::Color(0,0,215);
  d_red=sf::Color(215,0,0);
  d_magenta=sf::Color(215,0,215);
  d_green=sf::Color(0,215,0);
  d_cyan=sf::Color(0,215,215);
  d_yellow=sf::Color(215,215,0);
  d_white=sf::Color(215,215,215);

}


void HumanView::handle_size(sf::RenderWindow &window){
  //x is width, y is height. their ratio should be 4:3.
  //if not, SCALE THE VIEWPORT
  float current_aspect = (float)window.getSize().x / (float)window.getSize().y ;
  float target_aspect = m_text_loader.get_float("IDS_VIEW_X") / m_text_loader.get_float("IDS_VIEW_Y");
  
  //std::cout<<"current aspect:"<<current_aspect<<std::endl;
  //std::cout<<"target aspect:"<<target_aspect<<std::endl;

  if(current_aspect > target_aspect){
    //it's too wide. let's set the viewport to match the height
    view.setViewport(sf::FloatRect((1 - target_aspect / current_aspect)/2,
                                   0.f,
                                   target_aspect / current_aspect,
                                   1.f));
  }else{
    //either it's too tall or it's perfect. let's set the viewport to match width
    view.setViewport(sf::FloatRect(0.f,
                                   (1 - current_aspect / target_aspect)/2,
                                   1.f,
                                   current_aspect / target_aspect));
  }
  window.setView(view);
}

void HumanView::draw_background(sf::RenderWindow &window, sf::Color bgcolor){
  sf::RectangleShape bgRect = sf::RectangleShape(sf::Vector2f(
          m_text_loader.get_float("IDS_VIEW_X"),
          m_text_loader.get_float("IDS_VIEW_Y")));
  bgRect.setPosition(0.f,0.f);
  bgRect.setFillColor(bgcolor);
  window.draw(bgRect);
}


void HumanView::update(sf::RenderWindow &window){

  //handle inputs

  keyboard_movement();

  //std::cout<<"drawing"<<std::endl;
  handle_size(window);
  color_grid.reset();
  window.clear(d_white);
  draw_background(window, sf::Color::Black);

  m_logic.draw_components(window,color_grid);

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

void HumanView::keyboard_movement(){
  m_logic.set_player_movement(

          sf::Keyboard::isKeyPressed(sf::Keyboard::Up),
          sf::Keyboard::isKeyPressed(sf::Keyboard::Down),
          sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
          sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

  m_logic.set_player_sword(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
}