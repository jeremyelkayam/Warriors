#pragma once

#include "screen.hpp"
#include "playing_screen.hpp"

using std::string;

class MenuScreen : public Screen {
    private:
        sf::Text menu_text;
    public:
        MenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager);
        
        void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

        bool go_to_next() override;

        void handle_event(sf::Event &evt) override;

        unique_ptr<Screen> next_screen() override;
};