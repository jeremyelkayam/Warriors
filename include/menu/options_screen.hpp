#pragma once
#include "menu/scrolling_menu_screen.hpp"
#include "playing_screen.hpp"

class OptionsMenuScreen : public ScrollingMenuScreen { 

    private:
    

    public: 
        OptionsMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager);

        unique_ptr<Screen> next_screen() override;

        void handle_event(sf::Event &evt) override;

        void update(float s_elapsed) override;

};