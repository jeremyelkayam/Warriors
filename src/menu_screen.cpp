#include "menu_screen.hpp"

MenuScreen::MenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
        InputManager &an_input_manager) :
Screen(a_text_loader, a_resource_manager, an_input_manager),
flash_interval(text_loader.get_float("IDS_MENU_FLASH_INTERVAL")) {

    selected = 0;
    screen_over = false;


    up_arrow.setPosition(text_loader.get_float("IDS_VIEW_X") - 20,10);
    up_arrow.setTexture(resource_manager.get_texture("IDS_PATH_UP_TEX"));

    down_arrow.setPosition(text_loader.get_float("IDS_VIEW_X") - 20,
        text_loader.get_float("IDS_VIEW_Y") - 15);
    down_arrow.setTexture(resource_manager.get_texture("IDS_PATH_DOWN_TEX"));
}

void MenuScreen::clear_old_selection(sf::Text &seltext){
    cout << "clear my boy" << endl;
    if(selector.getFillColor() != sf::Color::Black){
        seltext.setFillColor(selector.getFillColor());
        selector.setFillColor(sf::Color::Black);
        //mark the selector as ready
    }
}

void MenuScreen::reset_selector(sf::Text &seltext){
    assert(selector.getFillColor() == sf::Color::Black);
    selector.setFillColor(seltext.getFillColor());
    seltext.setFillColor(sf::Color::Black);

    selector.setSize(sf::Vector2f(seltext.getGlobalBounds().width,
                                  seltext.getGlobalBounds().height - 1));
    selector.setPosition(seltext.getGlobalBounds().left, seltext.getGlobalBounds().top);
}

void MenuScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid){
    window.draw(selector);
    for(auto &option : options){
        window.draw(option);
    }
}

bool MenuScreen::go_to_next(){
    return screen_over;
}

void MenuScreen::handle_event(sf::Event &evt){
    assert(selected < options.size());
    if(evt.type == sf::Event::KeyPressed){    
        
        clear_old_selection(options.at(selected));
        flash_time = 0;


        //move our menu position forward or backward depending
        if(evt.key.code == sf::Keyboard::Down){
            selected++;
        }else if(evt.key.code == sf::Keyboard::Up){
            selected--;
            //i don't know why but we have to add this extra line
            if(selected < 0) selected += options.size();
        }

        selected %= options.size();
        
        reset_selector(options.at(selected));
    }
}

void MenuScreen::update(float s_elapsed){
    flash_time += s_elapsed;

    // reset the timer if we went over
    if(flash_time > flash_interval){
        flash_time = 0;
        swap_colors(options.at(selected));
    }
}

void MenuScreen::swap_colors (sf::Text &seltext){
    if(selector.getFillColor() == sf::Color::Black){
        selector.setFillColor(seltext.getFillColor());
        seltext.setFillColor(sf::Color::Black);
    }else{
        assert(seltext.getFillColor() == sf::Color::Black);
        seltext.setFillColor(selector.getFillColor());
        selector.setFillColor(sf::Color::Black);
    }
}