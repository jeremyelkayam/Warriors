/*
  player.cpp
  Purpose: Represent the player's character.
  Potential Improvement: add more than one player.
*/

#include "player.hpp"

void Player::move(float s_elapsed){
  float new_xcor = get_xcor() + speed*speed_scale_x*s_elapsed;
  float new_ycor = get_ycor() + speed*speed_scale_y*s_elapsed;

  //Don't want our player going off-screen. He should stop at the borders.
  if(new_xcor < 0) new_xcor = 0;
  if(new_xcor > field_width) new_xcor = field_width;
  if(new_ycor < 0) new_ycor = 0;
  if(new_ycor > field_height) new_ycor = field_height;

  sprite.setPosition(new_xcor,new_ycor);

  //cout << "position: " << new_xcor << "," << new_ycor << endl;
}

void Player::set_movement(bool moving_up, bool moving_down, bool moving_left, bool moving_right){
  speed_scale_x=0.f;
  speed_scale_y=0.f;

  if(moving_left){
    speed_scale_x-=1.f;
  }
  if(moving_right){
    speed_scale_x+=1.f;
  }
  if(moving_up){
    speed_scale_y-=1.f;
  }
  if(moving_down){
    speed_scale_y+=1.f;
  }

  if(speed_scale_y != 0.f && speed_scale_x != 0.f){
    speed_scale_y *= sin(M_PI/4);
    speed_scale_x *= sin(M_PI/4);
  }
}

void Player::set_sword(bool active){
  if(active){
    //The player cannot draw their sword if they are recharging sword time.
    if(sword_time >= max_sword_time){
      sword.unsheath();
      slash_sound.play();
    }
  }else{
    if(sword.is_active()) sheath_sound.play();
    sword.sheath();
  }
}

void Player::update(float s_elapsed){
  if(is_dead()) throw logic_error("Dead players cannot use the method update(float s_elapsed).");

  move(s_elapsed);

  if(invis_frames > 0){
    invis_frames -= s_elapsed;
  }

  update_sword(s_elapsed);

  info.age += s_elapsed;
}

void Player::update_sword(float s_elapsed){

  if(speed_scale_x == 0 && speed_scale_y == 0) {
    sword.update(get_xcor(), get_ycor());
  }else {
    auto angle = (float) atan2((double)speed_scale_y, (double)speed_scale_x);

    sword.update(get_xcor(), get_ycor(), angle);
  }

  //If the player is using their sword, they are using up sword time.
  if(sword.is_active()){
    sword_time -= s_elapsed;

    //If the player is not using their sword, they are recharging sword time.
  }else if(sword_time < max_sword_time){
    sword_time += s_elapsed;
  }

  //If the player runs out of sword time, they must sheath their sword.
  if(sword_time <= 0){
    sheath_sound.play();
    sword.sheath();
  }
}

Player::Player(unsigned int &a_player_number, TextLoader &text_loader, ResourceManager &resource_manager, sf::Color color) :
player_number(a_player_number),
Warrior(text_loader.get_float("IDS_VIEW_X") / 2,
        (text_loader.get_float("IDS_VIEW_Y") - text_loader.get_float("IDS_HUD_HEIGHT")) / 2,
        resource_manager.get_texture("IDS_PATH_WARRIOR_TEX"),
        resource_manager.get_texture("IDS_PATH_SWORD_TEX"),
        color),
        max_sword_time(text_loader.get_float("IDS_SWORD_TIME")),
        max_invis_frames(text_loader.get_float("IDS_INVIS_TIME")){

  cout << "make a player" << endl;

  set_origin_to_center();

  this->color = color;
  this->speed = text_loader.get_float("IDS_MOVEMENT_SPEED");
  speed_scale_x = 0;
  speed_scale_y = 0;
  this->field_height = text_loader.get_float("IDS_VIEW_Y") - text_loader.get_float("IDS_HUD_HEIGHT");
  this->field_width = text_loader.get_float("IDS_VIEW_X");
  this->health = (unsigned int)text_loader.get_integer("IDS_DEFAULT_HEALTH");
  this->info.num_kills = 0;
  this->info.age = 0;

  this->invis_frames = 0;
  this->sword_time = max_sword_time;


  hurt_sound.setBuffer(resource_manager.get_sound_buffer("IDS_PATH_HURT_SOUND"));
  heal_sound.setBuffer(resource_manager.get_sound_buffer("IDS_PATH_HEAL_SOUND"));
  slash_sound.setBuffer(resource_manager.get_sound_buffer("IDS_PATH_SLASH_SOUND"));
  sheath_sound.setBuffer(resource_manager.get_sound_buffer("IDS_PATH_SHEATH_SOUND"));

  sword.sheath();
}

void Player::hurt(unsigned int amount){
  //If the player has no invincibility frames left, they can get hurt.
  if(invis_frames <= 0){
    health -= amount;
    invis_frames = max_invis_frames;
    hurt_sound.play();
    //cout << "YOU HURT ME" << endl;
  }
}

void Player::heal(unsigned int amount) {
  health += amount;
  heal_sound.play();
}

void Player::draw(sf::RenderWindow &window, ColorGrid &color_grid) const {

  auto current_invis_frame = (int)(invis_frames * 10);

  //We should draw the player normally if they don't have any invincibility frames.
  //If they do have invincibility frames, their sprite can flash on and off.
  if(invis_frames <= 0 || current_invis_frame % 2){
    Warrior::draw(window, color_grid);
  }
}


postmortem_info Player::postmortem() {
  if(!is_dead()) throw logic_error("postmortem() can only be called on a player that is already dead.");
  return info;
}