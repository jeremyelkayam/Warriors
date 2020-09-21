/*
  player.cpp
  Purpose: Represent the player's character.
  Potential Improvement: add more than one player.
*/

#include "player.hpp"

void Player::move(int micros_elapsed){
  float xvelocity=0.f;
  float yvelocity=0.f;

  if(moving_left){
    xvelocity-=1.f;
  }
  if(moving_right){
    xvelocity+=1.f;
  }
  if(moving_up){
    yvelocity-=1.f;
  }
  if(moving_down){
    yvelocity+=1.f;
  }


  if(yvelocity != 0.f && xvelocity != 0.f){
    yvelocity*=sin(M_PI/4);
    xvelocity*=sin(M_PI/4);
  }


  float new_xcor = get_xcor() + speed*xvelocity*micros_elapsed;
  float new_ycor = get_ycor() + speed*yvelocity*micros_elapsed;

  sprite.setPosition(new_xcor,new_ycor);

}

void Player::set_moving(Player::Direction direction, bool moving){
  switch(direction){
    case Direction::Left :
      moving_left = moving;
      break;
    case Direction::Right :
      moving_right = moving;
      break;
    case Direction::Up :
      moving_up = moving;
      break;
    case Direction::Down :
      moving_down = moving;
      break;
  }
}