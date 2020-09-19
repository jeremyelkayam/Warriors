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
        shared_ptr<TextLoader>text_loader) :
        color_grid(text_loader,(float)text_loader->get_double("IDS_VIEW_X"),(float)text_loader->get_double("IDS_VIEW_Y")){
  this->logic=logic;
  this->window=window;
  this->text_loader=text_loader;
  this->view=sf::View(sf::FloatRect(0.f,0.f,
          (float)text_loader->get_double("IDS_VIEW_X"),
          (float)text_loader->get_double("IDS_VIEW_Y")));



  //Initialize our colors.
  d_blue=sf::Color(0,0,215);
  d_red=sf::Color(215,0,0);
  d_magenta=sf::Color(215,0,215);
  d_green=sf::Color(0,215,0);
  d_cyan=sf::Color(0,215,215);
  d_yellow=sf::Color(215,215,0);
  d_white=sf::Color(215,215,215);



  warrior_tex.loadFromFile(text_loader->get_string("IDS_PATH_WARRIOR_TEX"));
}

void HumanView::draw_warrior(std::shared_ptr<Warrior>warrior){
  const float height = (float)text_loader->get_double("IDS_WARRIOR_H");
  const float width = (float)text_loader->get_double("IDS_WARRIOR_W");

  //initializing a new sprite on the stack every time we draw it is kinda gross. Probably eventually
  //want to give each warrior its own sprite on the heap.
  sf::Sprite warriorSprite(warrior_tex);
  warriorSprite.setPosition((float)warrior->get_xcor()-height/2,(float)warrior->get_ycor()-width/2);



  window->draw(warriorSprite);
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
  color_grid.reset();
  window->clear(d_white);
  draw_background(sf::Color::Black);
  draw_warrior(logic->getPlayer());
  color_grid.draw(window);
  window->setView(window->getDefaultView());
  window->display();
}
