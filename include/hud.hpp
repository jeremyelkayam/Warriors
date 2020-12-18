//
// Created by jeremyelkayam on 10/8/20.
//

#pragma once

#include "player.hpp"
#include "resource_manager.hpp"
#include <list>
#include <cassert>
#include <SFML/Graphics.hpp>

using std::list;

class HUD {
private:
  sf::Sprite background;

  const float top, health_bar_width, health_bar_height, sword_bar_max_width,
      sword_bar_height, right_boundary, top_padding, left_padding;

  const sf::Texture &sword_icon_tex;

  sf::Text time_text;

  struct hud_section {
    const Player &player;
    list<sf::RectangleShape>health_bars;
    sf::RectangleShape sword_bar;
    sf::Sprite sword_icon;
    sf::Text text;
  };

  list<hud_section>sections;

public:

  HUD(TextLoader &a_text_loader, ResourceManager &a_resource_manager);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) const;

  void update(float &total_time_elapsed);

  void add_player(const Player &player, sf::Font &font, const unsigned int &size);

};