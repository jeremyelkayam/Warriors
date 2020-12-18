/*
  playing_screen.cpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#include "playing_screen.hpp"

PlayingScreen::PlayingScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager, game_options game_opts) :
Screen(a_text_loader, a_resource_manager),
        width_dist(0.f,a_text_loader.get_float("IDS_VIEW_X")),
height_dist(0.f,a_text_loader.get_float("IDS_VIEW_Y") - a_text_loader.get_float("IDS_HUD_HEIGHT")),
time_dist(0.f,a_text_loader.get_float("IDS_VIEW_Y") - a_text_loader.get_float("IDS_HUD_HEIGHT")),
base_speed(a_text_loader.get_float("IDS_MOVEMENT_SPEED")),
base_dmg(1),
base_heal(1),
field_width(a_text_loader.get_float("IDS_VIEW_X")),
field_height(a_text_loader.get_float("IDS_VIEW_Y") - a_text_loader.get_float("IDS_HUD_HEIGHT")),
color_change_interval(a_text_loader.get_float("IDS_COLOR_CHANGE_INTERVAL")),
hud(a_text_loader,a_resource_manager),
ring(a_resource_manager.get_texture("IDS_PATH_RING_TEX"),
     a_resource_manager.get_sound_buffer("IDS_PATH_RING_SOUND"),120.f),
bomb(a_resource_manager.get_texture("IDS_PATH_BOMB_TEX"),
     a_resource_manager.get_texture("IDS_PATH_FUSE_TEX"),
     a_resource_manager.get_sound_buffer("IDS_PATH_BOMB_SOUND"),80.f), //todo: maybe add randomness to the spawn time
dead_players_info(game_opts.num_players),
opts(game_opts){
  time_since_last_enemy_spawn = 0;
  time_since_last_potion_spawn = 0;
  total_time_elapsed = 0;

  field_fill.setSize(sf::Vector2f(field_width,field_height));
  color_change_index = 0;
  last_color_change = 0;

  //Let's set up our random number generator with a commonly used seed: the current time.
  unsigned long my_seed = (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count();
  cout << "my seed: " << my_seed << endl;
  randy.seed(my_seed);

  background.setTexture(a_resource_manager.get_texture("IDS_PATH_BACKGROUND_TEX0"));
  foreground.setTexture(a_resource_manager.get_texture("IDS_PATH_FOREGROUND_TEX"));


  float x_center = text_loader.get_float("IDS_VIEW_X") / 2;
  float y_center = (text_loader.get_float("IDS_VIEW_Y") - 
      text_loader.get_float("IDS_HUD_HEIGHT")) / 2;

  for(unsigned int i = 0; i < opts.num_players ; ++i) {
    /**
     * It looks nicer if we spawn the players in a formation. For a simple formation,
     * let's place them in equidistant positions on the perimeter of a circle.
     * 
     * This is a problem for polar coordinates. Just scale the radius based
     * on the number of players, and put the players at equal angle intervals, which 
     * you can calculate by dividing 2pi by the number of players.
     */
    float r = text_loader.get_float("IDS_SPAWN_RADIUS") * (opts.num_players - 1);
    float theta = i * ( 2 * M_PI / opts.num_players);
   
    // Convert to cartesian and translate to the center of the board.
    float x = r * cos(theta) + x_center;
    float y = r * sin(theta) + y_center;

    players.emplace_back(Player(i,
        a_text_loader,a_resource_manager, player_colors.at(i),
        x, y));
    
    hud.add_player(players.back(), resource_manager.get_font(), resource_manager.get_font_size());
  }

  kill_sound.setBuffer(resource_manager.get_sound_buffer("IDS_PATH_KILL_SOUND"));
  start_sound.setBuffer(resource_manager.get_sound_buffer("IDS_PATH_ROUND_START_SOUND"));
  start_sound.play();

  cout << "num players " << players.size() << endl;
}



