#pragma once
#include "menu_screen.hpp"
#include "playing_screen.hpp"
#include "keys_screen.hpp"

class MainMenuScreen : public MenuScreen { 
    private:
        sf::Sprite copyright;
        sf::Text header,footer;
        
    public:
        MainMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
            InputManager &an_input_manager);

        void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

        unique_ptr<Screen> next_screen() override;

        void handle_event(sf::Event &evt) override;

};