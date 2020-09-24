/*
  logic.cpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#include "logic.hpp"

Logic::Logic(sf::Texture &warrior_tex, mt19937 &rand, int field_width, int field_height) :
player(1,1,100,warrior_tex), m_warrior_tex(warrior_tex), randy(rand),
width_dist(0.f,field_width), height_dist(0.f,field_height) {
  time_since_last_spawn = 0;
  spawn_interval = 5;
  this->field_width = field_width;
  this->field_height = field_height;
}

void Logic::update(float s_elapsed){
  player.update(s_elapsed);
  time_since_last_spawn += s_elapsed;

  if(time_since_last_spawn > spawn_interval) {
    cout << "spawn a guy" << endl;
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
  float xcor,ycor,dist;
  do{
    //Generate a random position within our field

    xcor = width_dist(randy);
    ycor = height_dist(randy);

    //Calculate Euclidean distance
    float xdist = player.get_xcor() - xcor;
    float ydist = player.get_ycor() - ycor;

    xdist = (float)pow(xdist, 2.f);
    ydist = (float)pow(ydist, 2.f);

    dist = (float)sqrt(xdist + ydist);

    //We don't want an enemy to spawn on top of the player. That would suck.
    //So, if the player was too close, let's repeat.
  }while(dist<30);

  enemies.emplace_back(Enemy(xcor,ycor,m_warrior_tex));
}

void Logic::update_enemies(float s_elapsed){

  float speed = 100.f / enemies.size();

  for (auto it=enemies.begin(); it != enemies.end(); ++it) {
    it->point_at_player(player.get_xcor(),player.get_ycor());
    it->move(s_elapsed,speed);
  }

}