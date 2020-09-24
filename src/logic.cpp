/*
  logic.cpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#include "logic.hpp"

Logic::Logic(sf::Texture &warrior_tex, mt19937 &rand, float field_width, float field_height, TextLoader &a_text_loader) :
player(field_width/2,field_height/2,100,warrior_tex, field_width, field_height), m_warrior_tex(warrior_tex), randy(rand),
width_dist(0.f,field_width), height_dist(0.f,field_height), text_loader(a_text_loader) {
  time_since_last_enemy_spawn = 0;
  time_since_last_potion_spawn = 0;
  total_time_elapsed = 0;

  this->field_width = field_width;
  this->field_height = field_height;
}

void Logic::update(float s_elapsed){
  total_time_elapsed += s_elapsed;

  player.update(s_elapsed);

  //Check if it's time to spawn an enemy.

  time_since_last_enemy_spawn += s_elapsed;
  time_since_last_potion_spawn += s_elapsed;


  if(can_spawn_enemy()) {
    cout << "spawning enemy" << endl;
    spawn_enemy();
  }
  if(can_spawn_potion()) {
    cout << "spawning potion" << endl;
    spawn_potion();
  }

  update_enemies(s_elapsed);
  update_potions(s_elapsed);
}

void Logic::draw_components(sf::RenderWindow &window,ColorGrid &color_grid){

  //Draw all our enemies
  for (auto it=enemies.begin(); it != enemies.end(); ++it)
    it->draw(window,color_grid);

  //Draw all our potions
  for (auto it=potions.begin(); it != potions.end(); ++it)
    it->draw(window,color_grid);

  player.draw(window,color_grid);
}

sf::Vector2f Logic::random_distant_location(float threshold){
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
  }while(dist<threshold);

  return {xcor,ycor};

}


void Logic::spawn_enemy(){

  sf::Vector2f location = random_distant_location((float)text_loader.get_double("IDS_DISTANCE_THRESHOLD"));

  enemies.emplace_back(Enemy(location.x,location.y,m_warrior_tex));

  time_since_last_enemy_spawn = 0;
}


bool Logic::can_spawn_enemy() {

  return time_since_last_enemy_spawn > spawn_interval(
          (float)text_loader.get_double("IDS_MIN_SPAWN_INTERVAL"),
          (float)text_loader.get_double("IDS_BASE_SPAWN_INTERVAL"),
          (float)text_loader.get_double("IDS_MATURE_GAME"),
          false
          );
}


/*
 * Spawn intervals can increase and decrease depending on the amount of time elapsed in the game.
 * This is a simple function that returns a spawn interval
 *
 * @return true if spawning
 */
float Logic::spawn_interval(float min, float max, float time_limit, bool countingUp){
  float elapsed = total_time_elapsed;
  float scalar;

  //This will prevent us from going over the max or under the min.
  if(elapsed > time_limit) elapsed = time_limit;

  if(countingUp){
    scalar = elapsed / time_limit;
  }else{
    scalar = (time_limit - elapsed) / time_limit;
  }

  float result = max * scalar + min;

  return max * scalar + min;


}

void Logic::update_enemies(float s_elapsed){

  float speed = 100.f / enemies.size();

  for (auto it=enemies.begin(); it != enemies.end(); ++it) {
    it->point_at_player(player.get_xcor(),player.get_ycor());
    it->move(s_elapsed,speed);
  }

}

void Logic::spawn_potion() {
  sf::Vector2f location = random_distant_location((float)text_loader.get_double("IDS_DISTANCE_THRESHOLD"));

  potions.emplace_back(Potion(location.x,location.y,m_warrior_tex, 5, 1));

  time_since_last_potion_spawn = 0;
}

bool Logic::can_spawn_potion() {
  return time_since_last_potion_spawn > spawn_interval(
          5,
          20,
          (float)text_loader.get_double("IDS_MATURE_GAME"),
          true
  );

}


void Logic::update_potions(float s_elapsed){
  auto it=potions.begin();
  while (it != potions.end()) {
    it->update(s_elapsed);
    if (it->can_despawn()) {
      //Delete the current potion, and then move on to the next one
      potions.erase(it++);
    } else {
      ++it;
    }
  }

}