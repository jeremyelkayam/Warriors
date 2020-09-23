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

float Enemy::speed = 0.0001;

Enemy::Enemy(float xcor,float ycor, sf::Texture &texture) : Warrior(xcor,ycor,texture){
  color = sf::Color::Red;
  Enemy::speed *= 0.75;

}
void Enemy::move(int micros_elapsed){
  float new_xcor = get_xcor() + (speed*cos(angle)*micros_elapsed);
  float new_ycor = get_ycor() + (speed*sin(angle)*micros_elapsed);

  sprite.setPosition(new_xcor,new_ycor);
}

Enemy::~Enemy(){
  //WHERE IS THE DESTRUCTOR BEING CALLED FROM? SOMEHOW IT IS CALLED ONCE PER SPAWN
  cout << "DELETING ME" << endl;
  //Enemy::speed /= 0.75;
}