/*
 * enemy.cpp
 * Purpose: an enemy warrior
 *
 */

#include "enemy.hpp"

void Enemy::point_at_player(float player_x, float player_y){
  float delta_x = player_x - get_xcor();
  float delta_y = player_y - get_ycor() ;

  angle = (float)atan2(delta_y,delta_x);
}

float Enemy::speed = 100.f;

Enemy::Enemy(float xcor,float ycor, sf::Texture &texture) : Warrior(xcor,ycor,texture){
  cout << " i am born " << endl;
  color = sf::Color::Red;
  Enemy::speed *= 0.75f;

}
void Enemy::move(float s_elapsed){
  float new_xcor = get_xcor() + (speed*(float)cos(angle)*s_elapsed);
  float new_ycor = get_ycor() + (speed*(float)sin(angle)*s_elapsed);

  sprite.setPosition(new_xcor,new_ycor);
}

Enemy::~Enemy(){
  //WHERE IS THE DESTRUCTOR BEING CALLED FROM? SOMEHOW IT IS CALLED ONCE PER SPAWN
  cout << "DELETING ME" << endl;
  //Enemy::speed /= 0.75;
}