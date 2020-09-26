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

void Player::update(float s_elapsed){
  move(s_elapsed);

  if(invis_frames > 0){
    invis_frames -= s_elapsed;
  }
}

Player::Player(TextLoader &text_loader, sf::Texture &texture, sf::Texture &sword_tex, sf::Color color) :
Warrior((float)text_loader.get_double("IDS_VIEW_X") / 2, (float)text_loader.get_double("IDS_VIEW_Y") / 2,
        texture, sword_tex, color),
        max_sword_time((float)text_loader.get_double("IDS_SWORD_TIME")),
        max_invis_frames((float)text_loader.get_double("IDS_INVIS_TIME")){

  set_origin_to_center();

  this->color = color;
  this->speed = (float)text_loader.get_double("IDS_MOVEMENT_SPEED");
  speed_scale_x = 0;
  speed_scale_y = 0;
  this->field_height = (float)text_loader.get_double("IDS_VIEW_Y");
  this->field_width = (float)text_loader.get_double("IDS_VIEW_X");
  this->health = (unsigned int)text_loader.get_integer("IDS_DEFAULT_HEALTH");

  this->invis_frames = 0;
  this->sword_time = max_sword_time;
}

void Player::hurt(int amount){
  //If the player has no invincibility frames left, they can get hurt.
  if(invis_frames <= 0){
    health -= amount;
    invis_frames = max_invis_frames;
    cout << "YOU HURT ME" << endl;
  }
}

void Player::draw(sf::RenderWindow &window, ColorGrid &color_grid) {

  int current_invis_frame = (int)(invis_frames * 10);

  //We should draw the player normally if they don't have any invincibility frames.
  //If they do have invincibility frames, their sprite can flash on and off.
  if(invis_frames <= 0 || current_invis_frame % 2){
    Entity::draw(window, color_grid);
  }
}