//
// Created by jeremyelkayam on 10/8/20.
//

#include "hud.hpp"

HUD::HUD(TextLoader &a_text_loader, ResourceManager &a_resource_manager) :
top(a_text_loader.get_float("IDS_VIEW_Y") - a_text_loader.get_float("IDS_HUD_HEIGHT")),
health_bar_width( a_text_loader.get_float("IDS_HEALTHBAR_W") ),
health_bar_height( a_text_loader.get_float("IDS_HEALTHBAR_H") ),
sword_bar_max_width( a_text_loader.get_float("IDS_SWORDBAR_W") ),
sword_bar_height( a_text_loader.get_float("IDS_SWORDBAR_H") ),
right_boundary(a_text_loader.get_float("IDS_HUD_RBOUND")),
top_padding(a_text_loader.get_float("IDS_HUD_TOP_PADDING")),
left_padding(a_text_loader.get_float("IDS_HUD_LEFT_PADDING")),
sword_icon_tex(a_resource_manager.get_texture("IDS_PATH_SWORD_READY_TEX"))
{

  background.setTexture(a_resource_manager.get_texture("IDS_PATH_HUD_TEX"));
  background.setPosition(0,top);

  time_text.setFont(a_resource_manager.get_font());
  time_text.setCharacterSize((unsigned int)a_resource_manager.get_font_size());
  time_text.setFillColor(sf::Color::White);

  //todo: parameterize.
  float y = top_padding + top;
  time_text.setPosition(right_boundary, y);

  //health_unit.setSize(sf::Vector2f(1.f, 6.f));
  //health_unit.setFillColor(sf::Color::White);

}

//

void HUD::update(float &total_time_elapsed){


  //Let's get the number of digits BEFORE the decimal point
  unsigned long whole_digits = std::to_string((int)total_time_elapsed).length();

  string time_trunc = std::to_string(total_time_elapsed);
  time_trunc.resize(whole_digits + 3);

  time_text.setString("time " + time_trunc);
  //cout << "sections: " << sections.size() << endl;

  auto section_iterator = sections.begin();

  // float ypadding = 8.0f;
  // float xpadding = 8.0f;

  while(section_iterator != sections.end()) {
    if (section_iterator->player.is_dead()) {

      sections.erase(section_iterator++);

    } else {

      float xorigin = left_padding; //+ (right_boundary - left_padding) / num 
      float yorigin = top_padding + top;

      //If they're not dead, we do everything normally.

      //cout << "time to update the sections" << endl;
      const int player_health = section_iterator->player.get_health();

      //in this case, the player has less health than they have health bars. That's a problem.
      while (player_health < section_iterator->health_bars.size()) {
        //Remove health bars until our health meter is accurate to the player's health meter.
        section_iterator->health_bars.pop_back();
      }

      section_iterator->text.setPosition(xorigin, yorigin);
      xorigin += section_iterator->text.getLocalBounds().width + 1;

      //This for loop only runs if
      //Why mix 'while' and 'for'? Well, I need indexing to determine the positions of the health bars. Sorry.
      for (int i = section_iterator->health_bars.size(); i < player_health; ++i) {

        sf::RectangleShape next_bar(sf::Vector2f(health_bar_width, health_bar_height));
        //todo: maybe parameterize more
        //todo: this will only work for player one
        next_bar.setPosition(xorigin + i * (health_bar_width + 1), yorigin);
        next_bar.setFillColor(sf::Color::White);
        section_iterator->health_bars.emplace_back(next_bar);
      }

      //At this point, the health bars should equal the player's health.
      //Just to be safe, let's assert.
      assert(section_iterator->health_bars.size() == player_health);

      //todo: Maybe the sword bar needs something to show where the maximum is.
      //Maybe a sprite that appears next to the bar when the sword is ready?
      float sword_bar_width =
              (section_iterator->player.get_sword_time() / section_iterator->player.get_max_sword_time())
              * sword_bar_max_width;
      section_iterator->sword_bar.setSize(sf::Vector2f(sword_bar_width, sword_bar_height));
      section_iterator->sword_bar.setFillColor(sf::Color::White);
      section_iterator->sword_bar.setPosition(xorigin, yorigin + health_bar_height + 1.f);

      section_iterator->sword_icon.setTexture(sword_icon_tex, true);
      section_iterator->sword_icon.setPosition(xorigin + sword_bar_width + 1.f, yorigin + health_bar_height + 1.f);

      //Advance the loop.
      ++section_iterator;
    }
  }

}

void HUD::draw ( sf::RenderWindow &window, ColorGrid &color_grid ) const {

  window.draw( background );
  color_grid.update( background.getGlobalBounds(), sf::Color::White );


  for ( const auto &section : sections ) {
    for( const auto &rect : section.health_bars ){
      window.draw(rect);
      color_grid.update(rect.getGlobalBounds(), section.player.get_color());
    }
    window.draw(section.sword_bar);

    if(section.player.get_sword_time() >= section.player.get_max_sword_time()) {
      window.draw(section.sword_icon);
    }
    color_grid.update(section.text.getGlobalBounds(), section.player.get_color());
    window.draw(section.text);
  }

  window.draw(time_text);
}

void HUD::add_player(const Player &player, sf::Font &font, const unsigned int &size) {
  cout << "time to make the structs. how many players? " << endl;
  struct hud_section section {
    player,
    {},
    sf::RectangleShape(),
    sf::Sprite(),
    sf::Text()
  };
  section.text.setFont(font);
  section.text.setCharacterSize(size);
  section.text.setString("P" + std::to_string(player.get_player_number() + 1));
  section.text.setFillColor(sf::Color::White);

  sections.emplace_back(section);
}