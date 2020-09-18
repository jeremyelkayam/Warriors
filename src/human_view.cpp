/*
  human_view.cpp
  Purpose: Consolidate all rendering operations into a single class, with one
           function that executes with each iteration of the main loop.
  @author Jeremy Elkayam
 */
#include "human_view.hpp"
#include <iostream>

HumanView::HumanView(shared_ptr<Logic>logic,
        shared_ptr<sf::RenderWindow>window,
        shared_ptr<TextLoader>text_loader)
{
  this->logic=logic;
  this->window=window;
  this->text_loader=text_loader;
  this->view=sf::View(sf::FloatRect(0.f,0.f,
          (float)text_loader->get_double("IDS_VIEW_X"),
          (float)text_loader->get_double("IDS_VIEW_Y")));
}

void HumanView::draw_warrior(std::shared_ptr<Warrior>warrior){
  const float height = (float)text_loader->get_double("IDS_WARRIOR_H");
  const float width = (float)text_loader->get_double("IDS_WARRIOR_W");

  sf::RectangleShape warriorRect = sf::RectangleShape(sf::Vector2f(height,width));
  warriorRect.setPosition((float)warrior->get_xcor()-height/2,(float)warrior->get_ycor()-width/2);
  warriorRect.setFillColor(sf::Color::Cyan);
  window->draw(warriorRect);
}

void HumanView::handle_size(){
  //x is width, y is height. their ratio should be 4:3.
  //if not, SCALE THE VIEWPORT
  float current_aspect = (float)window->getSize().x / (float)window->getSize().y;
  float target_aspect = text_loader->get_double("IDS_VIEW_X")/text_loader->get_double("IDS_VIEW_Y");
  
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
  window->setView(view);
}

void HumanView::draw_background(sf::Color bgcolor){
  sf::RectangleShape bgRect = sf::RectangleShape(sf::Vector2f(
          (float)text_loader->get_double("IDS_VIEW_X"),
          (float)text_loader->get_double("IDS_VIEW_Y")));
  bgRect.setPosition(0.f,0.f);
  bgRect.setFillColor(bgcolor);
  window->draw(bgRect);
}

void HumanView::update(){
  //std::cout<<"drawing"<<std::endl;
  handle_size();
  window->clear(sf::Color::White);
  draw_background(sf::Color::Black);
  draw_warrior(logic->getPlayer());
  window->setView(window->getDefaultView());
  window->display();
}
