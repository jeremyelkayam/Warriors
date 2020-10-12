//
// Created by jeremyelkayam on 10/8/20.
//

#pragma once

#include "player.hpp"
#include "resource_manager.hpp"
#include <list>
#include <SFML/Graphics.hpp>

using std::list;

class HUD {
private:
  sf::Sprite background;

  float &total_time_elapsed;
  const float top;

  list<Player> &players;

  sf::Text time_text;
  list<list<sf::RectangleShape>> health_bars;
  list<sf::RectangleShape> sword_bars;

public:

  HUD(list<Player> &some_players, float &elapsed_time_ref,
          TextLoader &a_text_loader, ResourceManager &a_resource_manager);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) const;

  void update();

};