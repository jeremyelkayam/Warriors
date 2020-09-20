/*
  logic.cpp
  Purpose: Handle the logic computations of the game's main loop
           (e.g. controls, collison detection, etc).
  @author Jeremy Elkayam
 */

#include "logic.hpp"

Logic::Logic() : player(0,0){

}

void Logic::update(int micros_elapsed){
  player.move(micros_elapsed);
}

void Logic::take_input(float angle){

  if(player.get_current_speed() == 0.f){
    player.set_angle(angle);
  }else if(player.get_angle()!=angle){
    //if the angle doesn't change we son't do anything
    
    if(abs(player.get_angle()-angle)==M_PI){
      player.set_moving(false);
    }else{
      cout<<"average"<<endl;
      player.set_angle((player.get_angle()+angle)/2);
    }
  }

  player.set_moving(true);
}
