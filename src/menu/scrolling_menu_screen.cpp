#include "menu/scrolling_menu_screen.hpp"
ScrollingMenuScreen::ScrollingMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager) :
MenuScreen(a_text_loader, a_resource_manager, an_input_manager) {

    instruc.setFillColor(sf::Color::White);
    resource_manager.setup_text(instruc, 10, 10, "DUMMY");
}

void ScrollingMenuScreen::add_opt(float xcor, string s, sf::Color color){
    sf::Text opt;
    opt.setFillColor(color);
    resource_manager.setup_text(opt, xcor, 0, s);
    options.emplace_back(opt);
}

void ScrollingMenuScreen::update_scroll(){
    float min_y = 30;
    float max_y = 180;

    float interval = (max_y - min_y) / opts_per_screen;
    for(int i = scroll_position; i < scroll_position + opts_per_screen ; i++){
        options.at(i).setPosition(options.at(i).getPosition().x,
            min_y + (i - scroll_position) * interval);

        //There will be more options than keys, e.g. back button
        if(i < second_column.size()){
        second_column.at(i).setPosition(second_column.at(i).getPosition().x,
            min_y + (i - scroll_position) * interval);  
        }
    }   
}


void ScrollingMenuScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid){
    window.draw(selector);
    for(int i = scroll_position; i < scroll_position + opts_per_screen ; i++){
        window.draw(options.at(i));
        //There will be more options than keys, e.g. back button
        if(i < second_column.size()){
            window.draw(second_column.at(i));
        }
    }

    if(scroll_position > 0 ) {
        window.draw(up_arrow);
    }

    if(scroll_position < options.size() - opts_per_screen){
        window.draw(down_arrow);
    }

    window.draw(instruc);
}

void ScrollingMenuScreen::handle_event(sf::Event &evt){
    MenuScreen::handle_event(evt);
    if(evt.type == sf::Event::KeyPressed){
        if(selected < scroll_position){
            scroll_position = selected;
        }else if(selected >= scroll_position + opts_per_screen) {
            scroll_position = selected - opts_per_screen + 1;
        }
        clear_old_selection(options.at(selected));
        update_scroll();
        reset_selector(options.at(selected));
    }
}

void ScrollingMenuScreen::update(float s_elapsed){
    flash_time += s_elapsed;

    // reset the timer if we went over
    if(flash_time > flash_interval){
        flash_time = 0;
        swap_colors(options.at(selected));
    }
}
