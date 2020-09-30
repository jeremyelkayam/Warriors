//
// Created by jeremyelkayam on 9/28/20.
//

//potentially make human input a toplevel class that everything references

#pragma once


struct player_input {

  bool move_up;
  bool move_down;
  bool move_left;
  bool move_right;

  bool sword;

};


class InputManager {

private:

  player_input my_player_input;

public:

  InputManager(){};

  player_input get_player_input(){ return my_player_input;}

  void set_player_input(player_input a_player_input){my_player_input = a_player_input;}

};