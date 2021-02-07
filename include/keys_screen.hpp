#pragma once
#include "scrolling_menu_screen.hpp"
#include "main_menu_screen.hpp"
#include <Thor/Input.hpp>

class KeysMenuScreen : public ScrollingMenuScreen { 

    private:

        void reset_selector(sf::Text &seltext) override;

        bool selecting_key;

        string to_upper(string s);

        void add_opt(float xcor, string s, sf::Color color=sf::Color::White);

    public: 
        KeysMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager);

        // void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

        unique_ptr<Screen> next_screen() override;

        void handle_event(sf::Event &evt) override;

        void update(float s_elapsed) override;

};