void PlayingScreen::update(float s_elapsed){

  if(!go_to_next()) {

    total_time_elapsed += s_elapsed;

    //todo: CHANGE THIS
    keyboard_movement();


    background.setTexture(resource_manager.get_texture("IDS_PATH_BACKGROUND_TEX"
    + std::to_string( (int)(total_time_elapsed * 2) % 2 )));

    // Yes, this means the hud is always going to be one frame behind.
    // But that's because it can't have a null player, which we could create in just a bit here.
    hud.update(total_time_elapsed);

    auto player_iter = players.begin();
    while(player_iter != players.end()){
      if(player_iter->is_dead()){
        dead_players_info.at(player_iter->get_player_number()) = player_iter->postmortem();
        players.erase(player_iter++);
      }else{
        player_iter->update(s_elapsed);

        if(player_iter->intersects(ring) && ring.item_active()){
          ring.consume();
        }

        //todo: this sucks and I want there to be a better way without implementing an events system
        if(player_iter->intersects(bomb) && bomb.item_active()){
          bomb.consume();
          explode();
        }

        ++player_iter;
      }
    }
    //Check if it's time to spawn an enemy.

    time_since_last_enemy_spawn += s_elapsed;
    time_since_last_potion_spawn += s_elapsed;
    ring.update(s_elapsed);
    bomb.update(s_elapsed);


    if (can_spawn_enemy() && !bomb.effect_active()) {
      cout << "spawning enemy" << endl;
      spawn_enemies();
    }
    if (can_spawn_potion()) {
      cout << "spawning potion" << endl;
      spawn_potion();
    }
    spawn_if_able(ring);
    spawn_if_able(bomb);

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

  ring.draw(window,color_grid);
  bomb.draw(window,color_grid);

  //draw the explosion flashes! Boom boom!
  if(bomb.effect_active()){
    field_fill.setFillColor(explosion_colors.at(color_change_index));
    window.draw(field_fill, sf::BlendAdd);

    //Clear the color grid. This is a hacky workaround, but I want the color grid to be disabled while the explosion
    //As implemented, my color grid doesn't support background colors other than black. That's good for most situations,
    //but for this specific case, I want the background colored in. Since it's only for a few seconds, we can sacrifice
    //colored-in characters.
    color_grid.reset();
    if(total_time_elapsed - last_color_change >= color_change_interval) {
      ++color_change_index;
      color_change_index %= explosion_colors.size(); //make sure we loop around the back of the vector
      last_color_change = total_time_elapsed;
    }
  }
}

void PlayingScreen::spawn_if_able(SpecialItem &item){
  if(item.ready_to_spawn()) {
    sf::Vector2f pos = random_distant_location(text_loader.get_float("IDS_DISTANCE_THRESHOLD"));
    item.spawn(pos.x,pos.y);
  }
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


void PlayingScreen::spawn_enemies(){

  for(int i = 0; i < ( total_time_elapsed * players.size() ) || i <= 5 ; i+=15) {

    sf::Vector2f location = random_distant_location(text_loader.get_float("IDS_DISTANCE_THRESHOLD"));

    enemies.emplace_back(Enemy(location.x, location.y,
                               resource_manager.get_texture("IDS_PATH_ENEMY_TEX"),
                               resource_manager.get_texture("IDS_PATH_SHORTSWORD_TEX")));
  }

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
        player.hurt(base_dmg);//TODO: parameterize this
      }

      if (player.slicing(*it)) {
        enemies.erase(it++);
        player.add_kills(1);

        if(ring.effect_active())
          player.heal(base_heal);

        kill_sound.play();
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

  potions.emplace_back(Potion(location.x,location.y,resource_manager.get_texture("IDS_PATH_POTION_TEX"), 5, base_heal));

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
  if(!go_to_next()) throw logic_error("next_screen() can only be called in PlayingScreen if all players are dead.");

  //We MUST pass dead_players_info by value here, sadly. We created it in this class, and the next class needs it.
  //It COULD be stored at a Logic level, but I don't want Logic to have to worry about all that crap.
  return unique_ptr<Screen>(new EndScreen(text_loader,resource_manager,dead_players_info, opts));
}

void PlayingScreen::explode() {
  if(!bomb.effect_active()) throw logic_error("explode() can only be called immediately after the bomb is activated.");
  if(ring.effect_active()) {
    for (auto &player : players) {
      //The bomb is unique in that it heals all players equally. The amount of health healed per enemy
      //is dependent on the heal nerf. Health is then divided equally between all players.
      player.heal((unsigned int) (enemies.size() / (players.size() * text_loader.get_integer("IDS_BOMB_HEAL_NERF"))));
      player.add_kills((unsigned int) (enemies.size() / players.size()));
    }
  }
  enemies.clear();
  last_color_change = total_time_elapsed;
}
