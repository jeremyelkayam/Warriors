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
player_padding(a_text_loader.get_float("IDS_HUD_PLAYER_PADDING")),
sword_icon_tex(a_resource_manager.get_texture("IDS_PATH_SWORD_READY_TEX")),
dead_icon_tex(a_resource_manager.get_texture("IDS_PATH_SKULL_TEX"))
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

  for(hud_section &section : sections) {
    if (section.player.is_dead()) {

      section.health_bars.clear();
      
    } else if(!section.health_bars.empty()) {
      //Health bar will only be empty if they're dead

      //If they're not dead, we do everything normally.

      //cout << "time to update the sections" << endl;
      const int player_health = section.player.get_health();

      //in this case, the player has less health than they have health bars. That's a problem.
      while (player_health < section.health_bars.size()) {
        //Remove health bars until our health meter is accurate to the player's health meter.
        section.health_bars.pop_back();
      }

      while(player_health > section.health_bars.size()){
        sf::RectangleShape &previous_bar = section.health_bars.back();
        sf::RectangleShape next_bar(sf::Vector2f(health_bar_width, health_bar_height));

        float xpos = previous_bar.getGlobalBounds().left + health_bar_width + 1;
        float ypos = previous_bar.getGlobalBounds().top;

        float max_xpos = section.text.getGlobalBounds().left + player_padding;

        //This means we ran out of room. Can't exactly draw any more health in that case
        if(xpos > max_xpos) break;

        next_bar.setPosition(xpos, ypos);
        next_bar.setFillColor(sf::Color::White);
        section.health_bars.emplace_back(next_bar);
      }


        // //This is a check to make sure we're not spilling over into the next player's space.
        // if(section_iterator->health_bars.back().getGlobalBounds().left
        //       >= (xorigin + player_padding - (health_bar_width + 1 )))
        //   break;


      //todo: Maybe the sword bar needs something to show where the maximum is.
      //Maybe a sprite that appears next to the bar when the sword is ready?
      float sword_bar_width =
              (section.player.get_sword_time() / section.player.get_max_sword_time())
              * sword_bar_max_width;
      section.sword_bar.setSize(sf::Vector2f(sword_bar_width, sword_bar_height));

    }


  }

}

void HUD::draw ( sf::RenderWindow &window, ColorGrid &color_grid ) const {

  window.draw( background );
  color_grid.update( background.getGlobalBounds(), sf::Color::White );


  for ( const auto &section : sections ) {

    sf::Color fill_color = sf::Color::White;

    if( section.health_bars.empty() ){

      //The player will probably be deleted at this point.
      //So just keep it as white for now

      window.draw(section.dead_icon);
      color_grid.update(section.dead_icon.getGlobalBounds(),fill_color);
      
    }else{
      
      fill_color = section.player.get_color();
      
      for( const auto &rect : section.health_bars ){
        window.draw(rect);
        color_grid.update(rect.getGlobalBounds(), fill_color);
      }
      window.draw(section.sword_bar);

      if(section.player.get_sword_time() >= section.player.get_max_sword_time()) {
        window.draw(section.sword_icon);
      }

    }
    
    color_grid.update(section.text.getGlobalBounds(), fill_color);
    window.draw(section.text);


  }
  window.draw(time_text);
}

void HUD::add_player(const Player &player, sf::Font &font, const unsigned int &size) {
  cout << "time to make the structs. how many players? " << endl;
  struct hud_section section {
    player,
    {sf::RectangleShape(sf::Vector2f(health_bar_width, health_bar_height))},
    sf::RectangleShape(sf::Vector2f(sword_bar_max_width, sword_bar_height)),
    sf::Sprite(sword_icon_tex),
    sf::Sprite(dead_icon_tex),
    sf::Text()
  };
  section.text.setFont(font);
  section.text.setCharacterSize(size);
  section.text.setString("P" + std::to_string(player.get_player_number() + 1));
  section.text.setFillColor(sf::Color::White);

  unsigned int player_number = player.get_player_number();
  float ypos = top_padding + top;

  if(player_number >= 4){
    ypos += top_padding + 1;
    player_number -= 4;
  }

  float xpos = left_padding + player_padding * player_number;

  section.text.setPosition(xpos, ypos);
  xpos += section.text.getLocalBounds().width + 1;

  //setup one of our health bars. We can set up the rest later, but this first one 
  //will help determine the positions of our other ones
  section.health_bars.back().setPosition(xpos, ypos);
  section.health_bars.back().setFillColor(sf::Color::White);

  //The dead icon has the same position as the health bars because it will replace our 
  //bar once this player's dead
  section.dead_icon.setPosition(xpos, ypos);

  ypos += health_bar_height + 1;

  section.sword_bar.setPosition(xpos, ypos);
  section.sword_bar.setFillColor(sf::Color::White);


  xpos += sword_bar_max_width + 1;

  section.sword_icon.setPosition(xpos, ypos);

  sections.emplace_back(section);
}