#include "keys_screen.hpp"

KeysMenuScreen::KeysMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager) :
MenuScreen(a_text_loader, a_resource_manager, an_input_manager) {
    for(auto it : an_input_manager.get_bindings()){
        sf::Text opt,key;
        opt.setFillColor(sf::Color::White);
        key.setFillColor(sf::Color::White);
        resource_manager.setup_text(opt, 20, 0, it.first);
        
        resource_manager.setup_text(key, 230, 0, to_upper(thor::toString(it.second)), TOP_RIGHT);
        options.emplace_back(opt);
        keys.emplace_back(key);
    }
    sf::Text menu_end;
    menu_end.setFillColor(sf::Color::White);
    resource_manager.setup_text(menu_end, 20, 0, "BACK");
    options.emplace_back(menu_end);

    scroll_position = 0;
    selecting_key = false;
    selector.setFillColor(sf::Color::Black);
    update_scroll();
    reset_selector(options.at(selected));
}

//yes, this has to be pass-by-value because I'll be passing const strings into this
string KeysMenuScreen::to_upper(string s){
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

void KeysMenuScreen::reset_selector(sf::Text &seltext){
    MenuScreen::reset_selector(seltext);
}

void KeysMenuScreen::handle_event(sf::Event &evt){
    if(selecting_key) {
        if(evt.type == sf::Event::KeyPressed){
            string id = options.at(selected).getString();
            
            input_manager.change_binding(id, evt.key.code);

            clear_old_selection(keys.at(selected));
            selecting_key = false;
            reset_selector(options.at(selected));
            resource_manager.setup_text(keys.at(selected),
                keys.at(selected).getPosition().x, keys.at(selected).getPosition().y,
                to_upper(thor::toString(evt.key.code)), TOP_RIGHT);
        
        }
    }else{
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

            if(evt.key.code == sf::Keyboard::Enter){
                if(options.at(selected).getString() == "BACK"){
                    screen_over = true;
                }else{
                    clear_old_selection(options.at(selected));
                    selecting_key = true;
                    reset_selector(keys.at(selected));
                }
            }
        }
    }
}

void KeysMenuScreen::update(float s_elapsed){
    flash_time += s_elapsed;

    // reset the timer if we went over
    if(flash_time > flash_interval){
        flash_time = 0;
        if(selecting_key){
            swap_colors(keys.at(selected));
        }else{
            swap_colors(options.at(selected));
        }
    }
}

void KeysMenuScreen::update_scroll(){
    float min_y = 20;
    float max_y = 180;

    float interval = (max_y - min_y) / opts_per_screen;
    for(int i = scroll_position; i < scroll_position + opts_per_screen ; i++){
        options.at(i).setPosition(options.at(i).getPosition().x,
            min_y + (i - scroll_position) * interval);

        //There will be more options than keys, e.g. back button
        if(i < keys.size()){
        keys.at(i).setPosition(keys.at(i).getPosition().x,
            min_y + (i - scroll_position) * interval);  
        }
    }
}

void KeysMenuScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid){
    window.draw(selector);
    for(int i = scroll_position; i < scroll_position + opts_per_screen ; i++){
        window.draw(options.at(i));
        //There will be more options than keys, e.g. back button
        if(i < keys.size()){
            window.draw(keys.at(i));
        }
    }

    if(scroll_position > 0 ) {
        window.draw(up_arrow);
    }

    if(scroll_position < options.size() - opts_per_screen){
        window.draw(down_arrow);
    }
}

unique_ptr<Screen> KeysMenuScreen::next_screen(){
  assert(go_to_next());
  return unique_ptr<MenuScreen>(new MainMenuScreen(text_loader, resource_manager, 
      input_manager));
}