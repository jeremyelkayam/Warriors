/*
 * Created by jeremyelkayam on 9/28/20.
 */

#include "input_manager.hpp"

InputManager::InputManager(unsigned int max_players) {

    //todo: change from hardcoded to file loaded
    key_bindings.insert({"P0 UP", sf::Keyboard::Up});
    key_bindings.insert({"P0 DOWN", sf::Keyboard::Down});
    key_bindings.insert({"P0 LEFT", sf::Keyboard::Left});
    key_bindings.insert({"P0 RIGHT", sf::Keyboard::Right});
    key_bindings.insert({"P0 WEAPON", sf::Keyboard::RControl});


    key_bindings.insert({"P1 UP", sf::Keyboard::W});
    key_bindings.insert({"P1 DOWN", sf::Keyboard::S});
    key_bindings.insert({"P1 LEFT", sf::Keyboard::A});
    key_bindings.insert({"P1 RIGHT", sf::Keyboard::D});
    key_bindings.insert({"P1 WEAPON", sf::Keyboard::LShift});
}

player_input InputManager::get_player_input(unsigned long player_number){

    string prefix = "P" + std::to_string(player_number) + " ";

    return player_input { 
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "UP")),
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "DOWN")),
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "LEFT")),
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "RIGHT")),
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "WEAPON"))
    };
}


void InputManager::change_binding(string binding_id, sf::Keyboard::Key new_key){
    if(key_bindings.find(binding_id) == key_bindings.end())
        throw invalid_argument("Key binding with ID "+binding_id+" does not exist.");

    key_bindings.at(binding_id) = new_key;
}