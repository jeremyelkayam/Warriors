#include "keys_screen.hpp"

KeysMenuScreen::KeysMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager) :
MenuScreen(a_text_loader, a_resource_manager, an_input_manager) {
    for(auto it : an_input_manager.get_bindings()){
        sf::Text opt,key;
        opt.setFillColor(sf::Color::White);
        key.setFillColor(sf::Color::White);
        a_resource_manager.setup_text(opt, 20, 0, it.first);
        
        a_resource_manager.setup_text(key, 200, 0, to_upper(thor::toString(it.second)));
        options.emplace_back(opt);
        keys.emplace_back(key);
    }
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

    //fix to a weird off-by-one error
    selector.setSize(sf::Vector2f(seltext.getLocalBounds().width,
                                  seltext.getLocalBounds().height));
}

void KeysMenuScreen::handle_event(sf::Event &evt){
    if(selecting_key) {
        if(evt.type == sf::Event::KeyPressed){
            string id = options.at(selected).getString();
            input_manager.change_binding(id, evt.key.code);
            clear_old_selection(keys.at(selected));
            selecting_key = false;
            reset_selector(options.at(selected));
            
            keys.at(selected).setString(to_upper(thor::toString(evt.key.code)));
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
                clear_old_selection(options.at(selected));
                selecting_key = true;
                reset_selector(keys.at(selected));
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

        keys.at(i).setPosition(keys.at(i).getPosition().x,
            min_y + (i - scroll_position) * interval);  
    }
}

void KeysMenuScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid){
    window.draw(selector);
    for(int i = scroll_position; i < scroll_position + opts_per_screen ; i++){
        window.draw(options.at(i));
        window.draw(keys.at(i));
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