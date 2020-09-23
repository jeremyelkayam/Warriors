/*
  logic.cpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#include "logic.hpp"

Logic::Logic(sf::Texture &warrior_tex, mt19937 &rand) : player(1,1,100,warrior_tex), m_warrior_tex(warrior_tex), randy(rand) {
  time_since_last_spawn = 0;
  spawn_interval = 5;
}

void Logic::update(float s_elapsed){
  player.move(s_elapsed);
  time_since_last_spawn += s_elapsed;

  if(time_since_last_spawn > spawn_interval) {
    time_since_last_spawn = 0;
    spawn_enemy();
  }
  update_enemies(s_elapsed);
}

void Logic::draw_components(sf::RenderWindow &window,ColorGrid &color_grid){
  for (auto it=enemies.begin(); it != enemies.end(); ++it)
    it->draw(window,color_grid);

  player.draw(window,color_grid);
}

void Logic::spawn_enemy(){
  enemies.emplace_back(Enemy(100,100, m_warrior_tex));
}

void Logic::update_enemies(float s_elapsed){
  for (auto it=enemies.begin(); it != enemies.end(); ++it) {
    it->point_at_player(player.get_xcor(),player.get_ycor());
    it->move(s_elapsed);

    //cout<<"angle: " << it->get_angle() << endl;
  }

}