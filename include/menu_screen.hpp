#pragma once

#include "screen.hpp"
#include "playing_screen.hpp"

using std::string;

class MenuScreen : public Screen {
    protected:
        sf::Sprite copyright;
        sf::Text header,footer;
        vector<sf::Text> options;
        sf::RectangleShape selector;

        unsigned int selected;
        
        bool screen_over;
        float flash_time;
        const float flash_interval;
        void reset_selector();

    public:
        MenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager);
        
        void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

        bool go_to_next() override;

        void handle_event(sf::Event &evt) override;

        unique_ptr<Screen> next_screen() override;
        
        void update(float s_elapsed) override;
};