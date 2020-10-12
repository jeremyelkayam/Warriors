/*
  playing_screen.cpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#include "playing_screen.hpp"

PlayingScreen::PlayingScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager) :
Screen(a_text_loader, a_resource_manager),
        width_dist(0.f,a_text_loader.get_float("IDS_VIEW_X")),
height_dist(0.f,a_text_loader.get_float("IDS_VIEW_Y") - a_text_loader.get_float("IDS_HUD_HEIGHT")),
base_speed(a_text_loader.get_float("IDS_MOVEMENT_SPEED")),
hud(players,total_time_elapsed, a_text_loader,a_resource_manager){
  time_since_last_enemy_spawn = 0;
  time_since_last_potion_spawn = 0;
  total_time_elapsed = 0;

  //Let's set up our random number generator with a commonly used seed: the current time.
  unsigned long my_seed = (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count();
  cout << "my seed: " << my_seed << endl;
  randy.seed(my_seed);

  this->field_width = a_text_loader.get_float("IDS_VIEW_X");
  this->field_height = a_text_loader.get_float("IDS_VIEW_Y") - a_text_loader.get_float("IDS_HUD_HEIGHT");

  background.setTexture(a_resource_manager.get_texture("IDS_PATH_BACKGROUND_TEX0"));
  foreground.setTexture(a_resource_manager.get_texture("IDS_PATH_FOREGROUND_TEX"));

  players.emplace_back(Player(a_text_loader,a_resource_manager.get_texture("IDS_PATH_WARRIOR_TEX"),
          a_resource_manager.get_texture("IDS_PATH_SWORD_TEX"),
          sf::Color::Cyan));

  cout << "num players " << players.size() << endl;
}


void PlayingScreen::update(float s_elapsed){

  if(!go_to_next()) {

    total_time_elapsed += s_elapsed;

    //todo: CHANGE THIS
    keyboard_movement();


    background.setTexture(resource_manager.get_texture("IDS_PATH_BACKGROUND_TEX"
    + std::to_string( (int)(total_time_elapsed * 2) % 2 )));


    //needs to be a reference to avoid copying, but should not be const as we are modifying.
    for(auto &player : players) {
      player.update(s_elapsed);
    }
    //Check if it's time to spawn an enemy.

    time_since_last_enemy_spawn += s_elapsed;
    time_since_last_potion_spawn += s_elapsed;


    if (can_spawn_enemy()) {
      cout << "spawning enemy" << endl;
      spawn_enemy();
    }
    if (can_spawn_potion()) {
      cout << "spawning potion" << endl;
      spawn_potion();
    }

    hud.update();
    update_enemies(s_elapsed);
    update_potions(s_elapsed);
  }
}



void PlayingScreen::draw_gameplay(sf::RenderWindow &window, ColorGrid &color_grid){

  window.draw(background);

  //Draw all our enemies
  for (const auto &it : enemies)
    it.draw(window,color_grid);

  //Draw all our potions
  for (const auto &it : potions)
    it.draw(window,color_grid);

  for(auto &player : players) {
    player.draw(window, color_grid);
  }

  window.draw(foreground);
}

sf::Vector2f PlayingScreen::random_distant_location(float threshold){
  float xcor,ycor,dist;

  do{
    //Generate a random position within our field

    xcor = width_dist(randy);
    ycor = height_dist(randy);

    //The distance checks only matter if the distance goes below the threshold.
    //The initial value for dist is the value above which we don't care about dist.
    dist = threshold;
    //We are only reading from our players, not writing to them. This must be const
    for(const auto &player : players) {

      //Calculate Euclidean distance
      float xdist = player.get_xcor() - xcor;
      float ydist = player.get_ycor() - ycor;

      xdist = xdist * xdist;
      ydist = ydist * ydist;

      dist = min( dist, (float) sqrt((double) xdist + (double) ydist));

      cout << "dist: " <<  (float) sqrt((double) xdist + (double) ydist) << endl;
      cout << "threshold: " << threshold << endl;
    }

    cout << "outer dist: " << dist << endl;

    cout << "loop check: " << (dist < threshold) << endl;

    //We don't want an enemy to spawn on top of the player. That would suck.
    //So, if the player was too close, let's repeat.
  }while(dist<threshold);

  cout << "here you go" << endl;
  return {xcor,ycor};

}


void PlayingScreen::spawn_enemy(){

  sf::Vector2f location = random_distant_location(text_loader.get_float("IDS_DISTANCE_THRESHOLD"));

  enemies.emplace_back(Enemy(location.x,location.y,
                             resource_manager.get_texture("IDS_PATH_WARRIOR_TEX"),
                             resource_manager.get_texture("IDS_PATH_SHORTSWORD_TEX")));

  time_since_last_enemy_spawn = 0;
}


bool PlayingScreen::can_spawn_enemy() {

  return time_since_last_enemy_spawn > spawn_interval(
          text_loader.get_float("IDS_MIN_SPAWN_INTERVAL"),
          text_loader.get_float("IDS_BASE_SPAWN_INTERVAL"),
          text_loader.get_float("IDS_MATURE_GAME"),
          false);
}


/*
 * Spawn intervals can increase and decrease depending on the amount of time elapsed in the game.
 * This is a simple function that returns a spawn interval
 *
 * @return true if spawning
 */
