//
// Created by jeremyelkayam on 9/28/20.
//

#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using std::unordered_map;
using std::string;
using std::cout;
using std::endl;

struct player_input {

  bool move_up;
  bool move_down;
  bool move_left;
  bool move_right;

  bool sword;

};




class InputManager {

private:

  //more extensible so that we can have menu keys, etc etc
  unordered_map<string, sf::Keyboard::Key> key_bindings;

public:

  explicit InputManager(unsigned int max_players);

  player_input get_player_input(unsigned long player_number);

  unordered_map<string, sf::Keyboard::Key> get_bindings() {return key_bindings;}

  //void set_player_input(player_input a_player_input){my_player_input = a_player_input;}

  //todo: implement saving to file
  void load_inputs();
  void save_inputs();
};