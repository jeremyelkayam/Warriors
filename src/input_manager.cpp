/*
 * Created by jeremyelkayam on 9/28/20.
 */

#include "input_manager.hpp"

InputManager::InputManager(unsigned int max_players) {

    //todo: change from hardcoded to file loaded
    key_bindings.insert({"P0_UP", sf::Keyboard::Up});
    key_bindings.insert({"P0_DOWN", sf::Keyboard::Down});
    key_bindings.insert({"P0_LEFT", sf::Keyboard::Left});
    key_bindings.insert({"P0_RIGHT", sf::Keyboard::Right});
    key_bindings.insert({"P0_SWORD", sf::Keyboard::RControl});


    key_bindings.insert({"P1_UP", sf::Keyboard::W});
    key_bindings.insert({"P1_DOWN", sf::Keyboard::S});
    key_bindings.insert({"P1_LEFT", sf::Keyboard::A});
    key_bindings.insert({"P1_RIGHT", sf::Keyboard::D});
    key_bindings.insert({"P1_SWORD", sf::Keyboard::LShift});
}

player_input InputManager::get_player_input(unsigned long player_number){

    string prefix = "P" + std::to_string(player_number) + "_";

    return player_input { 
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "UP")),
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "DOWN")),
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "LEFT")),
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "RIGHT")),
        sf::Keyboard::isKeyPressed(key_bindings.at(prefix + "SWORD"))
    };
}

