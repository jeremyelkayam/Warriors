
#pragma once
#include "menu_screen.hpp"

class KeysScreen : public MenuScreen { 

    private:
        sf::Sprite up_arrow, down_arrow;
        vector<pair<sf::Text,sf::Text>> key_opts;

        int scroll_position, cursor_position;

        const int opts_per_screen;


    public: 
        KeysScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager);
}