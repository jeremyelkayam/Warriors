/*
 * enemy.cpp
 * Purpose: an enemy warrior
 *
 */

#include "enemy.hpp"

void Enemy::point_at_player(float player_x, float player_y){
  float delta_x = player_x - get_xcor();
  float delta_y = player_y - get_ycor();

  angle = (float)atan2(delta_y,delta_x);
}

Enemy::Enemy(float xcor,float ycor, sf::Texture &texture, sf::Texture &sword_tex) :
Warrior(xcor,ycor,texture, sword_tex, sf::Color::Red) {
  set_origin_to_center();
  sword.unsheath();

  //cout << " i am born " << endl;
}
void Enemy::move(float s_elapsed,float speed){
  float new_xcor = get_xcor() + (speed*(float)cos(angle)*s_elapsed);
  float new_ycor = get_ycor() + (speed*(float)sin(angle)*s_elapsed);

  sprite.setPosition(new_xcor,new_ycor);
}

void Enemy::update(float s_elapsed, float speed, float player_x, float player_y){
  point_at_player(player_x, player_y);
  move(s_elapsed, speed);
  sword.update(sprite.getPosition().x, sprite.getPosition().y, angle);
}
