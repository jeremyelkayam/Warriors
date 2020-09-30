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
        view(sf::FloatRect(0.f,0.f,
                      text_loader.get_float("IDS_VIEW_X"),
                      text_loader.get_float("IDS_VIEW_Y"))),
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

  //keyboard_movement();
  color_grid.reset();
  window.clear(d_white);
  //std::cout<<"drawing"<<std::endl;

  handle_size(window, 0.f);
  window.setView(view);
  draw_background(window, sf::Color::Black);
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


void HumanView::handle_size(sf::RenderWindow &window, float top_padding){
  //x is width, y is height. their ratio should be 4:3.
  //if not, SCALE THE VIEWPORT
  float current_aspect = (float)window.getSize().x / (float)window.getSize().y ;
  float target_aspect = view.getSize().x / view.getSize().y;

  //std::cout<<"current aspect:"<<current_aspect<<std::endl;
  //std::cout<<"target aspect:"<<target_aspect<<std::endl;

  if(current_aspect > target_aspect){
    //it's too wide. let's set the viewport to match the height
    view.setViewport(sf::FloatRect((1 - target_aspect / current_aspect)/2,
                                   top_padding,
                                   target_aspect / current_aspect,
                                   1.f));
  }else{
    //either it's too tall or it's perfect. let's set the viewport to match width
    view.setViewport(sf::FloatRect(0.f,
                                   (1 - current_aspect / target_aspect)/2 + top_padding * (current_aspect / target_aspect),
                                   1.f,
                                   current_aspect / target_aspect * 1.f));
  }
  //window.setView(view);
}

void HumanView::draw_background(sf::RenderWindow &window, sf::Color bgcolor){
  window.setView(view);
  sf::RectangleShape bgRect = sf::RectangleShape(sf::Vector2f(
          view.getSize().x,
          view.getSize().y));
  bgRect.setPosition(0.f,0.f);
  bgRect.setFillColor(bgcolor);
  window.draw(bgRect);
}