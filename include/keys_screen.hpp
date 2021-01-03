#pragma once
#include "main_menu_screen.hpp"
#include <Thor/Input.hpp>

class KeysMenuScreen : public MenuScreen { 

    private:

        sf::Text instruc;
    
        unsigned int scroll_position;
        
        void update_scroll();

        void reset_selector(sf::Text &seltext) override;

        vector<sf::Text> keys;

        bool selecting_key;

        string to_upper(string s);

    public: 
        KeysMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager);

        void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

        unique_ptr<Screen> next_screen() override;

        void handle_event(sf::Event &evt) override;

        void update(float s_elapsed) override;

};