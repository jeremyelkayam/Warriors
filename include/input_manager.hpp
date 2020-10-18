//
// Created by jeremyelkayam on 9/28/20.
//

//potentially make human input a toplevel class that everything references

#pragma once

#include <vector>

using std::vector;

struct player_input {

  bool move_up;
  bool move_down;
  bool move_left;
  bool move_right;

  bool sword;

};


class InputManager {

private:

  vector<player_input> my_player_input;

public:

  explicit InputManager(unsigned int max_players);

  player_input get_player_input(unsigned long player_number){ return my_player_input.at(player_number);}

  //void set_player_input(player_input a_player_input){my_player_input = a_player_input;}

  void update();

};