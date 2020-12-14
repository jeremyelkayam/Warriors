//
// Created by jeremyelkayam on 9/30/20.
//

#pragma once

#include <list>
#include "screen.hpp"
#include "title_screen.hpp"
#include "player.hpp"

using std::string;
using std::list;

class EndScreen : public Screen {

private:

  const game_options opts;

  bool screen_over;
  bool play_again;

  float time_so_far;

  const float min_screen_time;

  list<sf::Text> screen_texts;

  void setup_text(sf::Text &text, float xcor, float ycor, string content, int size_multiplier);

  sf::Sound end_game_sound;


public:
  EndScreen(TextLoader &text_loader, ResourceManager &resource_manager, vector<postmortem_info> dead_players_info, game_options game_opts);

  void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

  void update(float s_elapsed) override;

  bool go_to_next() override;

  void handle_event(sf::Event &evt) override;

  unique_ptr<Screen> next_screen() override;
};
