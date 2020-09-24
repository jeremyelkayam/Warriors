/*
  player.cpp
  Purpose: Represent the player's character.
  Potential Improvement: add more than one player.
*/

#include "player.hpp"

//TODO: Sometimes player's location starts out fucked up. Might be due to memory issues.
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
}

Player::Player(float xcor, float ycor, float speed, sf::Texture &texture, float field_width, float field_height) :
Warrior(xcor,ycor,texture){
  color = sf::Color::Cyan;
  this->speed = speed;
  speed_scale_x = 0;
  speed_scale_y = 0;
  this->field_height = field_height;
  this->field_width = field_width;
}