/*
 * enemy.cpp
 * Purpose: an enemy warrior
 *
 */

#include "enemy.hpp"

void Enemy::point_at_player(float player_x, float player_y){
  float delta_x = player_x - get_xcor();
  float delta_y = player_y - get_ycor() ;

  angle = atan2(delta_y,delta_x);
}

Enemy::Enemy(float xcor,float ycor,float speed, sf::Texture &texture) : Warrior(xcor,ycor,speed,texture){
  color = sf::Color::Red;
  Enemy::speed *= 0.75;

}
