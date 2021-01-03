/*
 * Created by jeremyelkayam on 9/28/20.
 */

#include "input_manager.hpp"

InputManager::InputManager(unsigned int max_players) {

    load_from_file();
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

void InputManager::load_from_file(){
    XMLDocument doc;

    if(doc.LoadFile( "../userdata/controls.xml" )) throw std::runtime_error("Controls file not found");

    XMLElement * root =  doc.FirstChildElement("controls");

    for(tinyxml2::XMLElement* node = root->FirstChildElement("binding");
            node != nullptr; node= node->NextSiblingElement("binding")) {
        string cmd = node->Attribute("cmd");
        sf::Keyboard::Key key = thor::toKeyboardKey(node->Attribute("key"));
        key_bindings.emplace(cmd,key);
    }
}

void InputManager::save_to_file(){
    XMLDocument doc;

    if(doc.LoadFile( "../userdata/controls.xml" )) throw std::runtime_error("Controls file not found");

    XMLElement * root =  doc.FirstChildElement("controls");

    XMLElement* node = root->FirstChildElement("binding");
    for(auto binding : key_bindings){
        if (node == nullptr) throw std::logic_error("you fucked up the file");

        node->SetAttribute("cmd", binding.first.c_str());
        node->SetAttribute("key", thor::toString(binding.second).c_str());

        node= node->NextSiblingElement("binding");
    }

    doc.SaveFile("../userdata/controls.xml" );

}