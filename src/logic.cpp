/*
  logic.cpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#include "logic.hpp"

Logic::Logic(sf::Texture &warrior_tex) : player(0,0,0.0001,warrior_tex), m_warrior_tex(warrior_tex) {
  time_since_last_spawn = 0;
  spawn_interval = 5000000;
}

void Logic::update(int micros_elapsed){
  player.move(micros_elapsed);
  time_since_last_spawn += micros_elapsed;

  if(time_since_last_spawn > spawn_interval) {
    time_since_last_spawn = 0;
    spawn_enemy();
  }
  update_enemies(micros_elapsed);
}

void Logic::draw_components(sf::RenderWindow &window,ColorGrid &color_grid){
  for (std::list<Enemy>::iterator it=enemies.begin(); it != enemies.end(); ++it)
    it->draw(window,color_grid);

  player.draw(window,color_grid);
}

void Logic::spawn_enemy(){
  enemies.push_back(Enemy(100,100, m_warrior_tex));
}

void Logic::update_enemies(int micros_elapsed){
  for (std::list<Enemy>::iterator it=enemies.begin(); it != enemies.end(); ++it) {
    it->point_at_player(player.get_xcor(),player.get_ycor());
    it->move(micros_elapsed);

    //cout<<"angle: " << it->get_angle() << endl;
  }

}