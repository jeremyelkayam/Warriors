#include "menu/keys_screen.hpp"

KeysMenuScreen::KeysMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager) :
ScrollingMenuScreen(a_text_loader, a_resource_manager, an_input_manager) {

    instruc.setString("SELECT A KEY & PRESS ENTER");

    for(auto it : an_input_manager.get_bindings()){
        string s = it.first;
        //We're dealing with chars here. Char 0 is character 48 and they
        //count up from there, which is why this works.
        //This WILL NOT work if there are more than 10 players.
        s.replace(1, 1, std::to_string(s.at(1) - 47));

        ScrollingMenuScreen::add_opt(menu_leftpos, s);

        sf::Text key;
        key.setFillColor(sf::Color::White);
        resource_manager.setup_text(key, 230, 0, to_upper(thor::toString(it.second)), TOP_RIGHT);
        second_column.emplace_back(key);
    }
    ScrollingMenuScreen::add_opt(menu_leftpos, "CANCEL");
    ScrollingMenuScreen::add_opt(menu_leftpos, "SAVE & EXIT");

    selecting_key = false;

    scroll_position = 0;
    selector.setFillColor(sf::Color::Black);
    update_scroll();
    reset_selector(options.at(selected));

}

//yes, this has to be pass-by-value because I'll be passing const strings into this
string KeysMenuScreen::to_upper(string s){
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

void KeysMenuScreen::handle_event(sf::Event &evt){
    if(selecting_key) {
        if(evt.type == sf::Event::KeyPressed){
            string id = options.at(selected).getString();
           id.replace(1, 1, std::to_string(id.at(1) - 49));
            
            input_manager.change_binding(id, evt.key.code);

            clear_old_selection(second_column.at(selected));
            selecting_key = false;
            //reset our text to match the new key pick
            reset_selector(options.at(selected));
            resource_manager.setup_text(second_column.at(selected),
                second_column.at(selected).getPosition().x, second_column.at(selected).getPosition().y,
                to_upper(thor::toString(evt.key.code)), TOP_RIGHT);
        
        }
    }else{
        ScrollingMenuScreen::handle_event(evt);

        //need this to avoid handling KeyReleased events
        if(evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Enter){
            if(options.at(selected).getString() == "CANCEL"){
                input_manager.load_from_file();
                screen_over = true;
            }else if(options.at(selected).getString() == "SAVE & EXIT"){
                input_manager.save_to_file();
                screen_over = true;
            }else{
                clear_old_selection(options.at(selected));
                selecting_key = true;
                reset_selector(second_column.at(selected));
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
            swap_colors(second_column.at(selected));
        }else{
            swap_colors(options.at(selected));
        }
    }
}


unique_ptr<Screen> KeysMenuScreen::next_screen(){
  assert(go_to_next());
  return unique_ptr<MenuScreen>(new MainMenuScreen(text_loader, resource_manager, 
      input_manager));
}