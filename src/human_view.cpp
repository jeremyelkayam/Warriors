/*
  human_view.cpp
  Purpose: Consolidate all rendering operations into a single class, with one
           function that executes with each iteration of the main loop.
  @author Jeremy Elkayam
 */
#include "human_view.hpp"
#include <iostream>

HumanView::HumanView(PlayingScreen &logic,
        TextLoader &text_loader) :
        color_grid(text_loader.get_integer("IDS_COLORGRID_SIZE"),
                text_loader.get_float("IDS_VIEW_X"),
                text_loader.get_float("IDS_VIEW_Y")),
                m_text_loader(text_loader),
                m_logic(logic),
                view(sf::FloatRect(0.f,0.f,
                    text_loader.get_float("IDS_VIEW_X"),
                    text_loader.get_float("IDS_VIEW_Y"))),
                hud_view(sf::FloatRect(0.f,0.f,
                        text_loader.get_float("IDS_VIEW_X"),
                        32.f)){




  //Initialize our colors.
  d_blue=sf::Color(0,0,215);
  d_red=sf::Color(215,0,0);
  d_magenta=sf::Color(215,0,215);
  d_green=sf::Color(0,215,0);
  d_cyan=sf::Color(0,215,215);
  d_yellow=sf::Color(215,215,0);
  d_white=sf::Color(215,215,215);

}


void HumanView::handle_size(sf::RenderWindow &window, sf::View &view, float top_padding){

  //x is width, y is height. their ratio should be 4:3.
  //if not, SCALE THE VIEWPORT
  float current_aspect = (float)window.getSize().x / (float)window.getSize().y ;
  float target_aspect = m_text_loader.get_float("IDS_VIEW_X") / (m_text_loader.get_float("IDS_VIEW_Y") + 32);
  
  //std::cout<<"current aspect:"<<current_aspect<<std::endl;
  //std::cout<<"target aspect:"<<target_aspect<<std::endl;

  float view_height = view.getSize().y / 192.f;


  if(current_aspect > target_aspect){
    //it's too wide. let's set the viewport to match the height
    view.setViewport(sf::FloatRect((1 - target_aspect / current_aspect)/2,
                                   top_padding,
                                   target_aspect / current_aspect,
                                   view_height));
  }else{
    //either it's too tall or it's perfect. let's set the viewport to match width
    view.setViewport(sf::FloatRect(0.f,
                                   (1 - current_aspect / target_aspect)/2 + top_padding * (current_aspect / target_aspect),
                                   1.f,
                                   current_aspect / target_aspect * view_height));
  }
  //window.setView(view);
}

void HumanView::draw_background(sf::RenderWindow &window, sf::View &view, sf::Color bgcolor){
  sf::RectangleShape bgRect = sf::RectangleShape(sf::Vector2f(
          view.getSize().x,
          view.getSize().y));
  bgRect.setPosition(0.f,0.f);
  bgRect.setFillColor(bgcolor);
  window.draw(bgRect);
}


void HumanView::update(sf::RenderWindow &window){

  //handle inputs

  keyboard_movement();
  color_grid.reset();
  window.clear(d_white);
  //std::cout<<"drawing"<<std::endl;

  //todo: fix this terribleness

  if(!m_logic.game_over()){

    handle_size(window, hud_view, 0.f);
    window.setView(hud_view);
    draw_background(window, hud_view, sf::Color::Red);

    m_logic.draw_hud(window, color_grid);

    handle_size(window, view, 0.166667f);
    window.setView(view);
    draw_background(window, view, sf::Color::Black);

    m_logic.draw_gameplay(window, color_grid);

  }else{
    window.close();
  }



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