#pragma once

#include "screen.hpp"

using std::string;

class MenuScreen : public Screen {
    protected:
        vector<sf::Text> options;
        sf::RectangleShape selector;

        sf::Sprite up_arrow, down_arrow;

        const int opts_per_screen = 6;

        int selected;
        
        bool screen_over;
        float flash_time;
        const float flash_interval;
        virtual void reset_selector(sf::Text &seltext);
        void swap_colors(sf::Text &seltext);

        void clear_old_selection(sf::Text &seltext);

    public:
        MenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager);

        void setup_from_vec(vector<string>options);
        
        virtual void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

        virtual bool go_to_next() override;

        virtual void handle_event(sf::Event &evt) override;

        virtual unique_ptr<Screen> next_screen() = 0;
        
        virtual void update(float s_elapsed) override;
};