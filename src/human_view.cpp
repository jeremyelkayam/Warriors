/*
  human_view.cpp
  Purpose: Consolidate all rendering operations into a single class, with one
           function that executes with each iteration of the main loop.
  @author Jeremy Elkayam
 */
#include "human_view.hpp"
#include <iostream>

HumanView::HumanView(std::shared_ptr<Logic>logic,sf::RenderWindow *window)
{
  this->logic=logic;
  this->window=window;
  this->view=sf::View(sf::FloatRect(0.f,0.f,800.f,600.f));
}

void HumanView::draw_warrior(std::shared_ptr<Warrior>warrior){
  sf::RectangleShape warriorRect = sf::RectangleShape(sf::Vector2f(30,30));
  warriorRect.setPosition(warrior->get_xcor(),warrior->get_ycor());
  warriorRect.setFillColor(sf::Color::Blue);
  window->draw(warriorRect);
}

void HumanView::handle_size(){
  std::cout<<"x="<<window->getSize().x<<std::endl<<"y="<<window->getSize().y<<std::endl;
  //x is width, y is height. their ratio should be 4:3.
  //if not, SCALE THE VIEWPORT
  float current_aspect = (float)window->getSize().x / (float)window->getSize().y;
  float target_aspect = 4.0/3.0;
  
  std::cout<<"current aspect:"<<current_aspect<<std::endl;
  std::cout<<"target aspect:"<<target_aspect<<std::endl;

  

  if(current_aspect > target_aspect){
    //it's too wide. let's set the viewport to match the height
    view.setViewport(sf::FloatRect(0.f, 0.f, target_aspect / current_aspect, 1.f));
  }else{
    //either it's too tall or it's perfect. let's set the viewport to match width
    view.setViewport(sf::FloatRect(0.0, 0.0, 1.0, current_aspect / target_aspect));
  }
  window->setView(view);
}

void HumanView::draw_background(sf::Color bgcolor){
  sf::RectangleShape bgRect = sf::RectangleShape(sf::Vector2f(800,600));
  bgRect.setPosition(0,0);
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
