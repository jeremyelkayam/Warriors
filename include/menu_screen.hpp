#pragma once

#include "screen.hpp"

using std::string;

class MenuScreen : public Screen {
    protected:
        vector<sf::Text> options;
        sf::RectangleShape selector;

        unsigned int selected;
        
        bool screen_over;
        float flash_time;
        const float flash_interval;
        void reset_selector();

    public:
        MenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager);
        
        virtual void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

        virtual bool go_to_next() override;

        virtual void handle_event(sf::Event &evt) override;

        virtual unique_ptr<Screen> next_screen() = 0;
        
        void update(float s_elapsed) override;
};