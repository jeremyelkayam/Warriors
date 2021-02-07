#pragma once
#include "menu_screen.hpp"

class ScrollingMenuScreen : public MenuScreen { 
protected:
    sf::Text instruc;
    
    unsigned int scroll_position;
    
    const float menu_leftpos = 20;

    void update_scroll();

    vector<sf::Text> second_column;

    ScrollingMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager, 
        InputManager &an_input_manager);

public:

    virtual void draw(sf::RenderWindow &window, ColorGrid &color_grid) override;

    virtual unique_ptr<Screen> next_screen() = 0;

    virtual void handle_event(sf::Event &evt) override;

    virtual void update(float s_elapsed) override;

    
};