float PlayingScreen::spawn_interval(float min, float max, float time_limit, bool countingUp){
  float elapsed = total_time_elapsed;
  float scalar;

  //This will prevent us from going over the max or under the min.
  if(elapsed > time_limit) elapsed = time_limit;

  if(countingUp){
    scalar = elapsed / time_limit;
  }else{
    scalar = (time_limit - elapsed) / time_limit;
  }

  return max * scalar + min;
}

void PlayingScreen::update_enemies(float s_elapsed){

  float speed = base_speed / (enemies.size() + 1);
  auto it=enemies.begin();
  while (it != enemies.end()) {

    //TODO: enemy AI needs to get a bit more complex for multiplayer. For now, everyone follows P1

    it->update(s_elapsed,speed,players.front().get_xcor(),players.front().get_ycor());
    bool dead = false;

    for(auto &player : players) {
      if (it->slicing(player)) {
        player.hurt(1);//TODO: parameterize this
      }
      if (player.slicing(*it)) {
        enemies.erase(it++);
        dead = true;
        //the enemy here no longer exists, so our pointer is dead. don't do anything with the iterator after this
        //Let's stop the for loop
        break;
      }
    }
    if(!dead) ++it;

  }
}

void PlayingScreen::spawn_potion() {
  sf::Vector2f location = random_distant_location(text_loader.get_float("IDS_DISTANCE_THRESHOLD"));

  potions.emplace_back(Potion(location.x,location.y,resource_manager.get_texture("IDS_PATH_POTION_TEX"), 5, 1));

  time_since_last_potion_spawn = 0;
}

bool PlayingScreen::can_spawn_potion() {
  return time_since_last_potion_spawn > spawn_interval(
          5,
          20,
          text_loader.get_float("IDS_MATURE_GAME"),
          true
  );

}


void PlayingScreen::update_potions(float s_elapsed){
  auto it=potions.begin();

  while (it != potions.end()) {
    it->update(s_elapsed);
    bool destroyed = false;

    if (it->can_despawn()) {
      //Delete the current potion, and then move on to the next one
      potions.erase(it++); // This is kind of ugly. Is there a better way to do this?
      destroyed = true;
    }else {
      //we DO NOT run this if the potion was erased
      for (auto &player : players) {
        if (it->intersects(player)) {
          //We need to delete it, but also heal the player.
          player.heal(it->get_health_recovery());
          potions.erase(it++);
          destroyed = true;
        }
      }
    }
    if(!destroyed) ++it;
  }
}


void PlayingScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid) {
  draw_gameplay(window, color_grid);
  hud.draw(window, color_grid);
}



//todo: This will get more complicated. Eventually move this to the InputManager.
//todo: Also, this should be updated by HumanView, not Logic.
void PlayingScreen::keyboard_movement(){

    players.front().set_movement(
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up),
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down),
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left),
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

    players.front().set_sword(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));

}

unique_ptr<Screen> PlayingScreen::next_screen() {
  assert(go_to_next());
  return unique_ptr<Screen>(new EndScreen(text_loader,resource_manager,total_time_elapsed));
}
