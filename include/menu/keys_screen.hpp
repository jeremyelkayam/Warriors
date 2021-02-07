#pragma once
#include "menu/scrolling_menu_screen.hpp"
#include "menu/main_menu_screen.hpp"
#include <Thor/Input.hpp>

class KeysMenuScreen : public ScrollingMenuScreen { 

    private:

        bool selecting_key;

        string to_upper(string s);

        void add_opt(float xcor, string s, sf::Color color=sf::Color::White);

    public: 
        KeysMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager);

        unique_ptr<Screen> next_screen() override;

        void handle_event(sf::Event &evt) override;

        void update(float s_elapsed) override;

};