//
// Created by jeremyelkayam on 9/28/20.
//

#pragma once

#include <map>
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <stdexcept>
#include <Thor/Input.hpp>
#include "tinyxml2.h"

using std::map;
using std::string;
using std::cout;
using std::endl;
using std::invalid_argument;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

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
  map<string, sf::Keyboard::Key> key_bindings;

public:

  explicit InputManager(unsigned int max_players);

  player_input get_player_input(unsigned long player_number);

  map<string, sf::Keyboard::Key> get_bindings() {return key_bindings;}

  void change_binding(string binding_id, sf::Keyboard::Key new_key);

  //void set_player_input(player_input a_player_input){my_player_input = a_player_input;}

  //todo: implement saving to file
  void load_from_file();
  void save_to_file();
};