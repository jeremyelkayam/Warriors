//
// Created by jeremyelkayam on 10/8/20.
//

#include "hud.hpp"

HUD::HUD(list<Player> &some_players, float &elapsed_time_ref, TextLoader &a_text_loader,
        ResourceManager &a_resource_manager) :
players(some_players), total_time_elapsed(elapsed_time_ref),
top(a_text_loader.get_float("IDS_VIEW_Y") - a_text_loader.get_float("IDS_HUD_HEIGHT")) {

  background.setTexture(a_resource_manager.get_texture("IDS_PATH_HUD_TEX"));
  background.setPosition(0,top);

  time_text.setFont(a_resource_manager.get_font());
  time_text.setCharacterSize((unsigned int)a_text_loader.get_integer("IDS_FONT_SIZE"));
  time_text.setFillColor(sf::Color::White);

  float y = 9.f + top;
  time_text.setPosition(150, y);


  //health_unit.setSize(sf::Vector2f(1.f, 6.f));
  //health_unit.setFillColor(sf::Color::White);

}

//

void HUD::update(){
  //Let's get the number of digits BEFORE the decimal point
  unsigned long whole_digits = std::to_string((int)total_time_elapsed).length();

  string time_trunc = std::to_string(total_time_elapsed);
  time_trunc.resize(whole_digits + 3);

  time_text.setString("time " + time_trunc);

}

void HUD::draw(sf::RenderWindow &window, ColorGrid &color_grid) const {

  window.draw(background);
  color_grid.update(background.getGlobalBounds(), sf::Color::White);



  /*for(const auto &player : players) {

    for (int i = 0; i < player.get_health(); ++i) {
      rect.setPosition(i * 2, y);
      window.draw(rect);
      color_grid.update(rect.getGlobalBounds(), sf::Color::Cyan);
    }
  }
   */

  window.draw(time_text);
}